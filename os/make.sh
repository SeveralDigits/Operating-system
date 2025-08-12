#!/bin/bash
set -e

# Assemble bootloader (raw binary)
nasm -f bin boot.s -o boot.bin

# Compile kernel C files (32-bit, freestanding)
gcc -m32 -ffreestanding -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-builtin -c vga.c -o vga.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-builtin -c keyboard.c -o keyboard.o

# Link kernel ELF at 0x10000
ld -m elf_i386 -T linker.ld -o kernel.elf kernel.o vga.o keyboard.o

# Convert kernel ELF to raw binary
objcopy -O binary kernel.elf kernel.bin

# Create empty disk image (10MB)
dd if=/dev/zero of=disk.img bs=512 count=20480

# Write bootloader to sector 0 (first 512 bytes)
dd if=boot.bin of=disk.img bs=512 count=1 conv=notrunc

# Write kernel starting at sector 2 (offset 1024 bytes)
dd if=kernel.bin of=disk.img bs=512 seek=2 conv=notrunc

echo "Build complete. To run in QEMU:"
echo "qemu-system-i386 -drive format=raw,file=disk.img"

# Compiler and flags
CC = gcc
CFLAGS = -m32 -fno-stack-protector -fno-builtin
AS = nasm
ASFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386 -T linker.ld

# Targets
OBJS = boot.o kernel.o vga.o keyboard.o
ISO = kernel.iso
KERNEL_PATH = Jazz/boot/kernel

all: $(ISO)

# Compile C sources
kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

vga.o: vga.c
	$(CC) $(CFLAGS) -c vga.c -o vga.o

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) -c keyboard.c -o keyboard.o

# Assemble bootloader
boot.o: boot.s
	$(AS) $(ASFLAGS) boot.s -o boot.o

# Link everything into kernel
kernel: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o kernel $(OBJS)
	mv kernel $(KERNEL_PATH)

# Build ISO with GRUB
$(ISO): kernel
	grub-mkrescue -o $(ISO) Jazz/

# Clean build artifacts
clean:
	rm -f *.o kernel $(ISO)

# Run with QEMU
run: $(ISO)
	qemu-system-i386 $(ISO)

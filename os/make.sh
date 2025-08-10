gcc -m32 -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o
gcc -m32 -fno-stack-protector -fno-builtin -c vga.c -o vga.o
gcc -m32 -fno-stack-protector -fno-builtin -c keyboard.c -o keyboard.o
nasm -f elf32 boot.s -o  boot.o
ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o vga.o keyboard.o
mv kernel Jazz/boot/kernel
grub-mkrescue -o kernel.iso Jazz/
echo "remember you can virtualize it with qemu like so"
echo "qemu-system-i386 kernel.iso"

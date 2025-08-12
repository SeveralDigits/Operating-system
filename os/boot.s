BITS 16
org 0x7C00

start:
    cli                 ; Disable interrupts
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Set VGA graphics mode 0x0D (640x200 16-color)
    mov ah, 0x00
    mov al, 0x0D
    int 0x10

    ; Setup GDT (just like before)
    ; ... your GDT setup code here ...

    ; Enable protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump to protected mode code
    jmp 0x08:pm_start

[BITS 32]
pm_start:
    ; Set up segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000        ; Setup stack

    ; Call kernel entry point
    call kmain

hang:
    hlt
    jmp hang

times 510-($-$$) db 0
dw 0xAA55

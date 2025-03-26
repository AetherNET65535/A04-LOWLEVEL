[org 0x7C00]    ; BIOS 加载 MBR 到 0x7C00

mov [BOOT_DRIVE], dl  ; BIOS 传来的启动驱动器号

; 进入 32 位模式
cli
lgdt [GDT_DESC]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:init_32

[bits 32]
init_32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000  ; 设置堆栈指针

    call _start       ; 调用 C 代码

    hlt              ; 停机

; GDT 结构
gdt:
    dq 0x0000000000000000   ; 空描述符
    dq 0x00CF9A000000FFFF   ; 代码段
    dq 0x00CF92000000FFFF   ; 数据段
gdt_end:

GDT_DESC:
    dw gdt_end - gdt - 1
    dd gdt

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xAA55

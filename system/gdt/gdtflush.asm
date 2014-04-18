global gdt_flush     ; Allows the C code to link to this
extern gp            ; '_gp' is in another file
gdt_flush:
    lgdt [gp]        ; Load the GDT with '_gp' 
    mov ax, 0x10      ; 0x10 is the offset in the GDT to the data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to the code segment: Far jump!
flush2:
    ret               ; Returns back to the C code



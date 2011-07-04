section .text
    global puts

puts: ; puts(char *msg, int length);
    push ebp
    mov ebp, esp

    mov eax, 4         ; system call should be write
    mov ebx, 1         ; should write to stdout
    mov ecx, [ebp+8]   ; grab the first argument (message) off of the stack
    mov edx, [ebp+12]  ; grab the second argument (length) off of the stack
    int 0x80           ; perform the system call

    mov esp, ebp
    pop ebp

    ret

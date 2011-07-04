section .text
    global puts

puts: ; puts(char *msg, int length);
    push rbp
    mov rbp, rsp

    mov eax, 4          ; system call should be write
    mov ebx, 1          ; should write to stdout
    mov ecx, [rbp+16]   ; grab the first argument (message) off of the stack
    mov edx, [rbp+24]   ; grab the second argument (length) off of the stack
    int 0x80            ; perform the system call

    mov rsp, rbp
    pop rbp

    ret

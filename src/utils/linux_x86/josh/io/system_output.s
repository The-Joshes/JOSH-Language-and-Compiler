section .text
    global system_puts

system_puts:     ; system_puts(char *msg, int length);
    mov eax, 4   ; system call for output
    mov ebx, 1   ; use standard out
    mov ecx, edi ; place message in correct register
    mov edx, esi ; place length in the correct register
    int 0x80     ; perform the system call

    ret

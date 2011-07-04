section .text
    global system_puts

system_puts:     ; system_puts(char *msg, int length);
    mov rax, 4   ; system call for output 
    mov rbx, 1   ; use standard out
    mov rcx, rdi ; place message in correct register 
    mov rdx, rsi ; place length in the correct register
    int 0x80     ; perform the system call

    ret

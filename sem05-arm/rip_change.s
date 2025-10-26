.intel_syntax noprefix
.extern printf
.data                   # Ассемблер не делает автоматический переход в .text после .data.
format:
    .string "%s\n"
message:
    .string "Hello world!" 
.text
.global main
A:
    lea rdi, [rip + format]
    lea rsi, [rip + message]
    xor rax, rax
    call printf
    mov rax, 0
    ret

B:
    lea rax, [rip + A] # rax = (rip + A)
    mov [rsp], rax
    mov rax, 0
    ret

main:
    call B
    mov rax, 0
    ret
    
    
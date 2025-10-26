.intel_syntax noprefix
.global push
.global pop
.text
push:
  # sub rsp, 8
  mov [rsp - 8], rdi
  mov rax, 0
  ret

pop:
  mov rax, [rsp - 8]
  ret



# sub rsp, 8
# mov [rsp - 8], rdi
# mov [rsp], rdi
# ret

# rip = [rsp]  rdi
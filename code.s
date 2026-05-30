// Codigo apenas para ver os bytes de meus diferentes comandos de linguagem de maquina

.text
.global code

code:
    pushq %rbp
    movq %rsp, %rbp
    
    movq %rdi, %rax
    
    leave
    ret
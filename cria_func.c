/* Eugenio Antelo 2412882 3WA */
/* Pedro Favassa 2400000 3WA */

#include "cria_func.h"

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    int pos = 0;
    int p_idx = 0; // se orig_val for PARAM, descobrimos a partir desse contador qual dos argumentos originais recebidos estamos processando.
    int i;

unsigned char prol[] = {
        0x55,                   // push %rbp
        0x48, 0x89, 0xe5,       // mov %rsp, %rbp
        0x41, 0x54,             // push %r12
        0x41, 0x55,             // push %r13
        0x41, 0x56,             // push %r14
        0x41, 0x57,             // push %r15 (manter a pilha alinhada em 16 bytes)
        0x49, 0x89, 0xfc,       // mov %rdi, %r12 (salva o 1 argumento recebido)
        0x49, 0x89, 0xf5,       // mov %rsi, %r13 (salva o 2 argumento recebido)
        0x49, 0x89, 0xd6        // mov %rdx, %r14 (salva o 3 argumento recebido)
    };

    // copia os 19 bytes do prol[i] para o vetor final(codigo[pos],que tá em branco), escrevendo no pos byte a byte.
    for (i = 0; i < 19; i++) {
        codigo[pos++] = prol[i];
    }
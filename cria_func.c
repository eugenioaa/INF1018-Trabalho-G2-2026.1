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
    for (i = 0; i < n; i++) {
        // caso 1: Parâmetro Fixo 
        if (params[i].orig_val == FIX) {
            if (params[i].tipo_val == INT_PAR) {
                if (i == 0) { codigo[pos++] = 0xbf; }
                else if (i == 1) { codigo[pos++] = 0xbe; }
                else if (i == 2) { codigo[pos++] = 0xba; }
                
                *(int*)(&codigo[pos]) = params[i].valor.v_int;
                pos += 4; //  (tamanho do int)
            } else {
                if (i == 0) { codigo[pos++] = 0x48; codigo[pos++] = 0xbf; }
                else if (i == 1) { codigo[pos++] = 0x48; codigo[pos++] = 0xbe; }
                else if (i == 2) { codigo[pos++] = 0x48; codigo[pos++] = 0xba; }
                
                *(void**)(&codigo[pos]) = params[i].valor.v_ptr;
                pos += 8; // (tamanho do ponteiro 64 bits)
            }
        }
        // caso 2: Parâmetro Indireto 
        else if (params[i].orig_val == IND) {
            codigo[pos++] = 0x48; codigo[pos++] = 0xb8;
            *(void**)(&codigo[pos]) = params[i].valor.v_ptr;
            pos += 8;

            if (params[i].tipo_val == INT_PAR) {
                if (i == 0) { codigo[pos++] = 0x8b; codigo[pos++] = 0x38; }
                else if (i == 1) { codigo[pos++] = 0x8b; codigo[pos++] = 0x30; }
                else if (i == 2) { codigo[pos++] = 0x8b; codigo[pos++] = 0x10; }
            } else {
                if (i == 0) { codigo[pos++] = 0x48; codigo[pos++] = 0x8b; codigo[pos++] = 0x38; }
                else if (i == 1) { codigo[pos++] = 0x48; codigo[pos++] = 0x8b; codigo[pos++] = 0x30; }
                else if (i == 2) { codigo[pos++] = 0x48; codigo[pos++] = 0x8b; codigo[pos++] = 0x10; }
            }
        }
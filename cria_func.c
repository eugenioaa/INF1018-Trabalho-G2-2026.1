/* Eugenio Antelo 2412882 3WA */
/* Pedro Favassa 2412917 3WA */

#include "cria_func.h"

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    int pos = 0;
    int p_idx = 0;
    int i;

unsigned char prol[] = {
        0x55,                   // push %rbp
        0x48, 0x89, 0xe5,       // mov %rsp, %rbp
        0x41, 0x54,             // push %r12
        0x41, 0x55,             // push %r13
        0x41, 0x56,             // push %r14
        0x41, 0x57,             // push %r15 
        0x49, 0x89, 0xfc,       // mov %rdi, %r12 
        0x49, 0x89, 0xf5,       // mov %rsi, %r13 
        0x49, 0x89, 0xd6        // mov %rdx, %r14 
    };

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
                pos += 4; 
            } else {
                if (i == 0) { codigo[pos++] = 0x48; codigo[pos++] = 0xbf; }
                else if (i == 1) { codigo[pos++] = 0x48; codigo[pos++] = 0xbe; }
                else if (i == 2) { codigo[pos++] = 0x48; codigo[pos++] = 0xba; }
                
                *(void**)(&codigo[pos]) = params[i].valor.v_ptr;
                pos += 8; 
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
        // caso 3: Parâmetro Repassado 
        else if (params[i].orig_val == PARAM) {

            if (p_idx == 0) {
 
                if (params[i].tipo_val == INT_PAR) {
                    if (i == 0) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xe7; }
                    else if (i == 1) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xe6; }
                    else if (i == 2) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xe2; }
                } else {
                    if (i == 0) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xe7; }
                    else if (i == 1) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xe6; }
                    else if (i == 2) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xe2; }
                }
            } 
            else if (p_idx == 1) {
                if (params[i].tipo_val == INT_PAR) {
                    if (i == 0) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xef; }
                    else if (i == 1) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xee; }
                    else if (i == 2) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xea; }
                } else {
                    if (i == 0) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xef; }
                    else if (i == 1) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xee; }
                    else if (i == 2) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xea; }
                }
            } 
            else if (p_idx == 2) {
                if (params[i].tipo_val == INT_PAR) {
                    if (i == 0) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xf7; }
                    else if (i == 1) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xf6; }
                    else if (i == 2) { codigo[pos++] = 0x44; codigo[pos++] = 0x89; codigo[pos++] = 0xf2; }
                } else {
                    if (i == 0) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xf7; }
                    else if (i == 1) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xf6; }
                    else if (i == 2) { codigo[pos++] = 0x4c; codigo[pos++] = 0x89; codigo[pos++] = 0xf2; }
                }
            }
            p_idx++; 
        }
    }

    codigo[pos++] = 0x48; codigo[pos++] = 0xb8;


    *(void**)(&codigo[pos]) = f;
    pos += 8;

    codigo[pos++] = 0xff; codigo[pos++] = 0xd0;
    unsigned char epi[] = {
        0x41, 0x5f, // pop %r15
        0x41, 0x5e, // pop %r14
        0x41, 0x5d, // pop %r13
        0x41, 0x5c, // pop %r12
        0xc9,       // leave 
        0xc3        // ret 
    };
    for (i = 0; i < 8; i++) {
        codigo[pos++] = epi[i];
    }
}
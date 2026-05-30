/* Eugenio Antelo 2412882 3WA */
/* Pedro Favassa 2400000 3WA */

#include "cria_func.h"

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;

    codigo[i++] = 0x55;        // push %rbp
    codigo[i++] = 0x48;        // mov %rsp, %rbp
    codigo[i++] = 0x89;
    codigo[i++] = 0xE5;


    codigo[i++] = 0xC9;        
    codigo[i++] = 0xC3;

}

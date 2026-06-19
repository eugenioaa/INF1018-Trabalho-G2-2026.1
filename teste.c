#include <stdio.h>
#include <string.h>
#include "cria_func.h"

int mult(int x, int y) {
    return x * y;
}
int operacao_complexa(int a, int b, int c) {
    return (a + b) * c;
}
int dobro(int x) {       
    return x * 2;
}
int soma_ptrs(int* a, int* b) {   
    return (*a) + (*b);
}

typedef int (*fp_int)    (int);
typedef int (*fp_noarg)  ();
typedef int (*fp_intptr) (int*);
typedef int (*fp_ptr2)   (void*, size_t);

char fixa[] = "quero saber se a outra string e um prefixo dessa";

int main(void) {
    unsigned char codigo[500];
    DescParam params[3];

    printf("------- TESTE 1: mult - PARAM + FIX -------\n");
    params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
    params[1].tipo_val = INT_PAR; params[1].orig_val = FIX;
    params[1].valor.v_int = 10;
    cria_func(mult, params, 2, codigo);
    fp_int f1 = (fp_int) codigo;
    printf("mult(5, 10) = %d | Esperado: 50\n\n", f1(5));

    printf("------- TESTE 2: operacao_complexa - PARAM + IND + FIX -------\n");
    int b = 3;
    params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
    params[1].tipo_val = INT_PAR; params[1].orig_val = IND;
    params[1].valor.v_ptr = &b;
    params[2].tipo_val = INT_PAR; params[2].orig_val = FIX;
    params[2].valor.v_int = 2;
    cria_func(operacao_complexa, params, 3, codigo);
    fp_int f2 = (fp_int) codigo;
    printf("(4+3)*2 = %d\n", f2(4));
    b = 5;
    printf("(4+5)*2 = %d\n\n", f2(4));

    printf("------- TESTE 3: dobro - 1 parametro -------\n");
    params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
    cria_func(dobro, params, 1, codigo);
    fp_int f3a = (fp_int) codigo;
    printf("dobro(5) PARAM = %d\n", f3a(5));
    params[0].tipo_val = INT_PAR; params[0].orig_val = FIX;
    params[0].valor.v_int = 7;
    cria_func(dobro, params, 1, codigo);
    fp_noarg f3b = (fp_noarg) codigo;
    printf("dobro(7) FIX   = %d\n\n", f3b());

    printf("------- TESTE 4: soma_ptrs - PTR_PAR FIX + PTR_PAR PARAM -------\n");
    int va = 10, vb = 5;
    params[0].tipo_val = PTR_PAR; params[0].orig_val = FIX;
    params[0].valor.v_ptr = &va;
    params[1].tipo_val = PTR_PAR; params[1].orig_val = PARAM;
    cria_func(soma_ptrs, params, 2, codigo);
    fp_intptr f4 = (fp_intptr) codigo;
    printf("soma_ptrs(&10, &5) = %d\n\n", f4(&vb));

    printf("------- TESTE 5: mult - IND + FIX, sem argumentos -------\n");
    int i;
    params[0].tipo_val = INT_PAR; params[0].orig_val = IND;
    params[0].valor.v_ptr = &i;
    params[1].tipo_val = INT_PAR; params[1].orig_val = FIX;
    params[1].valor.v_int = 10;
    cria_func(mult, params, 2, codigo);
    fp_noarg f5 = (fp_noarg) codigo;
    for (i = 1; i <= 10; i++)
        printf("%d ", f5());
    printf("\n\n");

    printf("------- TESTE 6: memcmp - PTR FIX + PTR PARAM + INT PARAM -------\n");
    params[0].tipo_val = PTR_PAR; params[0].orig_val = FIX;
    params[0].valor.v_ptr = fixa;
    params[1].tipo_val = PTR_PAR; params[1].orig_val = PARAM;
    params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;
    cria_func(memcmp, params, 3, codigo);
    fp_ptr2 mesmo_prefixo = (fp_ptr2) codigo;
    char s[] = "quero saber tudo";
    int tam = 12;
    printf("prefixo-%d: %s\n", tam, mesmo_prefixo(s, tam) ? "NAO" : "SIM");
    tam = (int)strlen(s);
    printf("prefixo-%d: %s\n", tam, mesmo_prefixo(s, tam) ? "NAO" : "SIM");

    return 0;
}
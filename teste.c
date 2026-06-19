#include <stdio.h>
#include "cria_func.h"

int mult(int x, int y) {
    return x * y;
}

typedef int (*func_ptr) (int x);

int main(void){
    unsigned char codigo[500];
    DescParam params[3];

    params[0].tipo_val = INT_PAR; 
    params[0].orig_val = PARAM;

    params[1].tipo_val = INT_PAR; 
    params[1].orig_val = FIX;     
    params[1].valor.v_int = 10;


    cria_func(mult, params, 2, codigo);
    func_ptr f_mult = (func_ptr) codigo;

    printf("Testando a funcao gerada dinamicamente...\n");

    int resultado = f_mult(5);
    printf("Resultado obtido: %d\n", resultado);

    return 0;
}
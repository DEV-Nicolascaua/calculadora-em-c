#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

int main() {
    char expressao[100];
    char posfixa[100];
    char infixaConvertida[100];
    float resultado;

    printf("Digite a expressao infixa (separe por espacos, use 'raiz', 'sen' e 'cos'):\n");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = '\0'; 

    infixaParaPosfixa(expressao, posfixa);
    printf("\nExpressao em posfixa: %s\n", posfixa);

    posfixaParaInfixa(posfixa, infixaConvertida);
    printf("Expressao convertida de volta para infixa: %s\n", infixaConvertida);

    resultado = avaliarPosfixa(posfixa);
    printf("Resultado da expressao: %.2f\n", resultado);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "expressao.h"


void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, char *item) {
    if (p->topo < MAX_TAM - 1) {
        p->topo++;
        strcpy(p->itens[p->topo], item);
    }
}

char* desempilhar(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[p->topo--];
    }
    return NULL;
}

char* topo(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[p->topo];
    }
    return NULL;
}


void inicializarPilhaFloat(PilhaFloat *p) {
    p->topo = -1;
}

int pilhaVaziaFloat(PilhaFloat *p) {
    return p->topo == -1;
}

void empilharFloat(PilhaFloat *p, float item) {
    if (p->topo < MAX_TAM - 1) {
        p->topo++;
        p->itens[p->topo] = item;
    }
}

float desempilharFloat(PilhaFloat *p) {
    if (!pilhaVaziaFloat(p)) {
        return p->itens[p->topo--];
    }
    return 0.0;
}

float topoFloat(PilhaFloat *p) {
    if (!pilhaVaziaFloat(p)) {
        return p->itens[p->topo];
    }
    return 0.0;
}


int precedencia(char *op) {
    if (strcmp(op, "sen") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "raiz") == 0)
        return 4;
    if (strcmp(op, "^") == 0)
        return 3;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    return 0;
}

int ehOperador(char *token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
           strcmp(token, "^") == 0;
}

int ehFuncao(char *token) {
    return strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "raiz") == 0;
}


void infixaParaPosfixa(const char *expressao, char *saida) {
    Pilha p;
    inicializarPilha(&p);
    char exp[MAX_TAM];
    strcpy(exp, expressao);

    char *token = strtok(exp, " ");
    saida[0] = '\0';

    while (token != NULL) {
        if (isdigit(token[0])) {
            strcat(saida, token);
            strcat(saida, " ");
        } else if (ehFuncao(token)) {
            empilhar(&p, token);
        } else if (strcmp(token, "(") == 0) {
            empilhar(&p, token);
        } else if (strcmp(token, ")") == 0) {
            while (!pilhaVazia(&p) && strcmp(topo(&p), "(") != 0) {
                strcat(saida, desempilhar(&p));
                strcat(saida, " ");
            }
            desempilhar(&p);
            if (!pilhaVazia(&p) && ehFuncao(topo(&p))) {
                strcat(saida, desempilhar(&p));
                strcat(saida, " ");
            }
        } else if (ehOperador(token)) {
            while (!pilhaVazia(&p) &&
                   precedencia(topo(&p)) >= precedencia(token)) {
                strcat(saida, desempilhar(&p));
                strcat(saida, " ");
            }
            empilhar(&p, token);
        }
        token = strtok(NULL, " ");
    }

    while (!pilhaVazia(&p)) {
        strcat(saida, desempilhar(&p));
        strcat(saida, " ");
    }
}


void posfixaParaInfixa(const char *expressao, char *saida) {
    Pilha p;
    inicializarPilha(&p);
    char exp[MAX_TAM];
    strcpy(exp, expressao);

    char *token = strtok(exp, " ");
    saida[0] = '\0';

    while (token != NULL) {
        if (isdigit(token[0])) {
            empilhar(&p, token);
        } else if (ehFuncao(token)) {
            char op1[MAX_TAM];
            strcpy(op1, desempilhar(&p));
            char temp[MAX_TAM];
            sprintf(temp, "%s(%s)", token, op1);
            empilhar(&p, temp);
        } else if (ehOperador(token)) {
            char op2[MAX_TAM], op1[MAX_TAM];
            strcpy(op2, desempilhar(&p));
            strcpy(op1, desempilhar(&p));
            char temp[MAX_TAM];
            sprintf(temp, "(%s %s %s)", op1, token, op2);
            empilhar(&p, temp);
        }
        token = strtok(NULL, " ");
    }

    strcpy(saida, desempilhar(&p));
}


float avaliarPosfixa(const char *expressao) {
    PilhaFloat p;
    inicializarPilhaFloat(&p);
    char exp[MAX_TAM];
    strcpy(exp, expressao);

    char *token = strtok(exp, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            empilharFloat(&p, atof(token));
        } else if (strcmp(token, "sen") == 0) {
            float op = desempilharFloat(&p);
            empilharFloat(&p, sin(op));
        } else if (strcmp(token, "cos") == 0) {
            float op = desempilharFloat(&p);
            empilharFloat(&p, cos(op));
        } else if (strcmp(token, "raiz") == 0) {
            float op = desempilharFloat(&p);
            empilharFloat(&p, sqrt(op));
        } else if (strcmp(token, "+") == 0) {
            float b = desempilharFloat(&p);
            float a = desempilharFloat(&p);
            empilharFloat(&p, a + b);
        } else if (strcmp(token, "-") == 0) {
            float b = desempilharFloat(&p);
            float a = desempilharFloat(&p);
            empilharFloat(&p, a - b);
        } else if (strcmp(token, "*") == 0) {
            float b = desempilharFloat(&p);
            float a = desempilharFloat(&p);
            empilharFloat(&p, a * b);
        } else if (strcmp(token, "/") == 0) {
            float b = desempilharFloat(&p);
            float a = desempilharFloat(&p);
            empilharFloat(&p, a / b);
        } else if (strcmp(token, "^") == 0) {
            float b = desempilharFloat(&p);
            float a = desempilharFloat(&p);
            empilharFloat(&p, pow(a, b));
        }
        token = strtok(NULL, " ");
    }

    return desempilharFloat(&p);
}

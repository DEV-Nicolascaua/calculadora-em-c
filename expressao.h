#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#define MAX_TAM 100

typedef struct {
    char itens[MAX_TAM][MAX_TAM];
    int topo;
} Pilha;

typedef struct {
    float itens[MAX_TAM];
    int topo;
} PilhaFloat;


void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, char *item);
char* desempilhar(Pilha *p);
char* topo(Pilha *p);

void inicializarPilhaFloat(PilhaFloat *p);
int pilhaVaziaFloat(PilhaFloat *p);
void empilharFloat(PilhaFloat *p, float item);
float desempilharFloat(PilhaFloat *p);
float topoFloat(PilhaFloat *p);


void infixaParaPosfixa(const char *expressao, char *saida);
void posfixaParaInfixa(const char *expressao, char *saida);
float avaliarPosfixa(const char *expressao);

#endif

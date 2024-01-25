#ifndef PILHAEP2_H_INCLUDED
#define PILHAEP2_H_INCLUDED

typedef struct{
    int linha;
    int coluna;
    int palavra;
    int direta_baixo; //direita 1 baixo 0
} posicao;

typedef posicao item;

typedef struct{
    item *v;
    int topo;
    int max;
} pilha;

void empilha(pilha *pil, item pos);
item desempilha(pilha *pil);
item topodapilha(pilha *pil);
int pilhavazia(pilha *pil);
void resize(pilha *pil);
pilha * cria();
void destroi(pilha *pil);

#endif // PILHAEP2_H_INCLUDED

typedef struct cel{
    char *palavra;
    int Linha;
    int Numero_de_ocorrencias;
    struct cel *esquerda;
    struct cel *direita;
    struct celula *proximo;
}no;

typedef struct celula{
    int Linha;
    int Numero_de_ocorrencias;
    struct celula *proximo;
}LL;


void printordem(no *raiz);
void printaLL(LL *Listliga);

LL *BuscaLl(LL *Listaliga, int linha);
LL *InsercaoLl(LL *Listaliga, int linha);

no *Insercao(no *raiz, char *palavra, int Linha);
no *Busca(no *raiz, char *palavra);


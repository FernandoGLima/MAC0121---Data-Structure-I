#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filadeprioridade.h"
#define MAX 256


void Heapsort(char **lista, int qntd_palavras, long long *comparacoes, long long *trocas){
    int m;
    char auxiliar[MAX];

    for(m=1; m<qntd_palavras; m++){
        constroiHeap(lista, m, comparacoes, trocas);
    }
    for(m=qntd_palavras; m>1; --m){
        strcpy(auxiliar, lista[1]);
        strcpy(lista[1], lista[m]);
        strcpy(lista[m], auxiliar);
        corrigeHeapDescendo(lista, m-1, comparacoes, trocas);
    }
}


int main()
{
    char filename[MAX], **lista;
    int i, qntd_palavras;
    long long comparacoes=0, trocas=0;
    FILE *arq;

    printf("Digite o nome do arquivo da lista de palavras:\n");
    scanf("%s", &filename);

    arq= fopen(filename, "r");
    if(arq==NULL){
        printf("Deu erro ao abrir o arquivo\n");
    }

    printf("Digite a quantidade de palavras:\n");
    scanf("%d", &qntd_palavras);

    lista= malloc((qntd_palavras+1)*sizeof(char*));

    for(i=0; i<=qntd_palavras; i++){
        lista[i]= malloc(10*sizeof(char));
    }

    strcpy(lista[0], filename);
    for(i=1; i<=qntd_palavras; i++){
        fscanf(arq, "%s", lista[i]);
    }

    /*for(i=1; i<=qntd_palavras; i++){
        printf("%s\n", lista[i]);
    }*/

    Heapsort(lista, qntd_palavras, &comparacoes, &trocas);

    /*for(i=1; i<=qntd_palavras; i++){
        printf("%s\n", lista[i]);
    }*/

    printf("Comparacoes: %lld\nTrocas: %lld", comparacoes, trocas);

    for(i=0; i<=qntd_palavras; i++){
        free(lista[i]);
    }

    free(lista);
    fclose(arq);

    return 0;

}

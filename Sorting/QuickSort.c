#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
long long comparacoes=0, trocas=0;

int separa(char **lista, int inicio, int fim){
    int j, k;
    char auxiliar[10], troca[10];

    strcpy(auxiliar, lista[fim]);
    j=inicio;
    for(k=inicio; k<fim; k++){
        comparacoes++;
        if(strcmp(lista[k], auxiliar)<0){
            strcpy(troca, lista[j]);
            strcpy(lista[j], lista[k]);
            strcpy(lista[k], troca);
            trocas++;
            j++;
        }
    }

    strcpy(lista[fim], lista[j]);
    strcpy(lista[j], auxiliar);

    return j;
}


void quicksort(char **lista, int inicio, int fim){
    int j;
    if(inicio<fim){
        j= separa(lista, inicio, fim);
        quicksort(lista, inicio, j-1);
        quicksort(lista, j+1, fim);
    }
}


int main()
{
    char filename[MAX], **lista;
    int qntd_palavras, i;
    FILE *arq;

    printf("Digite o nome do arquivo que contem a lista de palavras:\n");
    scanf("%s", &filename);

    arq= fopen(filename, "r");
    if(arq==NULL){
        printf("Deu erro ao abir o arquivo\n");
    }

    printf("Digite a quantidade de palavras:\n");
    scanf("%d", &qntd_palavras);

    lista= malloc(qntd_palavras*sizeof(char*));

    for(i=0; i<qntd_palavras; i++){
        lista[i]= malloc(10*sizeof(char));
    }

    for(i=0; i<qntd_palavras; i++){
        fscanf(arq, "%s", lista[i]);
    }

    /*for(i=0; i<qntd_palavras; i++){
        printf("%s\n", lista[i]);
    }*/

    quicksort(lista, 0, qntd_palavras-1);

    /*for(i=0; i<qntd_palavras; i++){
        printf("%s\n", lista[i]);
    }*/

    printf("Comparacoes: %lld\nTrocas: %lld", comparacoes, trocas);

    for(i=0; i<qntd_palavras; i++){
        free(lista[i]);
    }

    free(lista);
    fclose(arq);

    return 0;
}

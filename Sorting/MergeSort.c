#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
long long comparacoes=0, trocas=0;

void Intercala(char **lista, int inicio, int meio, int fim){
    int i=inicio, j=meio, k=0, cont;
    char **auxiliar;

    auxiliar= malloc((fim-inicio)*sizeof(char*));
    for(cont=0; cont<(fim-inicio); cont++){
        auxiliar[cont]= malloc(10*sizeof(char));
    }

    while(i<meio && j<fim){
        comparacoes++;
        if(strcmp(lista[i], lista[j])<=0){
            strcpy(auxiliar[k++], lista[i++]);
        }
        else{
            strcpy(auxiliar[k++], lista[j++]);
        }
    }
    while(i<meio){
        strcpy(auxiliar[k++], lista[i++]);
    }
    while(j<fim){
        strcpy(auxiliar[k++], lista[j++]);
    }

    for(i=inicio; i<fim; i++){
        strcpy(lista[i], auxiliar[i-inicio]);
        trocas++;
    }
    for(i=0; i<(fim-inicio); i++){
        free(auxiliar[i]);
    }
    free(auxiliar);
}


void Mergesort(char **lista, int inicio, int fim){
    if(inicio<fim-1){
        int meio = (inicio+fim)/2;
        Mergesort(lista, inicio, meio);
        Mergesort(lista, meio, fim);
        Intercala(lista, inicio, meio, fim);
    }
}


int main()
{
    char filename[MAX], **lista;
    int qntd_palavras, i;
    FILE *arq;

    printf("Digite o nome do arquivo que contem a lista de palavras:\n");
    scanf("%s", filename);

    arq= fopen(filename, "r");
    if(arq==NULL){
        printf("Deu erro ao abrir o arquivo\n");
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

    Mergesort(lista, 0, qntd_palavras);

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

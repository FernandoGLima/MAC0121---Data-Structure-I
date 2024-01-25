#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
long long comparacoes=0, trocas=0;

void insertion_sort(char **lista, int qntd_palavras){
    char auxiliar[10];
    int i, j;

    for(i=1; i<qntd_palavras; i++){
        strcpy(auxiliar, lista[i]);
        j=i-1;

        comparacoes++;
        while(j>=0 && (strcmp(lista[j], auxiliar)>0)){
            comparacoes++;
            strcpy(lista[j+1], lista[j]);
            trocas++;
            j--;
        }
        strcpy(lista[j+1], auxiliar);
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

 /*  for(i=0; i<qntd_palavras; i++){
        printf("%s\n", lista[i]);
    }*/

    insertion_sort(lista, qntd_palavras);

   /* for(i=0; i<qntd_palavras; i++){
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

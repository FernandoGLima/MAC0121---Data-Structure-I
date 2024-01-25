#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#define MAX 256

int main()
{
    char filename[MAX], word[MAX], c;
    int cont=0, linha=1, i;
    FILE *arq;
    no *aux=NULL, *raiz=NULL;
    LL *auxiliarLL=NULL;

    printf("Digite o nome do arquivo:\n");
    scanf("%s", filename);

    arq= fopen(filename, "r");
    if(arq==NULL){
        printf("Deu erro ao abrir o arquivo\n");
    }


  while ((c = fgetc(arq)) != EOF) {
    if((c>=65 && c<=90) || (c>=97 && c<=122)){
        word[cont]=c;
        cont++;
    }

    if (c == ' ') {
        if(word[0]!='\0'){
            aux=Busca(raiz, word);

            if(aux!=NULL){
                if(aux->Linha==linha){
                    aux->Numero_de_ocorrencias++;
                }
                else{
                    auxiliarLL= BuscaLl(aux->proximo, linha);
                    if(auxiliarLL!=NULL){
                        auxiliarLL->Numero_de_ocorrencias++;
                    }
                    else
                        aux->proximo= InsercaoLl(aux->proximo, linha);
                }
            }
            else
                raiz= Insercao(raiz, word, linha);

        }
        for(i=0; i<cont; i++){
            word[i]='\0';
        }
        cont=0;
    }
    if(c=='\n'){
        if(word[0]!='\0'){
            aux=Busca(raiz, word);

            if(aux!=NULL){
                if(aux->Linha==linha){
                    aux->Numero_de_ocorrencias++;
                }
                else{
                    auxiliarLL= BuscaLl(aux->proximo, linha);
                    if(auxiliarLL!=NULL){
                        auxiliarLL->Numero_de_ocorrencias++;
                    }
                    else{
                        aux->proximo= InsercaoLl(aux->proximo, linha);
                    }
                }
            }
            else
                raiz= Insercao(raiz, word, linha);

        }
        for(i=0; i<cont; i++){
            word[i]='\0';
        }
        cont=0;
        linha++;
    }
  }
    aux=Busca(raiz, word);              //Esta parte é para pegar a ultima palavra do arquivo.

            if(aux!=NULL){
                if(aux->Linha==linha){
                    aux->Numero_de_ocorrencias++;
                }
                else{
                    auxiliarLL= BuscaLl(aux->proximo, linha);
                    if(auxiliarLL!=NULL){
                        auxiliarLL->Numero_de_ocorrencias++;
                    }
                    else
                        aux->proximo= InsercaoLl(aux->proximo, linha);
                }
            }
            else
                raiz= Insercao(raiz, word, linha);




    printordem(raiz);

    return 0;
}

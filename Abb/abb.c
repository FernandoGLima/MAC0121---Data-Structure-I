#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

no *Busca(no *raiz, char *word){
    if(raiz==NULL || strcmp(raiz->palavra, word)==0){
        return raiz;
    }
    if(strcmp(word, raiz->palavra)<0){
        return Busca(raiz->esquerda, word);
    }
    else{
        return Busca(raiz->direita, word);
    }
}

LL *BuscaLl(LL *Listaliga, int linha){
    if(Listaliga==NULL || (Listaliga->Linha==linha)){
        return Listaliga;
    }
    else
        return BuscaLl(Listaliga->proximo, linha);
}

no *Insercao(no *raiz, char *word, int Lin){
    if(raiz==NULL){
        raiz= malloc(sizeof(no));
        raiz->palavra= malloc((strlen(word)+1)*sizeof(char));
        strcpy(raiz->palavra, word);
        raiz->Linha=Lin;
        raiz->Numero_de_ocorrencias=1;
        raiz->direita=raiz->esquerda=NULL;
        raiz->proximo=NULL;
        return raiz;
    }
    if(strcmp(word, raiz->palavra)<0){
        raiz->esquerda= Insercao(raiz->esquerda, word, Lin);
    }
    else if(strcmp(word, raiz->palavra)>0){
        raiz->direita= Insercao(raiz->direita, word, Lin);
    }
    return raiz;
}


LL *InsercaoLl(LL *Listaliga, int linha){
    if(Listaliga==NULL){
        Listaliga= malloc(sizeof(LL));
        Listaliga->Linha=linha;
        Listaliga->Numero_de_ocorrencias=1;
        Listaliga->proximo=NULL;
    }
    else
        Listaliga->proximo= InsercaoLl(Listaliga->proximo, linha);
}


void printordem(no *raiz){
    if(raiz!=NULL){
        printordem(raiz->esquerda);
        printf("%s : Linha = %d - vezes = %d //", raiz->palavra, raiz->Linha, raiz->Numero_de_ocorrencias);
        if(raiz->proximo!=NULL){
            printaLL(raiz->proximo);
        }
        printf("\n");
        printordem(raiz->direita);
    }
}

void printaLL(LL *Listaliga){
    printf(" Linha = %d - vezes = %d //", Listaliga->Linha, Listaliga->Numero_de_ocorrencias);
    LL *aux;
    aux=Listaliga->proximo;
    while(aux!=NULL){
        printf(" Linha = %d - vezes = %d //", aux->Linha, aux->Numero_de_ocorrencias);
        aux=aux->proximo;
    }
}

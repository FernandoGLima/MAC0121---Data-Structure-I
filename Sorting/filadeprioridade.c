#include <stdlib.h>
#include <stdio.h>
#include "filadeprioridade.h"
#define MAX 256

void constroiHeap(char **lista, int m, long long *comparacoes, long long *trocas){
    int f=m+1;
    char auxiliar[MAX];

    (*comparacoes)++;
    while(f>1 && strcmp(lista[f/2], lista[f])<0){
        (*comparacoes)++;
        strcpy(auxiliar, lista[f/2]);
        strcpy(lista[f/2], lista[f]);
        strcpy(lista[f], auxiliar);
        (*trocas)++;
        f=f/2;
    }
}


void corrigeHeapDescendo(char **lista, int m, long long *comparacoes, long long *trocas){
    int f=2;
    char auxiliar[MAX];

    while(f<=m){
        (*comparacoes)++;
        if(f<m && strcmp(lista[f], lista[f+1])<0){
            ++f;
        }
        (*comparacoes)++;
        if(strcmp(lista[f/2], lista[f])>=0){
            break;
        }
        strcpy(auxiliar, lista[f/2]);
        strcpy(lista[f/2], lista[f]);
        strcpy(lista[f], auxiliar);
        (*trocas)++;
        f*=2;
    }
}

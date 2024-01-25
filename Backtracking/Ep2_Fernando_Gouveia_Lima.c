#include <stdio.h>
#include <stdlib.h>
#include "pilhaep2.h"

/*------------------------Pilha C----------------------------------*/
pilha * cria(){
    pilha *pil= malloc(sizeof(pilha));
    pil->max=1;
    pil->topo=0;
    pil->v= malloc(pil->max * sizeof(item));

    if(pil->v==NULL){
        return NULL;
    }
    return pil;
}

int pilhavazia(pilha *pil){
    return (pil->topo==0);
}

void empilha(pilha *pil, item pos){
    if(pil->topo==pil->max){
        resize(pil);
    }
    pil->v[pil->topo]= pos;
    pil->topo++;
}

item desempilha(pilha *pil){
    if(!pilhavazia(pil)){
        pil->topo--;
        return(pil->v[pil->topo]);
    }
}

void destroi(pilha *pil){
    free(pil->v);
    free(pil);
}

void resize(pilha *pil){
    int i;
    item * z= malloc(2* pil->max * sizeof(item));
    for(i=0; i< pil->max; i++){
        z[i]=pil->v[i];
    }
    pil->max = 2 * pil->max;
    free(pil->v);
    pil->v=z;
}

item topodapilha(pilha *pil){
    if(!pilhavazia(pil)){
        return (pil->v[pil->topo-1]);
    }
}

/*---------Aloca / Printa / Le a matriz das palavras cruzadas------*/

int Aloca_Matriz(char *V, int m, int n){
    V= malloc(m*n*sizeof(char));
    if (V==NULL){
        printf("Deu erro na alocacao de memoria");
    }
return V;
}

void Le_Matriz(char *V, int m, int n){
    int i, j;

    printf("Digite a matriz:\n");
    for(i=0; i<m*n; i++){
        scanf("%c", &V[i]);
        if(V[i]=='\n'){
            i--;
            if((i+1)==(m*n)){
                i++;
            }
        }
        else if(V[i]=='1'){
            i--;
        }
    }
}


void Imprimi_Matriz(char *V, int m, int n){
    int i, j;

    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("%c ", V[i*n+j]);
        }
    printf("\n");
    }
}

/*------------------------------------------------------------------------*/


int Conta_caracter(char lista[][100]){
    int i, tamanho=0;

    for(i=0; lista[0][i]!='\0'; i++){                   //conta o tamanho da palavra
        tamanho++;
    }
    return tamanho;
}


int Conta_linha_direita(char *V, int n, posicao atual){
    int j, tamanho=0;

    if(V[atual.linha*n+atual.coluna-1]!='-' && (atual.coluna)!=0){          //conta as linhas pra direita, somente em posicao valida, ou seja, se antes for a borda ou um -1.
        tamanho=0;
    }
    else{
        for(j=atual.coluna; j<n && V[atual.linha*n+j]!='-'; j++){
            tamanho++;
        }
    }
    return tamanho;
}


int Conta_linha_baixo(char *V, int m, int n, posicao atual){
    int i, tamanho=0;

    if(V[(atual.linha-1)*n+atual.coluna]!='-' && (atual.linha)!=0){             //conta as linhas pra baixo, somente em posicao valida, ou seja, se antes for a borda ou um -1.
        tamanho=0;
    }
    else{
        for(i=atual.linha; i<m && V[i*n+atual.coluna]!='-'; i++){
            tamanho++;
        }
    }
    return tamanho;
}


int Verifica_espaco_cruzado(char *V, char **lista, int m, int n, posicao atual, int p, pilha *pil){
    int i, j, x, y, flag=1, cont1, cont2, cabe=1, tamanho_palavra, verifica_palavra=0, volta, salva_coluna, salva_linha, salva_direita_baixo, salva_palavra;

    if(atual.direta_baixo==0){
        for(j=atual.coluna; j<n && V[atual.linha*n+j]!='-'; j++){           //vou andar o espaço dessa palavra que eu quero colocar
            for(x=atual.linha; x>=0 && V[x*n+j]!='-'; x--){
                if(V[x*n+j]=='0'){
                    flag=0;
                }                                                              //se tiver um 0 na posicao cruzada dessa letra eu sigo em frente
            }
            for(y=atual.linha; y<m && V[y*n+j]!='-'; y++){
                if(V[y*n+j]=='0'){
                    flag=0;
                }
            }
            if(flag==1){
                cabe=0;                                                     //se so tiver letras eu tenho que verificar se essa palavra que eu quero colocar cabe ali ou seja se a palavra cruzada a essa letra existe na lista
                x++;
                volta=x;
                tamanho_palavra=y-x;
                for(cont1=0; cont1<p; cont1++){
                    for(cont2=0; lista[cont1][cont2]!='\0'; cont2++){           //verifico se a palavra existe na lista
                        if(V[x*n+j]==lista[cont1][cont2]){
                                verifica_palavra++;

                        }
                        if(tamanho_palavra==verifica_palavra){
                            cabe=1;
                            salva_linha=atual.linha; salva_coluna=atual.coluna;
                            salva_direita_baixo=atual.direta_baixo; salva_palavra=atual.palavra;        //se sim eu ja empilho essa palavra cruzada na pilha

                            atual.linha=volta;
                            atual.coluna=j;
                            atual.direta_baixo=1;
                            atual.palavra=cont1;
                            empilha(pil, atual);
                            x=volta;
                            for(cont2=0; lista[cont1][cont2]!='\0'; cont2++){
                                V[x*n+j]=lista[cont1][cont2];
                                x++;
                            }

                            atual.linha=salva_linha; atual.coluna=salva_coluna;
                            atual.direta_baixo=salva_direita_baixo; atual.palavra=salva_palavra;
                        }
                        x++;
                    }
                    x=volta;
                    verifica_palavra=0;
                }
                if(cabe==0){                                                            //se nao, eu falo que nao coube
                    goto fim_nao_coube;
                }
            }
            flag=1;
        }
    }

    else{
        for(i=atual.linha; i<m && V[i*n+atual.coluna]!='-'; i++){
            for(x=atual.coluna; x>=0 && V[i*n+x]!='-'; x--){
                if(V[i*n+x]=='0'){
                    flag=0;
                }
            }
            for(y=atual.coluna; y<n && V[i*n+y]!='-'; y++){
                if(V[i*n+y]=='0'){
                    flag=0;
                }
            }
            if(flag==1){
                cabe=0;
                x++;
                volta=x;
                tamanho_palavra=y-x;
                for(cont1=0; cont1<p; cont1++){
                    for(cont2=0; lista[cont1][cont2]!='\0'; cont2++){
                        if(V[i*n+x]==lista[cont1][cont2]){
                            verifica_palavra++;
                        }
                        if(tamanho_palavra==verifica_palavra){
                            cabe=1;
                            salva_linha=atual.linha; salva_coluna=atual.coluna;
                            salva_direita_baixo=atual.direta_baixo; salva_palavra=atual.palavra;

                            atual.linha=i;
                            atual.coluna=volta;
                            atual.direta_baixo=0;
                            atual.palavra=cont1;
                            empilha(pil, atual);
                            x=volta;
                            for(cont2=0; lista[cont1][cont2]!='\0'; cont2++){
                                V[i*n+x]=lista[cont1][cont2];
                                x++;
                            }

                            atual.linha=salva_linha; atual.coluna=salva_coluna;
                            atual.direta_baixo=salva_direita_baixo; atual.palavra=salva_palavra;
                        }
                        x++;
                    }
                    x=volta;
                    verifica_palavra=0;
                }
                if(cabe==0){
                    goto fim_nao_coube;
                }
            }
            flag=1;
        }
    }
    fim_nao_coube:
        return cabe;
}


int Verifica_espaco(char *V, char **lista, int m, int n, posicao atual, int p, pilha *pil){
    int i=0, j=0, cabe=1;

    if(atual.direta_baixo==0){
        for(j=atual.coluna; j<n && V[atual.linha*n+j]!='-' ; j++){
            if(V[atual.linha*n+j]!='0' && V[atual.linha*n+j]!=lista[atual.palavra][i]){         //verifico se no espaco nao tem 0 ou uma letra igual minha palavra
                cabe=0;
                goto sai_laco_nao_cabe;                                                         //se nao tiver quer dizer que nao cabe
            }
            if(V[atual.linha*n+j]=='0'){
                cabe=Verifica_espaco_cruzado(V, lista, m, n, atual, p, pil);                    //se tiver 0 vou verificar o espaco cruzado dessa palavra para nao encaixar uma errada
            }
            i++;
        }
        if(cabe==1){
            i=0;
            for(j=atual.coluna; lista[atual.palavra][i]!='\0'; j++){                        //se couber eu adiciono essa palavra la
                V[atual.linha*n+j]=lista[atual.palavra][i];
                i++;
            }
        }
    }
    else{
        for(i=atual.linha; i<m && V[i*n+atual.coluna]!='-'; i++){
            if(V[i*n+atual.coluna]!='0' && V[i*n+atual.coluna]!=lista[atual.palavra][j]){               //mesma coisa para a palavra em pe
                cabe=0;
                goto sai_laco_nao_cabe;
            }
            if(V[i*n+atual.coluna]=='0'){
                cabe=Verifica_espaco_cruzado(V, lista, m, n, atual, p , pil);
            }
            j++;
        }
        if(cabe==1){
            j=0;
            for(i=atual.linha; lista[atual.palavra][j]!='\0'; i++){
                V[i*n+atual.coluna]=lista[atual.palavra][j];
                j++;
            }
        }
    }
sai_laco_nao_cabe:
    return cabe;
}


void desempilhou_volta_0(char *V, int m, int n, posicao atual){
    int i, j, x, y, flag=1;

    if(atual.direta_baixo==0){
        for(j=atual.coluna; j<n && V[atual.linha*n+j]!='-'; j++){
            for(x=atual.linha; x>=0 && V[x*n+j]!='-'; x--){
                if(V[x*n+j]=='0'){                                      //na hora de desempilhar eu verifico se existe uma palavra cruzada a alguma letra que eu quero desempilha
                    flag=0;
                }                                                       //se sim, entao eu deixo a letra la, se nao eu desempilho e coloco um zero no local.
            }
            for(y=atual.linha; y<m && V[y*n+j]!='-'; y++){
                if(V[y*n+j]=='0'){
                    flag=0;
                }
            }
            if(flag==0){
                V[atual.linha*n+j]=='0';
            }
            flag=1;
        }
    }
    else{
        for(i=atual.linha; i<m && V[i*n+atual.coluna]!='-'; i++){
            for(x=atual.coluna; x>=0 && V[i*n+x]!='-'; x--){
                if(V[i*n+x]=='0'){
                    flag=0;
                }
            }
            for(y=atual.coluna; y<n && V[i*n+y]!='-'; y++){
                if(V[i*n+y]=='0'){
                    flag=0;
                }
            }
            if(flag==0){
                V[i*n+atual.coluna]='0';
            }
            flag=1;
        }
    }
}

void palavras_cruzadas(char *V, int m, int n){
    int p, i, tam_caracter, tam_espaco, flag_cabe, cont;             //dicionario: p - quantidade de palavras, i-contador,
    pilha *pil= cria();                                              // tam_caracter - tamanho da palavra, tam_espaco - tamanho de ume espaco na matriz
    posicao atual;                                                   //flag_cabe - para saber se cabe e empilhar a palavra

    printf("Digite a quantidade de palavras:\n");
    scanf("%d", &p);
    while(p==1){
        printf("Digite a quantidade de palavras:\n");
        scanf("%d", &p);
    }
    char **lista= malloc(p * sizeof(char*));
    printf("Digite as palavras:\n");                                // pega a lista de palavras
    for(i=0; i<p; i++){
        lista[i]= malloc(20 * sizeof(char));
        scanf("%s", lista[i]);
    }

    atual.linha=0;                                                // essas 2 primeiras variaveis vao percorrer a matriz toda
    atual.coluna=0;                                               // enquanto a segunda vai percorrer a lista de palavras
    atual.palavra=0;

    while(atual.palavra<p){                                       // enquanto nao percorrer todas as palavras faca isso
        tam_caracter=Conta_caracter(lista[atual.palavra]);         // pega o tamanho da primeira palavra
        while(atual.linha<m){                                       // as variaveis comecam a percorrer a matriz em busca de um
            while(atual.coluna<n){                                  //espaco igual o da palavra
                tam_espaco=Conta_linha_direita(V, n, atual);        //conta o tamanho do espaco para direita
                if(tam_caracter==tam_espaco){                          //se sao iguais eu vou verificar o espaço
                        atual.direta_baixo=0;
                        flag_cabe=Verifica_espaco(V, lista, m, n, atual, p, pil);
                        if(flag_cabe==1){
                            empilha(pil, atual);                        // se o couber no espaço empilha e vai pra proxima palavra
                            goto proxima_palavra;
                        }

                }
            testa_baixo_agr:
                tam_espaco=Conta_linha_baixo(V, m, n, atual);           // conta o tamanho do espaço para baixo
                if(tam_caracter==tam_espaco){
                        atual.direta_baixo=1;
                        flag_cabe=Verifica_espaco(V, lista, m, n, atual, p, pil);       //vou verifcar o espaço
                        if(flag_cabe==1){
                            empilha(pil, atual);                        // se couber, eu empilho a palavra, posicao e se ele esta deitada ou em pe e vou para a proxima
                            goto proxima_palavra;
                        }
                }
            testa_proxima_pos:
                atual.coluna++;                                         //incremento a coluna
            }
            atual.coluna=0;
            atual.linha++;                                                  //incremento a linha
        }

        proxima_palavra:

            atual.linha=0;
            atual.coluna=0;                                                 //vou verificar a outra palavra se cabe em algum espaço
            atual.palavra++;

        if(atual.palavra==p && !pilhavazia(pil)){                             //se for a ultima palavra e a pilha estiver cheia
            for(cont=0; cont<m*n; cont++){                                  //vou verificar se tem algum 0 na matriz
                if(V[cont]=='0'){
                    atual= desempilha(pil);
                    desempilhou_volta_0(V, m, n, atual);                        //se tiver eu desempilho e mando continua de onde parou
                    if(atual.direta_baixo==0){
                        tam_caracter=Conta_caracter(lista[atual.palavra]);     //se a palavra estava deitada mando testar ela em pe
                        goto testa_baixo_agr;
                    }
                    else{
                        tam_caracter=Conta_caracter(lista[atual.palavra]);
                        goto testa_proxima_pos;
                    }
                }
            }
            Imprimi_Matriz(V, m, n);
            free(V);                                                        //se nao tiver nenhum 0 na matriz, esta e a correta imprime ela
            destroi(pil);
            for(i=0; i<p; i++){
                free(lista[i]);
            }
            goto fim;
        }
        else if(atual.palavra==p && pilhavazia(pil)){
            printf("Esta instancia nao tem solucao!!\n");
            free(V);
            destroi(pil);                                                 //se a palavra for a ultima e a pilha estiver vazia nao tem solucao
            for(i=0; i<p; i++){
                free(lista[i]);
            }
            goto fim;
        }
    }

    fim:
        printf("\n");
}

int main()
{
    int i, m=1, n=1;
    char *V;

    printf("Digite as linhas e colunas da sua matriz:\n");
    scanf("%d %d", &m, &n);
    while(m!=0 && n!=0 ){
        V=Aloca_Matriz(V, m, n);
        Le_Matriz(V, m, n);

        palavras_cruzadas(V, m, n);

        printf("Digite as linhas e colunas da sua matriz:\n");
        scanf("%d %d", &m, &n);
    }

return 0;
}

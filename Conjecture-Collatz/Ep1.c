#include <stdio.h>
#include <stdlib.h>

int main()
{
    double *i, *f, *n;
    int passos=0;

    i=malloc(sizeof(double)*10);
    if(i==NULL){
        printf("Deu erro a alocacao\n");
    }
    f=malloc(sizeof(double)*10);
    if(f==NULL){
        printf("Deu erro a alocacao\n");
    }
    n=malloc(sizeof(double)*10);
    if(n==NULL){
        printf("Deu erro a alocacao\n");
    }

    printf("digite os intervalos:\n");
    scanf("%lf %lf", &(*i), &(*f));


    while((*i)!=(*f)+1){
      *n=*i;

        while(*n>1){
                if((int)*n%2==0){
                    *n=*n/2;
                    passos++;
                    if(*n==1){
                        goto jump;
                    }
                }
                else{
                    *n=3*(*n)+1;
                    passos++;
                }
        }
jump:
        printf("o numero: %.0lf teve %d passos\n", (*i), passos);
        passos=0;
        *i=*i+1;
    }

    free(i);
    free(n);
    free(f);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Marca{
    int minl;
    int maxc;
    int num;
} Marca;

void pVet(Int *v, int n){
    int i;
    printf("{%d", v[0].num);
    for(i = 1; i < n; i++){
        printf(" %d", v[i].num);
    }
    printf("}\n");
}
void pMat(Int m[][MAX], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%2d ", m[i][j].num);
        }
        printf("\n");
    }
}
int main(){
    int in[MAX][MAX];
    Marca aux[MAX][MAX];
    int n, i, j, k, sela = 0;
    char lixo[52];

    scanf("%d", &n);
    fgets(lixo, 50, stdin);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            /*leitura da quantidade de linhas, coluna e da in.*/
            if(scanf("%d", &in[i][j]) != EOF){
            }else{
                return 0;
            }
        }
        fgets(lixo, 50, stdin);
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            aux[i][j].num = 0;
        }
    }
    
    /* Imprime a saída. */
    
    printf("Os pontos de sela da matriz são:\n\n");

    if(sela){
        for(i = 0; i < k; i++){
            printf("%4d%4d%4d\n",resp[i].pos.i, resp[i].pos.j, resp[i].num);
        }
    }
    else{
        printf("nenhum\n");
    }

    return 0;
}
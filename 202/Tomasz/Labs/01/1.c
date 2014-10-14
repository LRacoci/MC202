#include <stdio.h>

#define MAX 50

typedef struct Pos {
    int i;
    int j;
} Pos;

typedef struct Int {
    int num;
    Pos pos;
} Int;
void pVet(int *v, int n){
    int i;
    printf("{%d", v[0])
    for(i = 1; i < n; i++){
        printf(" %d", v[i]);
    }
    printf("}\n");
}
void pMat(Int m[][MAX], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%2d ", m.num[i][j]);
        }
        prinf("\n");
    }
}
int main(){
    Int in[MAX][MAX], minL[MAX], maxC[MAX], resp[MAX];
    int n, i, j, k, sela = 0;

    scanf("%d", &n);

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        /*leitura da quantidade de linhas, coluna e da in.*/
        scanf("%d", &in[i][j].num);
        in[i][j].pos.i = i;
        in[i][j].pos.j = j;

    /*Inicializa minL com os elementos da primeira coluna da matriz*/
    for(i=0; i < n; i++)
        minL[i] = in[i][0];


    /* O programa acha o menor da linha. */
    for(i=0; i < n; i++){
        for(j = 0; j < n-1; j++){
            if(in[i][j+1].num < in[i][j].num){
                minL[i] = in[i][j+1];
            }
        }
    } 
    /*Inicializa maxC com os elementos da primeira linha da matriz*/
    for(j=0; j<n; j++)
        maxC[j] = in[0][j];

    /*O programa acha o maior da coluna.*/
    for(j=0; j<n; j++){
        for(i=0; i<n-1; i++){
            if(in[i+1][j].num>in[i][j].num)
                maxC[j] = in[i+1][j];

        }
    } 

    /*Vê se o mínimo da linha é igual ao máximo da coluna*/
    k = 0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(minL[i].num == maxC[j].num && 
               minL[i].pos.j == maxC[j].pos.j){
                resp[k++] = minL[i];
                sela = 1;
            }
        }
    } 
    /* Imprime a saída. */
    if(sela){
        for(i = 0; i < k; i++){
            printf("%4d %4d %4d\n", resp[k].num, resp[k].pos.i, resp[k].pos.j);
        }
    }
    else{
        printf("Nao existe um ponto de sela.\n");
    }

    return 0;
}
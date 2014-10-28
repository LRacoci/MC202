/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 06 - Pré, In e Pós */

#include <stdio.h>
#include <stdlib.h>


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true, head} bool;

typedef struct Arvore{
	char info;
	struct Arvore *esq, *dir;
} No, *Arvore;

/* TAD: Arvores */
/***************/
Arvore monta_arvore(char *pre, int pre_inicio, char *in, int in_inicio, int n);
void liberaArvore(Arvore A);

void imprime_pos(Arvore A);



/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int C, i, N;
	char *pre, *in;
	Arvore A = NULL;
	scanf("%d", &C);
	for (i = 0; i < C; i++){
		scanf("%d", &N);
		pre = (char*) malloc((N + 1) * sizeof(char));
		in  = (char*) malloc((N + 1) * sizeof(char));
		scanf ("%s %s\n", pre, in);
		A = monta_arvore(pre, 0, in, 0, N);
		free(pre); free(in);
		imprime_pos(A);
		liberaArvore(A);
		printf("\n");
	}

	return 0; 
} 
/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/
/***************************************/


/* Monta a arvore usando descrição in-ordem e pré-ordem */
Arvore monta_arvore(char *pre, int pre_inicio, char *in, int in_inicio, int n){
	int i;
	Arvore A;
	if(n <= 0){
		return NULL;
	}

	A = (Arvore)malloc(sizeof(No));
	A->info = pre[pre_inicio];

	for(i = 0; i < n && in[i + in_inicio] != pre[pre_inicio]; i++);

	A->esq = monta_arvore(pre,  pre_inicio + 1 , in, in_inicio, i);
	A->dir = monta_arvore(pre, pre_inicio+i+1, in, in_inicio+i+1, n-i-1);
	return A;

}
/* Libera tudo q foi alocado */
void liberaArvore(Arvore A){
	if(A){
		liberaArvore(A->dir);
		liberaArvore(A->esq);
		free(A);
	}
}
/* Imprime a arvore em pos ordem */
void imprime_pos(Arvore A){
	if(A){
		imprime_pos (A->esq);
		imprime_pos (A->dir);
		printf("%c", A->info);
	}
}
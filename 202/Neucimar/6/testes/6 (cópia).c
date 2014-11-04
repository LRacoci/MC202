/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 06 - Pré, In e Pós */

#include <stdio.h>
#include <stdlib.h>


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/
/************************************************************/

typedef enum bool{false, true} bool;

typedef struct Arvore{
	char info;
	struct Arvore *esq, *dir;
} No, *Arvore;

/* TAD: Arvores */
/***************/
Arvore cria_arvore(char *pre, int pre_inicio, char *in, int in_inicio, int n);
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
		/* Le o tamnho das strings */
		scanf("%d", &N);
		/* Cria as duas strings */
		pre = (char*) malloc((N + 1) * sizeof(char));
		in  = (char*) malloc((N + 1) * sizeof(char));
		/* Le as duas strings */
		scanf ("%s %s\n", pre, in);
		/* Monta a árvore recursivamente */
		A = cria_arvore(pre, 0, in, 0, N);
		/* Libera as duas strings */
		free(pre); free(in);
		/* Imprime em pós-ordem */
		imprime_pos(A);
		/* Desaloca tudo que foi alocado */
		liberaArvore(A);
		printf("\n");
	}

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: Arvores*/ 
/**************/

/* Cria e monta a arvore usando descrição in-ordem e pré-ordem */
Arvore cria_arvore(char *pre, int pre_inicio, char *in, int in_inicio, int n){
	int i;
	Arvore A;
	/* Criar uma árvore com 0 elementos apenas retorna NULL */
	if(n <= 0){
		return NULL;
	}
	/* Cria nó da Arvore a ser retornado */
	A = (Arvore)malloc(sizeof(No));
	A->info = pre[pre_inicio];

	/* Acha a raiz na in-ordem e conta o tamanho da primeira subarvore em i*/
	for(i = 0; i < n && in[i + in_inicio] != pre[pre_inicio]; i++);

	/* Chama a recursão mandando pra árvore esquerda strings de tamanho i 
	 * sendo que a string pre começa uma posição depois depois da raiz, que
	 * ficava na primeira posição e sting in, começa na primeira posição */
	A->esq = cria_arvore(pre,  pre_inicio + 1 , in, in_inicio, i);
	/* Cahma a recursão mandando pra árvore direita strings com o resto
	 * do tamanho da string original sem a raiz e com as posições de onde
	 * começam as representações das subarvores esquerdas nas strings */
	A->dir = cria_arvore(pre, pre_inicio+i+1, in, in_inicio+i+1, n-i-1);
	return A;

}
/* Libera tudo que foi alocado em pós-ordem */
void liberaArvore(Arvore A){
	if(A){
		liberaArvore(A->dir);
		liberaArvore(A->esq);
		free(A);
	}
}
/* Imprime a arvore em pos-ordem */
void imprime_pos(Arvore A){
	if(A){
		imprime_pos (A->esq);
		imprime_pos (A->dir);
		printf("%c", A->info);
	}
}
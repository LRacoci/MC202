/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 08 - Menor Ancestral Comum */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true} bool;

typedef struct Lista NoLista, *Lista;
typedef struct Arvore NoArvore, *Arvore, **Floresta;

struct Arvore{
	int info;
	int grau;
	Arvore pai;
	Lista filhos;
};
struct Lista{
	Arvore arv;
	Lista prox, ant;
};


/* TAD: Arvores Gerais */
/**********************/

Arvore cria_arvore(int chave);
void link(Arvore A, Arvore B);
void cut(Arvore A);
void lca(Arvore A, Arvore B);

/* Funções de Debugar */
void spaces(int n);
void pArv_aux(Arvore A, int i);
void pArv(Arvore A, char *str);
void confere_arvore(Arvore A, char *str);
Arvore raiz(NoArvore* p);	

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

Floresta inicializa_floresta(int n);

void operacao(Floresta in);


/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int i, n, m;
	Floresta entrada;
	scanf("%d %d", &n, &m);
	entrada = inicializa_floresta(n);
	for(i = 0; i < m; i++){
		operacao(entrada);
	}
	

	return 0;
} 

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

Floresta inicializa_floresta(int n){
	int i;
	Floresta nova = (Floresta) malloc(n * sizeof(Arvore));
	for (i = 0; i < n; i++){
		nova[i] = cria_arvore(i+1);
	}
	return nova;
}

void operacao(Floresta in){
	int a, b;
	char str[MAX];
	scanf("%s", str);
	if(strcmp(str, "cut") == 0){
		scanf("%d", &a);
		cut(in[a-1]);
	}else if(strcmp(str, "link") == 0){
		scanf("%d %d", &a, &b);
		link(in[a-1], in[b-1]);
	}else if(strcmp(str, "lca") == 0){
		scanf("%d %d", &a, &b);
		lca(in[a-1], in[b-1]);
	}
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: Arvores Gerais */
/**********************/

Arvore cria_arvore(int chave){
	Arvore nova = (Arvore)malloc(sizeof(NoArvore));
	nova->info = chave;
	nova->grau = 0;
	nova->pai = NULL;
	nova->filhos = (Lista)malloc(sizeof(NoLista));
	nova->filhos->prox = nova->filhos;
	nova->filhos->ant =  nova->filhos;
	nova->filhos->arv = NULL;
	return nova;
}
void link(Arvore A, Arvore B){
	Lista novo;
	A->pai = B;

	B->grau++;
	novo = (Lista)malloc(sizeof(NoLista));
	novo->ant = B->filhos->ant;
	novo->prox = B->filhos;
	novo->arv = A;
	B->filhos->ant->prox = novo;
	B->filhos->ant = novo;
}
void cut(Arvore A){
	Lista p;
	for(p = A->pai->filhos->prox; p->arv != NULL; p = p->prox){
		if(p->arv == A){
			A->pai->grau--;
			p->ant->prox = p->prox;
			p->prox->ant = p->ant;
			free(p);
			A->pai = NULL;
			return;
		}
	}
}
void lca(Arvore A, Arvore B){
	Arvore auxA, auxB;
	pArv(A, "A");
	for(auxA = A; auxA != NULL; auxA = auxA->pai){
		for(auxB = B; auxB != NULL; auxB = auxB->pai){
			if(auxA == auxB)
				printf("%d\n", auxA->info);
		}
	}
}

/* Funções de Debugar */
void spaces(int n){
	while(n > 0){
		printf("  ");
		n--;
	}
}
void pArv_aux(Arvore A, int i){
	Lista p;
	if(A == NULL){
		return;
	}
	spaces(i); 
	printf("%d\n", A->info);
	for(p = A->filhos->prox; p != NULL; p = p->prox){
		pArv_aux(p->arv, i + 1);
	}
}
void pArv(Arvore A, char *str){
	printf("\033[92m%s\033[97m\n",str);
	printf("(%d)->raiz = ", A->info);
	while(A->pai != NULL) A = A->pai;
	printf("%d\n", A->info);
	pArv_aux(A, 0);
}
void confere_arvore(Arvore A, char *str);
Arvore raiz(NoArvore* p);	


/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/
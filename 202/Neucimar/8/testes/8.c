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


/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

void cria_arvore(int chave){
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
	for(auxA = A; auxA != NULL; auxA = auxA->pai){
		for(auxB = B; auxB != NULL; auxB = auxB->pai){
			if(auxA == auxB)
				printf("%d\n", auxA->info);
		}
	}
}

/* Funções de Debugar */
void pArv(Arvore A);
void pPre(Arvore A);
void pIn(Arvore A);
void confere_arvore(Arvore A, char *str);
Arvore raiz(NoArvBin* p);	

/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

Floresta inicializa_floresta(int n){
	int i;
	Floresta nova = (Floresta) malloc(sizeof(n * Arvore));
	for (i = 1; i <= n, i++){
		v[i] = cria_arvore();
	}
}

void operacao(Floresta in){
	int a, b;
	char str[MAX];
	scanf("%s %d %d", str, &a, &b);
	a--; b--;
	if(strcmp(str, "lca") == 0){
		lca(in[a], in[b]);
	}


}


/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int i, n, m;
	Floresta entrada;
	scanf("%d %d", n, m);
	entrada = inicializa_floresta(n);
	for(i = 0; i < m; i++){
		operacao(Floresta, n);
	}
	

	return 0;
} 

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/


/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/
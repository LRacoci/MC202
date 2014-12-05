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

/* Define estruturas de lista e árvore */
typedef struct Lista NoLista, *Lista;
typedef struct Arvore NoArvore, *Arvore, **Floresta;

/* Cada nó da árvore tem: ... */
struct Arvore{
	/* ... Informação inteira */ 
	int info;
	/* ... Ponteiro para o pai */
	Arvore pai;
	/* ... Uma lista de filhos */
	Lista filhos;
};
/* Uso uma lista duplamente ligada circular com no cabeça
 * cuja informação é uma árvore */
struct Lista{
	Arvore arv;
	Lista prox, ant;
};


/* TAD: Arvores Gerais */
/**********************/

Floresta inicializa_floresta(int n);
void libera_floresta(Floresta X, int n);

/* Cria árvore geral */
Arvore cria_arvore(int chave);

/* Realiza as 3 operações definidas no enunciado */
void link(Arvore A, Arvore B);
void cut(Arvore A);
void lca(Arvore A, Arvore B);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

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
	libera_floresta(entrada, n);
	

	return 0;
} 

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/* Resolve operações da entrada */
void operacao(Floresta in){
	int a, b;
	char op[MAX];
	scanf("%s", op);
	if(strcmp(op, "cut") == 0){
		scanf("%d", &a);
		/* Acessa a posição correspondente no vetor */
		cut(in[a-1]);
	}else if(strcmp(op, "link") == 0){
		scanf("%d %d", &a, &b);
		link(in[a-1], in[b-1]);
	}else if(strcmp(op, "lca") == 0){
		scanf("%d %d", &a, &b);
		lca(in[a-1], in[b-1]);
	}
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: Arvores Gerais */
/**********************/

/* Inicializa um vetor de árvores e cria uma árvore pra cada posição */
Floresta inicializa_floresta(int n){
	int i;
	Floresta nova = (Floresta) malloc(n * sizeof(Arvore));
	for (i = 0; i < n; i++){
		nova[i] = cria_arvore(i+1);
	}
	return nova;
}
/* Libera todas as árvores do vetor de árvores alocadas */
void libera_floresta(Floresta X, int n){
	int i;
	Lista p, aux;
	for(i = 0; i < n; i++){
		for(p = X[i]->filhos->prox; p->arv != NULL; p = aux){
			aux = p->prox;
			free(p);
		}
		free(p);
		free(X[i]);
	}
	free(X);
}
/* Cria um no de arvore e o no cabeça da lista de filhos */
Arvore cria_arvore(int chave){
	Arvore nova = (Arvore)malloc(sizeof(NoArvore));
	nova->info = chave;
	nova->pai = NULL;
	/* A profundidade de uma arvore de um único nó é 1 */
	nova->filhos = (Lista)malloc(sizeof(NoLista));
	nova->filhos->prox = nova->filhos;
	nova->filhos->ant =  nova->filhos;
	nova->filhos->arv = NULL;
	return nova;
}
/* Faz de B pai de A e de A filho de B */
void link(Arvore A, Arvore B){
	Lista novo;
	A->pai = B;
	novo = (Lista)malloc(sizeof(NoLista));
	novo->ant = B->filhos->ant;
	novo->prox = B->filhos;
	novo->arv = A;
	B->filhos->ant->prox = novo;
	B->filhos->ant = novo;
}
/* Retira as referências criadas na função anteriror e desaloca o nó
 * na lista de filhos do pai de A que guardava o A */
void cut(Arvore A){
	Lista p;
	for(p = A->pai->filhos->prox; p->arv != NULL; p = p->prox){
		if(p->arv == A){
			p->ant->prox = p->prox;
			p->prox->ant = p->ant;
			free(p);
			A->pai = NULL;
			return;
		}
	}
}
/* Acha o ultimo ancestral comum que é ascendente de A e B ao mesmo tempo */
void lca(Arvore A, Arvore B){
	Arvore auxA = A, auxB = B;
	int profundidade_A = 0, profundidade_B = 0;
	/*Calcula a profundidade de A e B*/
	while(auxA){
		auxA = auxA->pai;
		profundidade_A++;
	}
	while(auxB){
		auxB = auxB->pai;
		profundidade_B++;
	}
	/* Iguala as duas profundidades */
	auxA = A; auxB = B;
	while(profundidade_B > profundidade_A){
		auxB = auxB->pai;
		profundidade_B--;
	}
	while(profundidade_A > profundidade_B){
		auxA = auxA->pai;
		profundidade_A--;
	}
	/* Percorre os pais de A e B ao mesmo tempo*/
	for(; auxA != NULL; auxA = auxA->pai, auxB = auxB->pai){
		/* Se em algum momento eles forem iguais */
		if(auxA == auxB){
			/* ...imprimi-se sua informação */
			printf("%d\n", auxA->info);
			return;
		}
	}
}
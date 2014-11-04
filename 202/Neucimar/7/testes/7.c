/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 07 - Cobertura de Conjuntos */

#include <stdio.h>
#include <stdlib.h>


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true} bool;

typedef struct Arvore{
	char info;
	struct Arvore *esq, *dir, *pai;
} NoArvBin, *Arvore;

typedef struct Subset{
	int tam;
	Arvore elem;
} Subset;

/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

void insere(Arvore * Raiz, int chave);
void remove(Arvore * Raiz, int chave);
void rotacao(char tipo, Arvore filho);


/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int u, n;

	int i;
	int atual;

	Subset *set;

	scanf("%d %d", &u, &n);

	set = (Subset*)malloc(n * sizeof(Subset));

	scanf("s ");
	for(i = 0; i < n; i++){
		set[i].tam = 0;
		set[i].elem = NULL;
		while(scanf("%d", &atual)){
			insere(&(set[i].elem), atual, false);
			set[i].tam++;
			if(set[i].tam > u){
				printf("\033[91mERRO\033[97m\n")
				exit(1);
			}
		}
	}



} 
/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/
/***************************************/

insere(Arvore * Raiz, int chave){
	insere_arv_bin(Raiz, chave);
	afunila(Raiz);
}

bool insere_arv_bin(Arvore * Raiz, int chave){
	if(*Raiz == NULL) {
		*Raiz = (Arvore)malloc(sizeof(NoArvBin));
		(*Raiz)->info = chave;
		(*Raiz)->esq = NULL;
		(*Raiz)->dir = NULL;
		(*Raiz)->pai = NULL;
	}
	else if(chave == (*Raiz)->chave){
		return false;
	}
	else if(chave < (*Raiz)->chave){
		insere_arv_bin(&(*Raiz)->esq, chave);
		(*Raiz)->esq->pai = (*Raiz);
	}else{
		insere_arv_bin(&(*Raiz)->dir, chave);
		(*Raiz)->dir->pai = (*Raiz);
	}
	return true;
}
void remove(Arvore * Raiz, int chave){
	
}
void afunila(NoArvBin * f){
	NoArvBin *p, *a;
	if (f == NULL) return;
	else p = f->pai;
	
	if(p == NULL) return;
	else a = p->pai;

	if(a == NULL){
		rotacao(p);
	}else{
		/* Se for homagêneo */
		if((a->dir == p && p->dir == f) || (a->esq == p && p->esq == f)){
			rotacao(p);
			rotacao(f);
		}else{
			rotacao(f);
			rotacao(f);
		}
	}
}

void rotacao(Arvore f) {
	Arvore p = f->pai;
	/* Nesse caso f é o filho direito */
	if(f->pai->dir == f){
		f->pai->esq = f->dir;
		f->dir = f->pai;
	}else{
		f->pai->dir = f->esq;
		f->esq = f->pai;
	}
}


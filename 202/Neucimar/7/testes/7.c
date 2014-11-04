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

bool insere(Arvore * Raiz, int chave);
bool insere_arv_bin(Arvore * Raiz, int chave);
void removE_arv_bin(Arvore * Raiz, int chave);
void afunila(NoArvBin * f);
void rotacao(Arvore f);

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int u, n;

	int i;
	int atual;
	char c;

	Subset *set;

	scanf("%d %d", &u, &n);

	set = (Subset*)malloc(n * sizeof(Subset));

	for(i = 0; i < n; i++){
		set[i].tam = 0;
		set[i].elem = NULL;
		scanf("s ");
		while((c = getchar()) != '\n'){
			ungetc(c, stdin);
			scanf("%d", &atual);
			insere(&(set[i].elem), atual);
			set[i].tam++;
			if(set[i].tam > u){
				printf("\033[91mERRO\033[97m\n");
				exit(1);
			}
		}
	}



} 
/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/
/***************************************/

bool insere(Arvore * Raiz, int chave){
	bool inserivel = insere_arv_bin(Raiz, chave);
	if(inserivel) afunila(Raiz);
	return inserivel
}

bool insere_arv_bin(Arvore * Raiz, int chave){
	if(*Raiz == NULL) {
		*Raiz = (Arvore)malloc(sizeof(NoArvBin));
		(*Raiz)->info = chave;
		(*Raiz)->esq = NULL;
		(*Raiz)->dir = NULL;
		(*Raiz)->pai = NULL;
	}
	else if(chave == (*Raiz)->info){
		return false;
	}
	else if(chave < (*Raiz)->info){
		insere_arv_bin(&(*Raiz)->esq, chave);
		(*Raiz)->esq->pai = (*Raiz);
	}else{
		insere_arv_bin(&(*Raiz)->dir, chave);
		(*Raiz)->dir->pai = (*Raiz);
	}
	return true;
}
void removE_arv_bin(Arvore * Raiz, int chave){
	
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


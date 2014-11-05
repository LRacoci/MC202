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
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde);
void removE_arv_bin(Arvore * Raiz, int chave);
bool afunila(NoArvBin * f);
void rotacao(Arvore f);
void liberaArvore(Arvore A);

void pPre(Arvore A);
void pIn(Arvore A);

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int u, n;

	int i;
	int atual;
	char c;

	Subset *set;

	scanf("%d %d\n", &u, &n);

	set = (Subset*)malloc(n * sizeof(Subset));

	for(i = 0; i < n; i++){
		set[i].tam = 0;
		set[i].elem = NULL;
		scanf("s");
		/***************************************************************************/
		while(scanf("%c", &c) != EOF && c == ' '){
			scanf("%d", &atual);
			insere(&(set[i].elem), atual);
			set[i].tam++;
			pPre(set[i].elem); printf("\n");
			pIn(set[i].elem); printf("\n\n");
			if(set[i].tam > u){
				printf("\033[91mERRO\033[97m\n");
				exit(1);
			}
		}
	}

	for(i = 0; i < n; i++)
		liberaArvore(set[i].elem);
	free(set);

	return 0;

} 
/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/
/***************************************/

bool insere(Arvore * Raiz, int chave){
	NoArvBin *onde;
	bool inserivel = insere_arv_bin(Raiz, chave, &onde);
	if(inserivel) 
		while(afunila(onde)){
			*Raiz = onde;
		}
	return inserivel;
}

bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde){
	if(*Raiz == NULL) {
		*Raiz = (Arvore)malloc(sizeof(NoArvBin));
		(*Raiz)->info = chave;
		(*Raiz)->esq = NULL;
		(*Raiz)->dir = NULL;
		(*Raiz)->pai = NULL;
		*onde = *Raiz;
	}
	else if(chave == (*Raiz)->info){
		return false;
	}
	else if(chave < (*Raiz)->info){
		insere_arv_bin(&(*Raiz)->esq, chave, onde);
		(*Raiz)->esq->pai = (*Raiz);
	}else{
		insere_arv_bin(&(*Raiz)->dir, chave, onde);
		(*Raiz)->dir->pai = (*Raiz);
	}
	return true;
}
void removE_arv_bin(Arvore * Raiz, int chave){
	
}
bool afunila(NoArvBin * f){
	NoArvBin *p, *a;
	if (f == NULL) return false;
	else p = f->pai;
	
	if(p == NULL) return false;
	else a = p->pai;

	if(a == NULL){
		rotacao(f);
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
	return true;
}

void rotacao(NoArvBin * f) {
	/* Nesse caso f é o filho direito */
	if(f->pai->esq == f){
		f->pai->esq = f->dir;
		f->dir = f->pai;
		f->pai = f->dir->pai;
		f->dir->pai = f;
	}else{
		f->pai->dir = f->esq;
		f->esq = f->pai;
		f->pai = f->esq->pai;
		f->esq->pai = f;
	}
}
void liberaArvore(Arvore A){
	if(A){
		liberaArvore(A->dir);
		liberaArvore(A->esq);
		free(A);
	}
}
void pPre(Arvore A){
	if(A){
		printf("%d ", A->info);
		pPre(A->esq);
		pPre(A->dir);
	}
}
void pIn(Arvore A){
	if(A){
		pIn(A->esq);
		printf("%d ", A->info);
		pIn(A->dir);
	}
	else printf("* ");
}
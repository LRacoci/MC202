/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 07 - Cobertura de Conjuntos */

#include <stdio.h>
#include <stdlib.h>


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true, head} bool;

typedef struct Arvore{
	char info;
	struct Arvore *esq, *dir, *pai;
} No, *Arvore;

/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

void insere(Arvore * Raiz, int chave);
void remove(Arvore * Raiz, int chave);

void rotacao(char tipo, Arvore filho);


/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	
} 
/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/
/***************************************/

void insere(Arvore * Raiz, int chave){
	
}
void remove(Arvore * Raiz, int chave){
	
}

void rotacao(char tipo, Arvore f) {
	Arvore p = f->pai;
	/* Nesse caso f é o filho direito */
	if(tipo == 'd'){
		f->pai->esq = f->dir;
		f->dir = f->pai;
	}else if(tipo == 'e'){
		f->pai->dir = f->esq;
		f->esq = f->pai;
	}
}


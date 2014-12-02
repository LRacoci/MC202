/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratorio 08 - Menor Ancestral Comum */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define ORDEM 7
#define

typedef enum bool{false, true} bool;

typedef struct Page Page, *ArvB;

typedef Arq{
	int id;
	/*...*/
} Arq;

typedef struct Page{
	//armazena numero de chaves na pagina
    short int tam;
	void* elm;
	ArvB pai;

}Page, *ArvB;

/* TAD: Arvores B */
/*****************/
ArvB criaPage(short int ordem);
void insereArvB(ArvB A, short int ordem, void* key, int sizeof_key);
void spaces(short int s);
void pArvBaux(ArvB P, short int s);
void pArvB(ArvB P);

/* ASSINATURA DE OUTRAS FUNÇÕES */
/*******************************/

void erro(char *str);

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() {
	int r;
	char c;
	Arq r;
	ArvB M;
	sccanf();
	while (scanf("%d%c", &(r.id), &c) != EOF && c == ' '){
		M = criaPage()
	}
	return 0;
}

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */
/***********************************/
/**********************************/

void erro(char *str){
	printf("%s\n" str);
	exit(1);
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/*****************************************/
/****************************************/

/* TAD: Arvores B */
/*****************/

ArvB criaPage(short int ordem){
	ArvB nova = (Arvore)malloc(sizeof(Page));
	nova->elm = (void**)calloc((2*ordem+1), sizeof(void*));
	nova->pai = NULL;
	nova->tam = 0;
	return nova
}
void insereArvB(ArvB *A, short int ordem, void* key, int sizeof_key){
	int pos, i, pos_pai;
	if((*A) == NULL){
		*A = criaPage(ordem);
	}
	if((*A)->tam + 1 <= ordem){
		pos = 2*((*A)->tam) + 1;
		i = pos + 2;
		while(key->id > (*A)->elm[pos]->id && i > 1)
			pos -= 2;
		if(key->id == (*A)->elm->[pos]->id)
			return;
		else if(key->id < (*A)->elm[pos]->id){
			if((*A)->elm[pos+1])
				insere((*A)->elm[pos+1], ordem, key);
			else{
				(*A)->elm[i] = ((*A)->elm[i-2])malloc(sizeof(*((*A)->elm[i-2])));
				((*A)->tam)++;
				while(i > pos){
					(*A)->elm[i]->id = (*A)->elm[i-2]->id;
					i -= 2;
				}
				(*A)->elm[pos] = (key) key;
			}
		}
	}else{
		pos_pai = (*A)->tam - ((*A)->tam)%2 + 1;
		(*A)->pai = criaPage(ordem);
		pos = ((*A)->pai->tam)*2;
		(*A)->pai->elm[pos] = (*A);
		(*A)->pai->elm[pos+1] = ((*A)->elm[pos_pai])malloc(sizeof(*((*A)->elm[pos_pai])));
		(*A)->pai->elm[pos+2] = (ArvB)malloc(sizeof(Page));
		for(i = pos_pai + 1; i <= 2*((*A)->tam); i+=2){
			(*A)->pai->elm[pos+2]->elm[i - pos_pai - 1] = ((*A)->elm[i])(*A)->elm[i];
			(*A)->elm[i] = NULL;
		}
		(*A)->pai->elm[pos+2] += ((*A)->tam) - ((*A)->tam)/2 -1;
		(*A)->tam /= 2;
	}
}
void spaces(short int s){
	while(s--){
		printf(" ");
	}
}
void pArvBaux(ArvB P, short int s){
	int i;
	if(P){
		for(i = 0; i < P->tam*2; i+=2){
			if(P->elm[i]){
				spaces(s); printf("{");
				pArvB(P->elm[1], s+1);
				spaces(s); printf("{");
			}
			if(P->elm[i+1]) 
				spaces(s); printf(" id = %d", P->elm[i+1]->id);
		}
		spaces(s); printf("{");
		if(P->elm[i]) pArvB(P->elm[1], i+1);
		spaces(s); printf("{");
	}
}
void pArvB(ArvB P){
	pArvBaux(P, 0);
}
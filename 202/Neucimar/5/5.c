/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 05 - Gerente do Espaço */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_TIPO 8
#define MAX_NOME 11

/* Lista Duplamente Ligada, com Nó Cabeça e Circular*/
typedef enum bool{false, true, head} bool;

typedef struct lista { 
	char nome[MAX_NOME]
	int tamanho;
	bool ocupado;
	struct lista *esq, *dir;
} No, *Lista, **Head;



/* TAD: Listas Duplamente Ligadas, Circulares com Nós Cabeças*/

void cria_lista(Head nova_lista);
void cria_no_final(Lista ini, char nome[], int tamanho);
void atribui_tamanho(Lista ini, No* p, int tam);
void transpB2bA(Lista ini, No* A, No* B);
void transpB2aA(Lista ini, No* A, No* B);
void removeNo(Lista ini, No * A);
void removeLista(Head h);

void pLst(Lista ini){
	No* p;
	for(p = ini->dir; p != ini; p = p->dir){
		if(p->ocupado == true)
			printf("\033[95m");
		else
			printf("\033[92m");
		printf("%s: %dKb\n", p->nome, p-<tamanho);
	}
	printf("\033[97m\n");
}

/* TAD: Disco Implementado com Listas Ligadas */

/* assinatura de outras funções */
/********************************/
int Converte_pra_K(char X){
	switch ((int)(X)) {
	case ((int)('K'):
		return 1;
	case ((int)('M')):
		return 1024;
	case ((int)('G')):
		return 1024 * 1024;
	}
}

void imprime_celula(double P){

}
void imprime_disco(Lista ini, int D){
	No* p = ini;
	double aux = 0, livre = 0;
	int max = D/8.0, i = 0, aux;
	
	for (p = ini->dir; p != ini;) {


	
	}


}
bool insere(Lista disco, int D){
	bool cheio;
	char nome[MAX_NOME], unidade, lixo;
	int tam;
	No* p;
	scanf("%s %d%c%c", nome, &tam, &unidade, &lixo);
	tam = tam * Converte_pra_K(unidade);

	if(disco->tamanho + tam > D) return true;

	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado == false && p->tam >= tam){
			atribui_tamanho(disco, p, p->tam - tam)
			cria_antes(disco, p, nome, tam);
		}
	}
	otimiza(disco, D);
	p = disco->esq;
	if(p->ocupado == false && tam <= p->tam){

	}
}
bool


bool Continua(int N){
	int i, D, tam;
	char unidade, lixo;
	char tipo[MAX_TIPO];
	bool cheio;

	Lista disco;

	if(N == 0) return false;
	
	scanf("%d%c%c", &D, &unidade, &lixo);
	D = D * Converte_pra_K(unidade);
	cria_lista(&disco);
	cria_no_final(disco, 0);
	
	for(i = 0, i < N && !cheio; i++){
		scanf("%s", tipo);
		if(strcmp(tipo, "insere") == 0)
			cheio = insere(disco, D);
		else if(strcmp(tipo, "remove") == 0)
			cheio = remove(disco, D);
		else if(strcmp(tipo, "otimiza") == 0)
			cheio = otimiza(disco, D)
	}
	
	removeLista(&disco);
	
	if(cheio) printf("ERRO: disco cheio\n");
	else imprime_disco(disco);

	return true;
}

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int N;
	do{
		scanf("%d", &N);
	}while(Continua(N));

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD de Listas Duplamente Ligadas, Circulares com Nós Cabeças */
/***************************************************************/

/* Cria o nó cabeça*/
void cria_lista(Head nova_lista){
	*nova_lista = (Lista)malloc(sizeof(No));
	
	(*nova_lista)->nome = "Head";
	(*nova_lista)->tamanho = 0;
	(*nova_lista)->ocupado = true;

	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
/* Cria um nó e o insere no final da lista, antes do no cabeça*/
void cria_no_final(Lista ini, char nome[], int tamanho){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	
	novo->tamanho = tamanho;
	ini->tam += tamanho;
	novo->nome = nome;
	novo->ocupado = true;

	novo->dir = ini;
	novo->esq = ini->esq;
	ini->esq = novo;
	novo->esq->dir = novo;
}
/* Cria nó e o insere antes de P*/
void cria_antes(Lista ini, No* P, char nome[], int tamanho){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	
	novo->tamanho = tamanho;
	ini->tam += tamanho;
	novo->nome = nome;
	novo->ocupado = true;


	novo->dir = P;
	novo->esq = P->esq;
	P->esq = novo;
	novo->esq->dir = novo;
}
void atribui_tamanho(Lista ini, No* p, int tam){
	ini->tam -= p->tam;
	p->tam = tam;
	ini->tam += p->tam;
}
/* Retira da lista o nó na posição B e insere antes de A */
void transpB2bA(Lista ini, No* A, No* B){
	if(A == ini || B == ini || A == B)
		return;

	B->dir->esq = B->esq;
	B->esq->dir = B->dir;

	B->dir = A;
	B->esq = A->esq;

	A->esq->dir = B;
	A->esq = B;
}
/* Retira da lista o nó na posição B e insere depois de A */
void transpB2aA(Lista ini, No* A, No* B){
	if(A == ini || B == ini || A == B)
		return;

	B->dir->esq = B->esq;
	B->esq->dir = B->dir;

	B->dir = A->dir;
	B->esq = A;

	A->dir->esq = B;
	A->dir = B;
}
/*Remove o nó na posição A*/
void removeNo(Lista ini, No * A){
	
	if(A == ini)
		return;

	ini->tam -= A->tam;
	A->dir->esq = A->esq;
	A->esq->dir = A->dir;
	free(A);
}
/* Desaloca uma lista inteira*/
void removeLista(Head h){
	/* (*h)->dir é a primeira posição jdá que (*h) aponta para o no cabeça */
	Lista temp, p = (*h)->dir;
	while(p != *h){
		temp = p;
		p = p->dir;
		free(temp);
	}
	free(p);
	*h = NULL;
}

/* TAD de  */
/****************************/

/* implementação de outras funções */
/**********************************/
/*********************************/
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
#define MAX_DISCO 8

/* Lista Duplamente Ligada, com Nó Cabeça e Circular*/
typedef enum bool{false, true, head} bool;

typedef struct lista { 
	char *nome;
	int tam;
	bool ocupado;
	struct lista *esq, *dir;
} No, *Lista, **Head;

/* TAD: Listas Duplamente Ligadas, Circulares com Nós Cabeças*/
/************************************************************/

void cria_lista(Head nova_lista, int D);
void cria_primeiro(Lista ini, char nome[], int tam);
void cria_antes(Lista ini, No* P, char nome[], int tam, bool flag);
void atribui_tam(Lista ini, No* p, int tam);
void transpB2bA(Lista ini, No* A, No* B);
void transpB2aA(Lista ini, No* A, No* B);
void removeNo(Lista ini, No * A);
void removeLista(Head h);
void copia_lista(Lista A, Lista B);
void picotaLista(Lista A, double parte);
void picotaNo(Lista A, No* p, double slice);

void pLst(Lista ini);

/* TAD: Disco, implementado com Listas Ligadas */
/**********************************************/
void imprime_celula(double P);
void imprime_disco(Lista ini, int D);
bool otimiza_disco(Lista disco, int D);
bool insere(Lista disco, int D, int tam, char* nome);
void remove_arquivo(Lista disco, char* nome);
void mescla(Lista disco, No * p);

/* assinatura de outras funções */
/********************************/
int Converte_pra_K(char X);
bool Continua(int N);

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
/* implementação de outras funções */
/**********************************/
/*********************************/

bool Continua(int N){
	int i, D, tam;
	char unidade, lixo;
	char tipo[MAX_TIPO], nome[MAX_NOME];
	bool cheio = false;

	Lista disco;

	if(N == 0) return false;
	
	scanf("%d%c%c", &D, &unidade, &lixo);
	D = D * Converte_pra_K(unidade);
	
	cria_lista(&disco, D);
	cria_primeiro(disco, "", D);
	
	for(i = 0; i < N; i++){
		scanf("%s", tipo);
		if(strcmp(tipo, "insere") == 0){
			scanf("%s %d%c%c", nome, &tam, &unidade, &lixo);
			if(!cheio){
				tam = tam * Converte_pra_K(unidade);
				cheio = insere(disco, D, tam, nome);
			}
		}else if(strcmp(tipo, "remove") == 0){
			scanf("%s", nome);
			if(!cheio)
				remove_arquivo(disco, nome);
		}else if(strcmp(tipo, "otimiza") == 0){
			if(!cheio) 
				cheio = otimiza_disco(disco, D);
		}else{
			printf("\033[91mERRO: Operaçao desconhecida: %s\033[97m\n", tipo);
			exit(1);
		}
		/*imprime_disco(disco, D);*/
	}
	
	if(cheio) printf("ERRO: disco cheio\n");
	else imprime_disco(disco, D);

	removeLista(&disco);
	
	return true;
}

int Converte_pra_K(char X){
	switch ((int)(X)) {
	case ((int)('K')):
		return 1;
	case ((int)('M')):
		return 1024;
	case ((int)('G')):
		return 1024 * 1024;
	}
	return -1;
}

/* TAD de Disco, implementado com Listas Ligadas */
/************************************************/
/***********************************************/

void imprime_celula(double P){
	P *= 100;
	if ((75 < P) && (P <= 100)) 
		printf("[ ]");
	else if((25 < P) && (P <= 75)) 
		printf("[-]");
	else if((0 <= P) && (P <= 25)) 
		printf("[#]");
}
void imprime_disco(Lista ini, int D){
	double parte = D/8.0;
	/*double jl = 0;*/
	Lista aux;
	pLst(ini);
	cria_lista(&aux, D);
	copia_lista(aux, ini);
	picotaLista(aux, parte);
	pLst(aux);
	/*for(p = ini->dir; p != ini; p = p->prox){
		jl += p->tam;
		if(jl == ){

		}
	}*/
	removeLista(&aux);

}
bool otimiza_disco(Lista disco, int D){
	No* p;
	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado == false){
			removeNo(disco, p);
		}
	}
	if(disco->tam < 0) return true;
	
	cria_primeiro(disco, "", disco->tam);
	
	return false;
}
bool insere(Lista disco, int D, int tam, char* nome){
	No* p;
	
	if(disco->tam - tam < 0) return true;

	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado == false && p->tam >= tam){
			atribui_tam(disco, p, p->tam - tam);
			cria_antes(disco, p, nome, tam, true);
			return false;
		}
	}

	if(otimiza_disco(disco, D)) return true;
	p = disco->esq;
	if(p->ocupado == false && tam <= p->tam){
		atribui_tam(disco, p, p->tam - tam);
		cria_antes(disco, p, nome, tam, true);
		return false;
	}else return true;
	return false;
}
void remove_arquivo(Lista disco, char* nome){
	No* p;
	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado && strcmp(nome, p->nome) == 0){
			p->ocupado = false;
			disco->tam += p->tam;
			mescla(disco, p);
			return;
		}
	}
}
void mescla(Lista disco, No * p){
	if(!(p->dir->ocupado)){
		p->tam += p->dir->tam;
		removeNo(disco, p->dir);
	}
	if(!(p->esq->ocupado)){
		p->tam += p->esq->tam;
		removeNo(disco, p->esq);
	}
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD de Listas Duplamente Ligadas, Circulares com Nós Cabeças */
/***************************************************************/

/* Cria o nó cabeça */
void cria_lista(Head nova_lista, int D){
	*nova_lista = (Lista)malloc(sizeof(No));
	
	(*nova_lista)->nome = (char*)malloc(10 * sizeof(char));
	(*nova_lista)->nome = strcpy((*nova_lista)->nome, "Head");

	(*nova_lista)->tam = D;
	(*nova_lista)->ocupado = true;

	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
/* Cria um nó e o insere no final da lista, antes do no cabeça */
void cria_primeiro(Lista ini, char nome[], int tam){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	
	novo->tam = tam;
	novo->nome = (char*)malloc(MAX_NOME * sizeof(char));
	novo->nome = strcpy(novo->nome, nome);
	novo->ocupado = false;

	novo->dir = ini;
	novo->esq = ini->esq;
	ini->esq = novo;
	novo->esq->dir = novo;
}
/* Cria nó e o insere antes de P */
void cria_antes(Lista ini, No* P, char nome[], int tam, bool flag){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	
	novo->tam = tam;
	if(flag == true) ini->tam -= tam;

	novo->nome = (char*)malloc(MAX_NOME * sizeof(char));
	novo->nome = strcpy(novo->nome, nome);

	novo->ocupado = flag;


	novo->dir = P;
	novo->esq = P->esq;
	P->esq = novo;
	novo->esq->dir = novo;
}
void atribui_tam(Lista ini, No* p, int tam){
	if (p->ocupado) {
		ini->tam += p->tam;
		p->tam = tam;
		ini->tam -= p->tam;
	}else{
		p->tam = tam;
	}
}
/* Remove o nó na posição A */
void removeNo(Lista ini, No * A){
	
	if(A == ini)
		return;

	if(A->ocupado){
		ini->tam += A->tam;
	}
	free(A->nome);

	A->dir->esq = A->esq;
	A->esq->dir = A->dir;
	free(A);
}
/* Desaloca uma lista inteira */
void removeLista(Head h){
	/* (*h)->dir é a primeira posição jdá que (*h) aponta para o no cabeça */
	Lista temp, p = (*h)->dir;
	while(p != (*h)){
		temp = p;
		p = p->dir;
		free(temp->nome);
		free(temp);
	}
	free(p);
	*h = NULL;
}

void copia_lista(Lista A, Lista B){
	No* pB;
	if(A->dir != A || A->esq != A){
		return;
	}
	for(pB = B->dir; pB != B; pB = pB->dir){
		cria_antes(A, A, pB->nome, pB->tam, pB->ocupado);
	}
}
void picotaLista(Lista A, double parte){
	double jl = 0;
	No *p;
	for(p = A->dir; p != A;){
		jl += p->tam;	
		if(jl < parte && jl + p->dir->tam > parte){
			p = p->dir;
			picotaNo(A, p->dir, parte - jl);
			jl = 0;
		}else if(jl > parte){
			jl -= p->tam;
			picotaNo(A, p, parte - jl);
			
			jl = 0;
		}else{
			p = p->dir;
		}

	}
}
void picotaNo(Lista A, No* p, double slice){
	if(p->tam <= slice || slice <= 0){
		return;
	}
	cria_antes(A, p, p->nome, slice, p->ocupado);
	atribui_tam(A, p, p->tam - slice);
}
void pLst(Lista ini){
	No* p;
	printf("Disco com %d Kb livres\n", ini->tam);
	for(p = ini->dir; p != ini; p = p->dir){
		if(p->ocupado == true)
			printf("\033[94m");
		else
			printf("\033[91m");
		printf("%s: %dKb\n", p->nome, p->tam);
	}
	printf("\033[97m\n");
}

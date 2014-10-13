/* Nome: Lucas Alves Racoci
* RA: 156331 
* Laboratorio 01 - O problema do acesso à lista */


#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */ 
/*************************************************************/
typedef struct No{
	int info;
	int k;
	struct No *dir, *esq;
} No, *Lista, **Head; 

/*Funções básicas de lista, só as necessárias*/
void cria_lista(Head nova_lista);
void cria_no(Lista ini, int info, int k);
void RemoveLista(Lista * p);
void Ordena_Lst(Lista ini, No * p);
void TrocaNos(Lista ini, No* A, No* B);
void Transp(Lista ini, No* A, No* B);

/*Funções Principais*/
int MTF (Lista ini, int chave);
int  TR (Lista ini, int chave);
int  FC (Lista ini, int chave);

/*Função de ler entrada*/
void LeEntrada(int *N, int *R, int **requisicoes);
/*Função de incializar lista de acordo com o enunciado*/
void inicializaLista(Lista * lista, int R);

/*FUNÇÕES DE DEBUGAR*/
void pLst(Lista ini, char indicador);
void pVet(int v[], int n);


/* MEU PROGRAMA - MAIN */
/***********************/
int main() { 
	int N, R, *requisicao, i;

	int custo;

	int MTF_total = 0, TR_total = 0, FC_total = 0;
	Lista arqs;
	
	/*Se a entrada for muito estranha*/
	LeEntrada(&N, &R, &requisicao);
	
	/*MTF*/
	cria_lista(&arqs);
	inicializaLista(&arqs, N);
	
	for (i = 0; i < R; i++){
		if (requisicao[i] < 1 || requisicao[i] > N) 
			custo = N;
		else 
			custo = MTF(arqs, requisicao[i]);
		
		MTF_total += custo;

	}

	RemoveLista(&arqs);

	/*TR*/

	cria_lista(&arqs);
	inicializaLista(&arqs, N);

	for (i = 0; i < R; i++){
		if (requisicao[i] < 1 || requisicao[i] > N) 
			custo = N;
		else 
			custo = TR(arqs, requisicao[i]);
		
		TR_total += custo;

	}

	RemoveLista(&arqs);

	/*FC*/

	cria_lista(&arqs);
	inicializaLista(&arqs, N);

	for (i = 0; i < R; i++){
		if (requisicao[i] < 1 || requisicao[i] > N) 
			custo = N;
		else 
			custo = FC(arqs, requisicao[i]);
		
		FC_total += custo;

	}
		
	RemoveLista(&arqs);

	/*Final*/
	printf("%d %d %d\n", MTF_total, TR_total, FC_total);

	free(requisicao);
	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/******************************************/

void cria_lista(Head nova_lista){
	*nova_lista = (Lista)malloc(sizeof(No));
	(*nova_lista)->info = -1;
	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
void LeEntrada(int *N, int *R, int **requisicoes){
	int i;

	scanf("%d %d", N, R);
	if(*R > 0) *requisicoes = malloc((*R) * sizeof(int));
	for(i = 0; i < (*R); i++){
		scanf("%d", &((*requisicoes)[i]));
	}
}
void inicializaLista(Head h, int N){
	int i;
	for(i = 1; i <= N; i++){
		cria_no(*h, i, 0);
	}
}
void cria_no(Lista ini, int info, int k){
	No* novo;
	novo = malloc(sizeof(No));
	novo->info = info;
	novo->k = k;

	novo->dir = ini;
	novo->esq = (ini)->esq;
	(ini)->esq = novo;
	novo->esq->dir = novo;
}
void RemoveLista(Head h){
	Lista temp, p = (*h)->dir;
	while(p != *h){
		temp = p;
		p = p->dir;
		free(temp);
	}
	free(p);
	*h = NULL;
}
void Ordena_Lst(Lista ini, No * p){
	Lista i;

	for(i = (ini)->dir; (i != ini) && (i->k > p->k); i = i->dir);
		
	Transp(ini, i, p);
}
/*Troca a por b*/
void TrocaNos(Lista ini, No* A, No* B){
	Lista a, b, aux;
	if(A == ini || B == ini || A == B)
		return;

	a = A->esq;
	b = B->esq;

	a->dir = B;
	b->dir = A;
	aux = B->dir;
	B->dir = A->dir;
	A->dir = aux;

	a = A->dir;
	b = B->dir;

	a->esq = B;
	b->esq = A;
	aux = B->esq;
	B->esq = A->esq;
	A->esq = aux;
}

void Transp(Lista ini, No* A, No* B){
	if(A == ini || B == ini || A == B)
		return;

	B->dir->esq = B->esq;
	B->esq->dir = B->dir;

	B->dir = A;
	B->esq = A->esq;

	A->esq->dir = B;
	A->esq = B;
	
}
int MTF(Lista ini, int chave){
	Lista p = ini->dir;
	int MTF = 0;
	
	/*Se a lista for vazia não há custo, pq nenhm elemento foi acessado*/
	while(p != ini){
		MTF++;
		if(p->info == chave){
			Transp(ini, ini->dir, p);
			return MTF;
		}
		p = p->dir;
	}
	return MTF;
}
int TR(Lista ini, int chave){
	Lista p = ini->dir;
	int TR = 0;

	/*Se a chave está na primeira pos, o custo é 1 e nda precisa ser feito*/
	if(p->info == chave)
		return 1;
	
	/*Percorre-se a lista até achar o elemento p, que contém a chave*/
	while(p != ini){
		TR++;
		if(p->info == chave){
			Transp(ini, p->esq, p);
			return TR + 1;
		}
		p = p->dir;
	}
	return TR;
}
int FC(Lista ini, int chave){
	No* p = (ini)->dir;
	int FC = 0;

	while(p != ini){
		FC++;
		if(p->info == chave){
			(p->k)++;
			Ordena_Lst(ini, p);
			return FC;
		}
		p = p->dir;
	}
	return FC;
}
/*FUNÇÕES DE DEBUGAR*/
/*******************/
void pLst(Lista ini, char indicador) {
	No *p;
	printf("Lista L=(%d", ini->dir->info);
	for(p = ini->dir->dir; p != ini; p = p->dir){
		printf(",%d", p->info);
	}
	if(indicador == 's'){
		printf(").Contador C=(%d", ini->k);
		for(p = ini->dir; p != ini; p = p->dir){
			printf(",%d", p->k);
		}
	}
	printf(")\n");
}
void pVet(int v[], int n){
	int i;
	printf("{%d", v[0]);
	for(i = 1; i < n; i++){
		printf(" %d", v[i]);
	}
	printf("}\n");
}
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
	struct No* prox;
} No, *Lista, **No1; 

/*Funções básicas de lista, só as necessárias*/
Lista cria_lista();
Lista insere_no(No* p, int info, int k);
void RemoveLista(Lista *p);
void Recoloca_No(Lista * ini, No * p);
void TrocaNos(Lista* ini, No* A, No* B);
/*Funções Principais*/
int MTF(Lista* ini, int chave);
int TR(Lista* ini, int chave);
int FC(Lista* ini, int chave);
/*Função aux para a FC fincionar*/
void zera_K(Lista ini);

/*Função de ler entrada*/
void LeEntrada(int *N, int *R, int **in);
/*Função de incializar lista de acordo com o enunciado*/
void inicializaLista(Lista * lista, int R);

/*FUNÇÕES DE DEBUGAR*/
void pLst(Lista ini, char nome[]);
void pVet(int v[], int n);


/* MEU PROGRAMA - MAIN */
/***********************/
int main() { 
	int N, R, *in, i;

	int aux;


	int MTFr = 0, TRr = 0, FCr = 0;
	Lista arqs;
	

	LeEntrada(&N, &R, &in);
	
	
	/*MTF*/
	
	arqs = cria_lista();
	inicializaLista(&arqs, N);
	
	
	for (i = 0; i < R; i++){
		aux = MTF(&arqs, in[i]);
		MTFr += aux;
	}

	
	RemoveLista(&arqs);

	/*TR*/
		arqs = cria_lista();
	inicializaLista(&arqs, N);

	
	for (i = 0; i < R; i++){
		aux = TR(&arqs, in[i]);
		TRr += aux;
	}

	RemoveLista(&arqs);

	/*FC*/
	
	arqs = cria_lista();
	inicializaLista(&arqs, N);
	zera_K(arqs);

	
	for (i = 0; i < R; i++){
		aux = FC(&arqs, in[i]);
		FCr += aux;
	}
		
	RemoveLista(&arqs);

	/*Final*/
	printf("%d %d %d\n", MTFr, TRr, FCr);

	free(in);
	return 0; 
}  

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/******************************************/

Lista cria_lista(){
	return NULL;
}
void LeEntrada(int *N, int *R, int **in){
	int i;

	scanf("%d %d", N, R);
	*in = malloc((*R) * sizeof(int));

	for(i = 0; i < (*R); i++){
		scanf("%d", &((*in)[i]));
	}
}
void inicializaLista(Lista * lista, int N){
	int i;
	for(i = N; i > 0; i--){
		*lista = insere_no(*lista, i, 0);
	}
}
Lista insere_no(No* p, int info, int k){
	No* novo;
	novo = malloc(sizeof(No));
	novo->info = info;
	novo->k = k;
		
	novo->prox = p;
	return novo;
}
void RemoveLista(Lista *p){
	Lista temp;
	while(*p != NULL){
		temp = *p;
		*p = (*p)->prox;
		free(temp);
	}
}
int MTF(Lista* ini, int chave){
	Lista p = *ini;
	int MTF = 0;
	/*se a lista for vazia*/
	if(p == NULL) return 0;

	/*Se o primeiro elemento contiver a chave*/
	if(p->info == chave){
		return 1;
	}
	/*Percorre a lista*/
	while(p != NULL){
		/*Conta o custo de perocrrer a lista*/
		MTF++;
		/*Se a chave for achada*/
		if(p->info == chave){
			/*Traca-se este no com o primeiro*/
			TrocaNos(ini, p, *ini);
			/*e retorna o custo*/
			return MTF;
		}
		/*Paso*/
		p = p->prox;
	}
	/*Será o n, porque a lista foi completamente percorrida*/
	return MTF;
}
int TR(Lista* ini, int chave){
	Lista p = *ini;
	int TR = 0;
	/*Se a lista for vazia não há custo, pq nenhm elemento foi acessado*/
	if(p == NULL) 
		return 0;
	/*Se a chave está na primeira pos, o custo é 1 e nada precisa ser feito*/
	if(p->info == chave)
		return 1;
	/*Se a lista so tem um elemento que não é a chave, o custo é o 
	 *de percorrer a unica pos da lista*/
	if(p->prox == NULL) 
		return 1;
	/*Percorre-se a lista até achar o elemento p,
	 *anterior ao que contém a chave*/
	while(p != NULL){
		TR++;
		if(p->prox != NULL && p->prox->info == chave){
			/*No caso, eu paro de contar o custo quando acho o elemento
			 *anterior ao da chave, para corrigir isso, eu re-incremento
			 *o custo aqui*/
			TR++;
			TrocaNos(ini, p, p->prox);
			/*O +1 é da troca*/
			return TR+1;
		}
		p = p->prox;
	}
	return TR;
}
int FC(Lista* ini, int chave){
	No* p = *ini;
	int FC = 0;
		
	FC = 0;

	while(p != NULL){
		FC++;
		if(p->info == chave){
			(p->k)++;
			Recoloca_No(ini, p);
			return FC;
		}
		p = p->prox;
	}
	return FC;
}
void zera_K(Lista ini){
	No* p;
	for(p = ini; p != NULL; p = p->prox){
		p->k = 0;
	}
}
void Recoloca_No(Lista * ini, No * p){
	Lista i;

	for(i = *ini; (i != NULL) && (i->k > p->k); i = i->prox);
		
	TrocaNos(ini, i, p);
}
/*Troca a por b*/
void TrocaNos(Lista* ini, No* A, No* B){
	Lista aux, a, b;

	if(A == NULL || B == NULL || A == B)
		return;
	
	if(*ini == A){
		TrocaNos(ini, B, A);
		return;
	}
	if(*ini == B){
		/*Acha o elemento a, anterior a A*/
		
		a = *ini; 
		while(a->prox != A) 
			a = a->prox;
		
		aux = a->prox;
		a->prox = a->prox->prox;
		aux->prox = *ini;
		*ini = aux;
		return;
	}
	
	/*Acha os elementos, a e b, anteriores a A e B*/
	a = *ini; 
	while(a->prox != A) 
		a = a->prox;
	
	b = *ini; 
	while(b->prox != B) 
		b = b->prox;
	
	a->prox = B;
	b->prox = A;
	aux = B->prox;
	B->prox = A->prox;
	A->prox = aux;
}
/*FUNÇÕES DE DEBUGAR*/
/*******************/
void pLst(Lista ini, char nome[]) {
	No *p;
	printf("Lista %s=(%d", nome, ini->info);
	for(p = ini->prox; p != NULL; p = p->prox){
		printf(",%d", p->info);
	}
	printf(").Contador C=(%d", ini->k);
	for(p = ini->prox; p != NULL; p = p->prox){
		printf(",%d", p->k);
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
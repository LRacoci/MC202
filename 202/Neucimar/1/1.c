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
	/*int ID;*/
	struct No* prox;
} No, *Lista, **No1; 

Lista cria_lista();
Lista insere_no(No* p, int info, int k);
void remove_no(No* p, int *info, int *k);
void pLst(Lista ini, char nome[]);
void RemoveLst_i(Lista *p);
void RemoveLst_r(Lista ini);
void zera_K(Lista ini);
void TrocaNos(Lista* ini, No* A, No* B);
int MTF(Lista* ini, int chave);
int TR(Lista* ini, int chave);
void Ordena_Lst(Lista * ini, No * p);
int FC(Lista* ini, int chave);
void pVet(int v[], int n);

/* MEU PROGRAMA - MAIN */
/***********************/
int main() { 
	int N, R, *in;
	int i;
	int MTFr = 0, TRr = 0, FCr = 0;

	Lista arqs = cria_lista();

	scanf("%d %d", &N, &R);
	in = malloc(R * sizeof(int));

	for(i = 0; i < R; i++){
		scanf("%d", &in[i]);
	}
	/*MTF*/
	printf("Calculo MTF:\n\n");

	for(i = N; i > 0; i--){
		arqs = insere_no(arqs, i, 0);
	}

	printf("Requisições: ");
	pVet(in, R);

	for (i = 0; i < R; i++){
		MTFr += MTF(&arqs, in[i]);
		printf("Requisição = %d Custo = %2d. ", in[i], MTFr);
		pLst(arqs, "arqs");
	}
	pLst(arqs, "arqs");

	RemoveLst_i(&arqs);

	/*TR*/
	arqs = cria_lista();

	printf("Calculo TR:\n\n");

	for(i = N; i > 0; i--){
		arqs = insere_no(arqs, i, 0);
	}

	printf("Requisições: ");
	pVet(in, R);

	for (i = 0; i < R; i++){
		TRr += TR(&arqs, in[i]);
		printf("Requisição = %d Custo = %2d. ", in[i], TRr);
		pLst(arqs, "arqs");
	}
	pLst(arqs, "arqs");

	RemoveLst_i(&arqs);

	/*FC*/
	arqs = cria_lista();

	printf("Calculo FC:\n\n");

	for(i = N; i > 0; i--){
		arqs = insere_no(arqs, i, 0);
	}
	/*
	printf("Requisições: ");
	pVet(in, R);
	*/
	zera_K(arqs);

	for (i = 0; i < R; i++){
		FCr += FC(&arqs, in[i]);
		printf("Requisição = %d Custo = %2d. ", in[i], FCr);
		pLst(arqs, "arqs");
	}
	pLst(arqs, "arqs");

	RemoveLst_i(&arqs);

	

	/*Final*/
	printf("%d %d %d\n", MTFr, TRr, FCr);


	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/******************************************/

Lista cria_lista(){
	return NULL;
}
Lista insere_no(No* p, int info, int k){
	No* novo;
	novo = malloc(sizeof(No));
	novo->info = info;
	novo->k = k;
		
	novo->prox = p;
	return novo;
}
void remove_no(No* p, int *info, int *k){
	No* temp;
	
	*info = p->prox->info;
	*k = p->prox->k;
	

	if(p == NULL){
		return;
	}else if(p->prox == NULL){
		return;
	}else{
		temp = p->prox;
		p->prox = temp->prox;
		free(temp);
    }
}
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
void RemoveLst_i(Lista *p){
	Lista temp;
	while(*p != NULL){
		temp = *p;
		*p = (*p)->prox;
		free(temp);
	}
}
void RemoveLst_r(Lista ini){
	if(ini == NULL) return;
	RemoveLst_r(ini->prox);
	free(ini);
}
void zera_K(Lista ini){
	No* p;
	for(p = ini; p != NULL; p = p->prox){
		p->k = 0;
	}
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
int MTF(Lista* ini, int chave){
	Lista p = *ini;
	int MTF;
	
	if(p == NULL) return 0;

	if(p->info == chave){
		return 1;
	}
	/*O elemento deve estar no mínimo na primeira posição*/
	MTF = 1;

	while(p != NULL && p->info != chave){
		p = p->prox;
		MTF++;
	}
	if(p == NULL) 
		return MTF;
	else{
		TrocaNos(ini, p, *ini);
		return MTF;
	}
}
int TR(Lista* ini, int chave){
	Lista p = *ini;
	int TR = 0;
	/*Se a lista for vazia não há custo, pq nenhm elemento foi acessado*/
	if(p == NULL) 
		return 0;
	/*Se a chave está na primeira pos, o custo é 1 e nda precisa ser feito*/
	if(p->info == chave)
		return 1;
	/*Se a lista so tem um elemento que não é a chave, o custo é o 
	 *de percorrer a unica pos da lista*/
	if(p->prox == NULL) 
		return 1;
	/*O elemento deve estar no mínimo na segunda posição*/
	TR = 2;
	/*Percorre-se a lista até achar o elemento p,
	 *anterior ao que contém a chave*/
	while(p->prox != NULL && p->prox->info != chave){
		p = p->prox;
		TR++;
	}
	if(p->prox == NULL){
		return TR;
	}else{
		TrocaNos(ini, p, p->prox);
		return TR + 1;
	}
}

void Ordena_Lst(Lista * ini, No * p){
	Lista i;

	for(i = *ini; (i != NULL) && (i->k > p->k); i = i->prox);
		
	TrocaNos(ini, i, p);
}

int FC(Lista* ini, int chave){
	No* p = *ini;
	int FC = 0;
	
	
	
	/*O elemento deve estar no mínimo na primeira posição*/
	FC = 1;

	while(p != NULL && p->info != chave){
		p = p->prox;
		FC++;
	}
	if(p == NULL){
		return FC;
	}else{
		(p->k)++;
		Ordena_Lst(ini, p);
		return FC;
	}
}



void pVet(int v[], int n){
	int i;
	printf("{%d", v[0]);
	for(i = 1; i < n; i++){
		printf(" %d", v[i]);
	}
	printf("}\n");
}
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

typedef struct Set{
	int tam;
	Arvore elem;
} *Set, Conjunto;

typedef struct VetInt{
	int tam;
	bool cobre;
	int *v;
} VetInt;

/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

bool insira(Set C, int chave);
void insere_arv_bin_recursivo(Arvore *p, int chave, bool* inserivel);
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde);
bool insere_arv_bin_2(Arvore * Raiz, int chave, NoArvBin** onde);

bool remova(Set C, int chave);
bool remove_arv_bin(Arvore * Raiz, int chave,  NoArvBin** onde);
bool afunila(NoArvBin * f);
void rotacao(NoArvBin * f);
void liberaArvore(Arvore A);

void pArv(Arvore A);
void pPre(Arvore A);
void pIn(Arvore A);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

void cria_universo(Set U, int u);
int maior(Set *subsets, int n);
void remove_set(int M, Set *subset, int* n);
void complemento(Set A, Set B);
void salva_elementos_pre_ordem(Arvore A, VetInt * A_elem);
void imprime_final(VetInt R);

void pSet(Set* x, int n, char *str){
	int i;
	for(i = 0; i < n; i++){
		printf("\033[93m%s[%d]\033[97m:\n", str, i+1);
		if(x[i])pArv(x[i]->elem);
		printf("\n");
	}
}
void Confere(Arvore A, char *str){
	if(!A)
		return;
	if(A->esq){
		if(A->esq->pai != A){
			printf("\033[91m%s\n", str);
			printf("(%d)->pai != (%d), mas (%d)->esq == (%d)\n", 
				   A->esq->info, A->info, A->info, A->esq->info);
		}if(A->esq->info > A->info){
			printf("\033[91m%s\n", str);
			printf("%d > %d, mas (%d)->esq == (%d)\n", 
				   A->esq->info, A->info, A->info, A->esq->info);
		}
	Confere(A->esq, str);
	}if(A->dir){
		if(A->dir->pai != A){
			printf("\033[91m%s\n", str);
			printf("(%d)->pai != (%d), mas (%d)->dir == (%d)\n", 
				   A->dir->info, A->info, A->info, A->dir->info);
		}if(A->dir->info < A->info){
			printf("\033[91m%s\n", str);
			printf("%d < %d, mas (%d)->dir == (%d)\n", 
				   A->dir->info, A->info, A->info, A->dir->info);
		}
	Confere(A->dir, str);
	}
	printf("\033[97m");
}
Arvore raiz(NoArvBin* p){
	if(p) 
		while(p->pai){
			p = p->pai;
		}
	return p;
}

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int n, u;

	int i, j, M_indice;
	int atual;
	char c;

	VetInt R;

	Set *subsets, universe, M = NULL;

	universe = (Set)malloc(sizeof(Conjunto));
	universe->tam = 0;
	universe->elem = NULL;

	scanf("%d %d\n", &u, &n);

	cria_universo(universe, u);

	R.v = (int*)malloc(n * sizeof(int));
	R.tam = 0;
	R.cobre = true;

	subsets = (Set*)malloc(n * sizeof(Set));

	for(i = 0; i < n; i++){
		subsets[i] = (Set)malloc(sizeof(Conjunto));
		subsets[i]->tam = 0;
		subsets[i]->elem = NULL;
		scanf("s");
		while(scanf("%c", &c) != EOF && c == ' '){
			scanf("%d", &atual);
			insira(subsets[i], atual);
			if(subsets[i]->tam > universe->tam){
				printf("\033[91mERRO\033[97m\n");/** dbERROS **/
				exit(1);
			}
		}
	}
	
	for(i = 0; i < n; i++){
		pSet(subsets, n, "S");/** db prints1 **/
		M_indice = maior(subsets, n);
		if(M_indice == -1) break;
		M = subsets[M_indice];
		subsets[M_indice] = NULL;
		for(j = 0; j < n; j++){
			if(subsets[j] && subsets[j]->tam) 
				complemento(subsets[j], M);
		}
		complemento(universe, M);
		pSet(&universe, 1, "U");/** db prints1 **/
		R.v[R.tam++] = M_indice + 1;
		imprime_final(R);/** db prints1 **/
		printf("\n");/** db prints1 **/
		if(!M){
			printf("\033[91mERRO 2\033[97m\n");/** dbERROS **/
			exit(1);
		}
		liberaArvore(M->elem);
		free(M); 
	}
	R.cobre = universe->tam == 0;

	imprime_final(R);
	free(R.v);
	if(universe){
		liberaArvore(universe->elem);
		free(universe); 
	}
	for(i = 0; i < n; i++){
		if((subsets[i])){
			liberaArvore(subsets[i]->elem);
			free(subsets[i]);
		}
	}
	free(subsets);

	return 0;
} 

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

void cria_universo(Set U, int u){
	int i;
	for(i = 1; i <= u; i++){
		insira(U, i);
	}
}
int maior(Set *S, int n){
	int i, max;
	for(max = n-1; max >= 0; max--){
		if(S[max] && S[max]->tam){
			break;
		}
	}
	for(i = max; i >= 0; i--){
		if(S[i] && S[max]->tam < S[i]->tam)
			max = i;
		printf("\033[94mmax = %d\033[97m\n", max+1);/** db prints2 **/
	}
	return max;
}
void complemento(Set A, Set B){
	int i;
	VetInt B_elem;
	B_elem.v = (int*)malloc(B->tam * sizeof(int));
	B_elem.tam = 0;
	salva_elementos_pre_ordem(B->elem, &B_elem);
	for(i = 0; i < B_elem.tam; i++){
		remova(A, B_elem.v[i]);
	}
}
void salva_elementos_pre_ordem(Arvore A, VetInt * A_elem){
	if(A){
		A_elem->v[A_elem->tam++] = A->info;
		salva_elementos_pre_ordem(A->esq, A_elem);
		salva_elementos_pre_ordem(A->dir, A_elem);
	}
}
void imprime_final(VetInt R){
	int i;
	if(R.cobre && R.tam > 0){
		printf("S%d ",R.v[0]);
		for(i = 1; i < R.tam; i++){
			printf("U S%d ",R.v[i]);
		}
	 	printf(":)\n");
	 }
	else printf(":(\n");
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

bool insira(Set C, int chave){
	NoArvBin *onde;
	bool inserivel;
	
	printf("\033[92mI:Chave\033[97m = %d:\n", chave);/** db prints2 **/
	pArv(C->elem);/** db prints2 **/
	Confere(C->elem, "I: Antes de inserir:");/** db RevisaArvore **/

	inserivel = insere_arv_bin(&C->elem, chave, &onde);
	if(!inserivel) return false;
	
	Confere(C->elem, "I: Antes de afunilar:");/** db RevisaArvore **/
	pSet(&C, 1, "R: Antes de Afunilar");/** db prints3 **/

	while(afunila(onde)){
		C->elem = onde; /** apagar isso **/
		pSet(&C, 1, "I: Afunilando");/** db Afunilando **/
	}

	Confere(C->elem, "I: Depois de afunilar:");/** db RevisaArvore **/
	pSet(&C, 1, "I: Final");/** db prints3 **/

	C->elem = onde;
	(C->tam)++;


	return true;
}
void insere_arv_bin_recursivo(Arvore *p, int chave, bool* inserivel){
	if(*p == NULL) {
		*inserivel = true;
		*p = (Arvore)malloc(sizeof(NoArvBin));
		(*p)->info = chave;
		while((*p)->info != chave){
			printf("(*p)->info = %d e chave = %d\n", (*p)->info, chave);
			(*p)->info = chave*((*p)->info/chave);
			printf("(*p)->info = %d e chave = %d\n", (*p)->info, chave);
		}
		(*p)->esq = NULL;
		(*p)->dir = NULL;
	}
	else if(chave == (*p)->info)
		*inserivel = false;
	else if(chave < (*p)->info){
		insere_arv_bin_recursivo(&(*p)->esq, chave, inserivel);
		(*p)->esq->pai = *p;
	}else{
		insere_arv_bin_recursivo(&(*p)->dir, chave, inserivel);
		(*p)->dir->pai = *p;
	}
}
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde){
	bool esquerdo, ehraiz = false;
	NoArvBin *temp = NULL;
	Arvore f = *Raiz;
	if(f == NULL)
		ehraiz = true;
	while (f != NULL){
		if(chave < f->info){
			temp = f;
			f = temp->esq;
			esquerdo = true;
		}else if(chave > f->info){
			temp = f;
			f = temp->dir;
			esquerdo = false;
		}else{
			return false;
		}
	}
	f = (Arvore)malloc(sizeof(NoArvBin));
	f->info = chave;
	/*Loop WTF*/
	while(f->info != chave){
		f->info = chave;
	}
	f->esq = NULL;
	f->dir = NULL;
	f->pai = temp;
	if(temp){
		if(esquerdo){
			temp->esq = f;
		}else{
			temp->dir = f;
		}
	}
	*onde = f;
	if(ehraiz)
		*Raiz = f;
		
	return true;
}
bool insere_arv_bin_2(Arvore * Raiz, int chave, NoArvBin** onde){
	NoArvBin *temp = NULL;
	Arvore *p = Raiz;
	while (*p != NULL){
		if(chave < (*p)->info){
			temp = (*p);
			p = &((*p)->esq);
		}else if(chave > (*p)->info){
			temp = (*p);
			p = &((*p)->dir);
		}else{
			return false;
		}
	}
	(*p) = (Arvore)malloc(sizeof(NoArvBin));
	(*p)->info = chave;
	(*p)->esq = NULL;
	(*p)->dir = NULL;
	(*p)->pai = temp;
	*onde = *p;
		
	return true;
}
bool remova(Set C, int chave){
	NoArvBin *onde;
	bool removivel;
	
	printf("\033[92mR:Chave\033[97m = %d:\n", chave);/** db prints2 **/
	pArv(C->elem);/** db prints2 **/

	Confere(C->elem, "R: Antes de remover:");/** db RevisaArvore **/
	removivel = remove_arv_bin(&C->elem, chave, &onde);
	if(!removivel) return false;

	Confere(C->elem, "R: Antes de afunilar:");/** db RevisaArvore **/
	pSet(&C, 1, "R: Antes de Afunilar");/** db prints3 **/

	while(afunila(onde)){
		C->elem = onde; /** apagar isso **/
		pSet(&C, 1, "R: Afunilando");/** db Afunilando **/
	}

	Confere(C->elem, "R: Depois de afunilar:");/** db RevisaArvore **/
	pSet(&C, 1, "R: Final");/** db prints3 **/
	
	C->elem = onde;
	C->tam--;
	if(C->tam < 0){
		printf("\033[91mERRO 3\033[97m\n");/** dbERROS **/
	}


	return true;
}
bool remove_arv_bin(Arvore *Raiz, int chave,  NoArvBin** onde){
	/* subs acha um substituto pra alvo */
	NoArvBin *subs = NULL, *alvo = *Raiz;
	if(*Raiz == NULL) 
		return false;
	if((*Raiz)->info == chave){
		alvo = *Raiz;
	}
	/* alvo procura nó a ser removido */
	else {
		while(alvo != NULL && alvo->info != chave){
			if(chave > alvo->info){
				alvo = alvo->dir;
			}else{
				alvo = alvo->esq;
			}
		}if(alvo == NULL) 
			return false;
	}
	/* Se alvo só tem um filho */
	if(alvo->dir == NULL){
		subs = alvo->esq;
		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = subs;
			else 
				alvo->pai->esq = subs;
		}
		if(subs) 
			subs->pai = alvo->pai;

	}else if(alvo->esq == NULL) {
		subs = alvo->dir;

		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = subs;
			else 
				alvo->pai->esq = subs;
		}
		if(subs) 
			subs->pai = alvo->pai;

	/* Se tem os dois filhos, procura pelo mais a dir da subarvore esq */
	}else{
		for(subs = alvo->esq; subs->dir != NULL; subs = subs->dir);

		subs->dir = alvo->dir;
		
		alvo->dir->pai = subs;
		alvo->esq->pai = subs;
		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = subs;
			else 
				alvo->pai->esq = subs;
		}
		
		if(subs == alvo->esq)
			alvo->esq = subs->esq;
		else	
			subs->pai->dir = subs->esq;
		
		if(subs->esq)
			subs->esq->pai = subs->pai;
		
		subs->pai = alvo->pai;
		subs->esq = alvo->esq;
		
	}
	if(alvo == *Raiz){
		*onde = *Raiz = subs;
	}else{
		*onde = alvo->pai;
	}
	free(alvo);
	return true;
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
			Confere(raiz(f), "Homogêneo: Antes de r(p)");/** db Revisa Rotações **/
			rotacao(p);
			Confere(raiz(f), "Homogêneo: Antes de r(f)");/** db Revisa Rotações **/
			rotacao(f);
			Confere(raiz(f), "Homogêneo: Depois de r(f)");/** db Revisa Rotações **/
		}else{
			Confere(raiz(f), "Heterogêneo: Antes do r(f) 1");/** db Revisa Rotações **/
			rotacao(f);
			Confere(raiz(f), "Heterogêneo: Antes do r(f) 2");/** db Revisa Rotações **/
			rotacao(f);
			Confere(raiz(f), "Heterogêneo: Depois do r(f) 2");/** db Revisa Rotações **/
		}
	}
	return true;
}
void rotacao(NoArvBin * f) {
	/* Nesse caso f é o filho esquerdo */
	if(f->pai->esq == f){
		if(f->dir) f->dir->pai = f->pai;
		f->pai->esq = f->dir;
		f->dir = f->pai;
		f->pai = f->dir->pai;
		if(f->pai){
			if(f->pai->dir == f->dir) f->pai->dir = f;
			else f->pai->esq = f;
		}
		f->dir->pai = f;
	}else{
		if(f->esq) f->esq->pai = f->pai;
		f->pai->dir = f->esq;
		f->esq = f->pai;
		f->pai = f->esq->pai;
		if(f->pai){
			if(f->pai->dir == f->esq) f->pai->dir = f;
			else f->pai->esq = f;
		}
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
void pArv(Arvore A){
	if(!A) return;
	pPre(A); printf("\n");
	pIn(A); printf("\n");
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
}
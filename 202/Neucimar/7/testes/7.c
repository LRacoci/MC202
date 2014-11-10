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
	int *v;
} VetInt;

/* TAD: Arvore Binária de Busca por Afunilamento */
/************************************************/

bool insira(Set C, int chave);
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde);
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

void pSet(Set* x, int n, char c){
	int i;
	for(i = 0; i < n; i++){
		printf("%c%d: ", c, i+1);
		if(x[i])pArv(x[i]->elem);
		printf("\n");
	}
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
				printf("\033[91mERRO\033[97m\n");
				exit(1);
			}
		}
	}
	
	for(i = 0; i < n; i++){
		/*pSet(subsets, n, 'S');*/
		M_indice = maior(subsets, n);
		M = subsets[M_indice];
		if(M_indice == -1) break;
		subsets[M_indice] = NULL;
		for(j = 0; j < n; j++){
			if(subsets[j] && subsets[j]->tam) 
				complemento(subsets[j], M);
		}
		complemento(universe, M);
		/*pSet(&universe, 1, 'U');*/
		R.v[R.tam++] = M_indice + 1;
		/*imprime_final(R);
		printf("\n");*/
	}

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
	for(i = 1; i <= u; i++)
		insira(U, i);
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
		/*printf("\033[94mmax = %d\033[97m\n", max+1);*/
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
		/*printf("\033[92mChave\033[97m = %d:\n", B_elem.v[i]);
		pArv(A->elem);*/
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
	if(R.tam > 0){
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
	bool inserivel = insere_arv_bin(&C->elem, chave, &onde);
	if(!inserivel) return false;
	
	while(afunila(onde)){
		C->elem = onde;
	}
	(C->tam)++;
	/*rintf("\033[94mI\033[97m: ");
	pArv(C->elem);*/

	return true;
}
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde){
	NoArvBin *temp = NULL;
	Arvore *p;
	p = onde;
	if (*Raiz == NULL) {
		p = Raiz;
	}
	else{
		*p = *Raiz;
		while ((*p) != NULL){
			if(chave < (*p)->info){
				temp = (*p);
				(*p) = (*p)->esq;
			}else if(chave > (*p)->info){
				temp = (*p);
				(*p) = (*p)->dir;
			}else{
				return false;
			}
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
	bool removivel = remove_arv_bin(&C->elem, chave, &onde);
	if(!removivel) return false;
	
	while(afunila(onde)){
		C->elem = onde;
	}
	C->tam--;
	
	/*printf("\033[91mR\033[97m: ");
	pArv(C->elem);*/

	return true;
}
bool remove_arv_bin(Arvore * Raiz, int chave,  NoArvBin** onde){
	/* subs acha um substituto pra alvo */
	NoArvBin *p, **subs = &p, *alvo = *Raiz;
	if(*Raiz == NULL) 
		return false;
	if((*Raiz)->info == chave) 
		subs = Raiz;
	/* alvo procura nó a ser removido */
	while(alvo != NULL && alvo->info != chave){
		if(chave > alvo->info){
			alvo = alvo->dir;
		}else{
			alvo = alvo->esq;
		}
	}if(alvo == NULL) 
		return false;
	/* remover alvo */
	*onde = alvo->pai;
	/* Se alvo só tem um filho */
	if(alvo->dir == NULL){
		(*subs) = alvo->esq;
		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = (*subs);
			else 
				alvo->pai->esq = (*subs);
		}
		if((*subs)) (*subs)->pai = alvo->pai;

	}else if(alvo->esq == NULL) {
		(*subs) = alvo->dir;

		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = (*subs);
			else 
				alvo->pai->esq = (*subs);
		}
		(*subs)->pai = alvo->pai;

	/* Se tem os dois filhos, procura pelo mais a dir da subarvore esq */
	}else{
		for((*subs) = alvo->esq; (*subs)->dir != NULL; (*subs) = (*subs)->dir);

		(*subs)->dir = alvo->dir;

		if(alvo->pai){
			if(alvo->pai->dir == alvo) 
				alvo->pai->dir = (*subs);
			else 
				alvo->pai->esq = (*subs);
		}
		
		if((*subs) == alvo->esq)
			(*subs)->pai->esq = (*subs)->esq;
		else	
			(*subs)->pai->dir = (*subs)->esq;
		
		if((*subs)->esq)
			(*subs)->esq->pai = (*subs)->pai;
		
		(*subs)->pai = alvo->pai;
		(*subs)->esq = alvo->esq;
		
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
	else printf("* ");
}
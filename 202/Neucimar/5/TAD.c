/* Cria o nó cabeça*/
void cria_lista(Head nova_lista){
	*nova_lista = (Lista)malloc(sizeof(No));
	(*nova_lista)->info = -1;
	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
/* Cria um nó e o insere no final da lista, antes do no cabeça*/
void cria_no_final(Lista ini, int info, int freq){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	novo->info = info;
	novo->freq = freq;

	novo->dir = ini;
	novo->esq = (ini)->esq;
	ini->esq = novo;
	novo->esq->dir = novo;
}
/* Cria nó e o insere depois de P*/
void cria_no_final(Lista ini, P, int info, int freq){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	novo->info = info;
	novo->freq = freq;

	novo->dir = ini;
	novo->esq = (ini)->esq;
	(ini)->esq = novo;
	novo->esq->dir = novo;
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

	A->dir->esq = A->esq;
	A->esq->dir = A->dir;
	free(A);
}
/* Desaloca uma lista inteira*/
void removeLista(Head h){
	/*(*h)->dir é a primeira posição jdá que (*h) aponta para o no cabeça*/
	Lista temp, p = (*h)->dir;
	while(p != *h){
		temp = p;
		p = p->dir;
		free(temp);
	}
	free(p);
	*h = NULL;
}

#include <stdio.h>
#include <stdlib.h>
 
typedef struct no{
	struct no *esq;
	struct no *dir;
	int valor;
}no;
 
void inserirNo(no **raiz,int elemento)
{
	if(*raiz == NULL) {
    	no *aux = (no *)malloc(sizeof(no));
    	aux->valor = elemento;
    	aux->dir = aux->esq = NULL;
    	*raiz = aux;
    	printf("Elemento %d foi inserido com sucesso.\n",elemento);
    	return;
	}
 
	if(elemento < (*raiz)->valor) {
    	inserirNo(&(*raiz)->esq,elemento);
    	return;
	}
	if(elemento > (*raiz)->valor) {
    	inserirNo(&(*raiz)->dir,elemento);
    	return;
	}
	printf("Elemento %d ja existe na arvore.\n",elemento);
}
 
no *DoisFilhos(no *root){
    	if(root == NULL)
        	return NULL;
    	else if(root->esq == NULL)
            	return root;
    	else
        	return DoisFilhos(root->esq);
}
 
void removerNo(no **raiz,int elemento)
{
	if(elemento < (*raiz)->valor){
    	removerNo(&(*raiz)->esq,elemento);
	}
	else if(elemento > (*raiz)->valor){
    	removerNo(&(*raiz)->dir,elemento);
	}
	else if((*raiz)->esq!=NULL && (*raiz)->dir != NULL){
    	no *aux= NULL;
    	aux = DoisFilhos((*raiz)->dir);
    	(*raiz)->valor = aux->valor;
    	removerNo(&(*raiz)->dir,(*raiz)->valor);
	}
	else {
    	no *aux = (*raiz);
    	if((*raiz)->esq==NULL) {
        	(*raiz) = (*raiz)->dir;
    	}
    	else {
        	*raiz = (*raiz)->esq;
    	}
    	free(aux);
	}
}
 
void pesquisaOrdemSimetrica(no *raiz)
{
	if(raiz == NULL)
    	return;
	pesquisaOrdemSimetrica(raiz->esq);
	printf("%d\n",raiz->valor);
	pesquisaOrdemSimetrica(raiz->dir);
}
 
void pesquisaPosOrdem(no *raiz)
{
	if(raiz == NULL)
    	return;
	pesquisaPosOrdem(raiz->esq);
	pesquisaPosOrdem(raiz->dir);
	printf("%d\n",raiz->valor);
}
 
void pesquisaPreOrdem(no *raiz)
{
	if(raiz == NULL)
    	return;
	printf("%d\n",raiz->valor);
	pesquisaPreOrdem(raiz->esq);
	pesquisaPreOrdem(raiz->dir);
}
 
int main()
{
	no *raiz = NULL;
	inserirNo(&raiz,5);
	inserirNo(&raiz,7);
	inserirNo(&raiz,9);
	inserirNo(&raiz,1);
	inserirNo(&raiz,2);
	removerNo(&raiz,5);
	pesquisaPreOrdem(raiz);
 
	return 0;
}
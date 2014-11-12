/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Exs */

#include <stdio.h>
#include <stdlib.h>


/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true} bool;

typedef struct Arvore{
	char info;
	struct Arvore *esq, *dir, *pai;
} NoArvBin, *Arvore;

void encontra_elemento(Arvore A, int chave,  NoArvBin** onde){
	if(A == NULL) return;
	if(A->info == chave) {
		*onde = A;
		return;
	}
	else
		encontra_elemento(A->esq, chave, onde);
		encontra_elemento(A->dir, chave, onde);
}
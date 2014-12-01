/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 09 - Árvores 2-3 (inserção) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

typedef enum bool{false, true} bool;


/*arvore23_no_t - define tipo nó de uma arvore 2-3*/
typedef struct arvore23_no {
    /*valor das chaves do no, se existirem*/
    int chave[2];
    /*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
    int nchaves;
    /*ponteiros para os nós filhos*/
    struct arvore23_no * filho[3];	
    /*ponteiro para o nó pai (não é usado na função imprime)*/
    struct arvore23_no *pai;				
} Arvore23_no, *Arvore23;

/*Novos campos podem ser acrescentados ou retirados da estrutura de dados a gosto.*/
/*Mas cuidado! Excluir um campo pode alterar a corretude da função imprime*/

/* TAD: Arvores 2-3 */
/*******************/

/* arvore23_aloca() - Cria árvore 2-3. */
Arvore23 arvore23_aloca();

/* arvore23_libera() - Libera árvore 2-3. */
void arvore23_libera(Arvore23 t);

/* arvore23_insere() - insere chave na árvore 2-3. Não insere se chave já existir na árvore */
void arvore23_insere(Arvore23 *t, int chave);

/* arvore23_busca() - busca chave na árvore 2-3. Retorna 1 se encontrar ou 0 se não encontrar */
int arvore23_busca(Arvore23 t, int chave);

/* arvore23_imprime() - imprime árvore 2-3. */
void arvore23_imprime(Arvore23 t);


/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/


/*programa que implementa arvores 2-3 com chaves inteiras*/

int main(){
    Arvore23 t;
    int i,N,chave;
    char comando[9];

    /* Cria árvore 2-3 */
    t = arvore23_aloca();
    
    /*le quantidade de entradas*/
    scanf("%d\n",&N);
    for(i = 0; i < N; i++) {
	    /*le instrução*/
		scanf("%s", comando);
		if (!strcmp(comando,"inserir")){
			scanf("%d", &chave);
	 		arvore23_insere(&t, chave);
		}
		if (!strcmp(comando,"buscar")){
			scanf("%d", &chave);
	 		if (!arvore23_busca(t, chave))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		if (!strcmp(comando,"imprimir")){
			arvore23_imprime(t);
			printf("\n");
		}
    } 
    /* libera memória */
    arvore23_libera(t);

    return 0;
}

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/


/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: Arvores 2-3 */
/*******************/


/* Cria árvore 2-3. */
Arvore23 arvore23_aloca()
{
    return NULL;
}

/* Libera árvore 2-3. */
void arvore23_libera(Arvore23 t){
    int i;
    if(t!=NULL){
		for(i = 0; i < 3; i++){
			arvore23_libera(t->filho[i]);
		}
		free(t); t=NULL;
    }
}

void arvore23_insere(Arvore23 *t, int chave){
    if(*t == NULL)/*se t for vazia*/{
    	(*t) = (Arvore23) malloc(sizeof(Arvore23_no));
    	(*t)->nchaves = 1;
		(*t)->chave[0] = chave;
    	(*t)->pai = (*t)->filho[0] = (*t)->filho[1] = (*t)->filho[2] = NULL;
	return;
    }
    if (!arvore23_busca((*t), chave)) /*se chave ja existe em árvore*/ 
	return;

	/*-------------------------------
	Completar aqui
	---------------------------------*/
}

int arvore23_busca(Arvore23 t, int chave){

	/*-------------------------------
	Completar aqui
	---------------------------------*/

    return 0;
}
void arvore23_imprime(Arvore23 t){
    if(t!=NULL){
		printf("( ");
    	if (t->nchaves == 1){
			arvore23_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvore23_imprime(t->filho[1]);
	   	}
	    else /*t->nchaves == 2*/{
			arvore23_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvore23_imprime(t->filho[1]);
			printf("%d ",t->chave[1]);
			arvore23_imprime(t->filho[2]);
		}
		printf(") ");
    }
}

void arvore23_imprime_identado(Arvore23 t){
	 arvore23_imprime_identado_aux(t, 0);
}
void arvore23_imprime_identado_aux(Arvore23 t, short int s){
	int i;
	for(i = 0; i < t->nchaves; i++){
		arvore23_imprime_identado_aux(t->filho[i], s+1);
		spaces(s); printf("%d ",t->chave[i]);
	}
	if(t->filho[i]) 
		arvore23_imprime_identado_aux(t->filho[i], s+1);
}
void spaces(short int s){
	while(s--){
		printf(" ");
	}
}
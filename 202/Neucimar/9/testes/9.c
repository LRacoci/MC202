/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 09 - Árvores 2-3 (inserção) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_CHAVES 2

typedef enum bool{false, true} bool;

/*arvore23_no_t - define tipo nó de uma arvore 2-3*/
typedef struct arvore23_no {
	/*valor das chaves do no, se existirem*/
	int chave[MAX_CHAVES];
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvore23_no * filho[MAX_CHAVES+1];	
	/*ponteiro para o nó pai (não é usado na função imprime)*/
	struct arvore23_no *pai;
} Pagina, *Arvore23;

/*Novos campos podem ser acrescentados ou retirados da estrutura de dados a gosto.*/
/*Mas cuidado! Excluir um campo pode alterar a corretude da função imprime*/

/* TAD: Arvores 2-3 */
/*******************/

/* Cria árvore 2-3. */
Arvore23 arvore23_aloca();

/* Libera árvore 2-3. */
void arvore23_libera(Arvore23 t);

/* insere chave na árvore 2-3. Não insere se chave já existir na árvore */
void arvore23_insere(Arvore23 *t, int chave);

/* insere chave numa página da árvore 2-3 */
short int insere_pagina(Arvore23 *t, int chave);

/* busca chave na árvore 2-3. Retorna 1 se encontrar ou 0 se não encontrar */
bool arvore23_busca(Arvore23 t, int chave, Arvore23* pos);

/* imprime árvore 2-3. */
void arvore23_imprime(Arvore23 t);

Arvore23 cria_pagina_arvore23();



void pVert(Arvore23 t, char* str);
void pVert_aux(Arvore23 t, short int s);
void spaces(short int s);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/


/*programa que implementa arvores 2-3 com chaves inteiras*/

int main(){
	Arvore23 t, lixo = NULL, *plixo = &lixo;
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
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			if (!arvore23_busca(t, chave, plixo))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			arvore23_imprime(t);
			printf("\n");
		}
		pVert(t, "");
		/*arvore23_imprime(t);*/
		printf("\n");
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
Arvore23 arvore23_aloca(){
	return NULL;
}

/* Libera árvore 2-3. */
void arvore23_libera(Arvore23 t){
	int i;
	if(t!=NULL){
		for(i = 0; i <= MAX_CHAVES; i++){
			arvore23_libera(t->filho[i]);
		}
		free(t);
	}
}

Arvore23 cria_pagina_arvore23(){
	int i;
	Arvore23 nova;
	nova = (Arvore23) malloc(sizeof(Pagina));
	nova->tam = 0;
	nova->pai = NULL;
	for(i = 0; i < MAX_CHAVES; i++){
		nova->filho[i] = NULL;
		nova->chave[i] = -1;
	}
	nova->filho[i] = NULL;
	
	return nova;
}

short int insere_pagina(Arvore23 *t, int chave){
	short int i, j, posicao, meio, nchaves, return_value;
	Arvore23 pai;
	if(*t == NULL) /*se t for vazia*/{
		(*t) = cria_pagina_arvore23();
		(*t)->chave[0] = chave;
		((*t)->tam)++;
		return 0;
	}if((*t)->tam < MAX_CHAVES){
		i = (*t)->tam;
		while(chave < (*t)->chave[i] && i > 1){
			(*t)->filho[i+1] = (*t)->filho[i];
			(*t)->chave[i] = (*t)->chave[i-1];	
			i--;
		}
		(*t)->chave[i] = chave;
		(*t)->tam++;
		return i;
	}else{
		/*split()*/
		meio = ((*t)->tam)/2;
		
		posicao = insere_pagina( &((*t)->pai), (*t)->chave[meio] );
		(*t)->chave[meio] = -1;
		
		pai = (*t)->pai;

		nchaves = (*t)->tam;
		((*t)->tam)--;

		pai->filho[posicao] = *t;

		pai->filho[posicao+1] = cria_pagina_arvore23();
	
		pai->filho[posicao+1]->pai = pai;

		for(j = 0, i = meio + 1; i < nchaves; i++, j++){
			pai->filho[posicao+1]->filho[j] = pai->filho[posicao]->filho[i];
			pai->filho[posicao+1]->chave[j] = pai->filho[posicao]->chave[i];
			pai->filho[posicao]->chave[i] = -1;
			pai->filho[posicao]->filho[i] = NULL;
			(pai->filho[posicao]->tam)--;
		}
		pai->filho[posicao+1]->tam = j;
		pai->filho[posicao+1]->filho[j] = pai->filho[posicao]->filho[i];
		pai->filho[posicao]->filho[i] = NULL;

		if(chave < pai->chave[posicao]){
			return_value = insere_pagina( &(pai->filho[posicao]), chave );

		}else{
			return_value = insere_pagina( &(pai->filho[posicao+1]), chave);
		}
		return return_value;
	}
}

void arvore23_insere(Arvore23 *t, int chave){
	Arvore23 inicial = NULL;
	Arvore23 *pos = &inicial;
	if(*t == NULL){ /*se t for vazia*/
		insere_pagina(t, chave);
		return;
	}
	if(arvore23_busca(*t, chave, pos)) /*se chave ja existe em árvore*/ 
		return;

	if(*pos){
		insere_pagina(pos, chave);
	}else{
		insere_pagina(t, chave);
	}
	while((*t)->pai) *t = (*t)->pai;
	
}

bool arvore23_busca(Arvore23 t, int chave, Arvore23* pos){
	short int i;
	Arvore23 p = t;
	while(p != NULL){
		for(i = 0; i < p->tam; i++){
			if(chave == p->chave[i]){
				return true;
			}else if(chave < p->chave[i]){
				break;
			}
		}
		*pos = p;
		p = p->filho[i];
	}
	return false;
}
void arvore23_imprime(Arvore23 t){
	if(t!=NULL){
		printf("( ");
		if (t->tam == 1){
			arvore23_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvore23_imprime(t->filho[1]);
		}
		else /*t->tam == 2*/{
			arvore23_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvore23_imprime(t->filho[1]);
			printf("%d ",t->chave[1]);
			arvore23_imprime(t->filho[2]);
		}
		printf(") ");
    }
}

void pVert(Arvore23 t, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(t, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);

}
void pVert_aux(Arvore23 t, short int s){
	int i;
	if(t){
		for(i = 0; i < t->tam; i++){
			pVert_aux(t->filho[i], s+2);
			spaces(s); printf("%d \n",t->chave[i]);
		}
		if(t->filho[i]){
			pVert_aux(t->filho[i], s+2);
		}
	}

}
void spaces(short int s){
	while(s--){
		printf("  ");
	}
}
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

/*arvoreB_no_t - define tipo nó de uma arvore 2-3*/
typedef struct arvoreB_no {
	/*valor das chaves do no, se existirem*/
	int chave[3];
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvoreB_no * filho[4];	
	/*ponteiro para o nó pai (não é usado na função imprime)*/
	struct arvoreB_no *pai;
} Pagina, *ArvoreB;

/*Novos campos podem ser acrescentados ou retirados da estrutura de dados a gosto.*/
/*Mas cuidado! Excluir um campo pode alterar a corretude da função imprime*/

/* TAD: Arvores 2-3 */
/*******************/

ArvoreB cria_pagina_arvoreB(short int ordem);

/* Libera árvore 2-3. */
void arvoreB_libera(ArvoreB t, short int ordem);

/* insere chave na árvore 2-3. Não insere se chave já existir na árvore */
void arvoreB_insere(ArvoreB *t, int chave);

/* insere chave numa página da árvore 2-3 */
short int insere_pagina(ArvoreB *t, int chave, short int ordem);

/* busca chave na árvore 2-3. Retorna 1 se encontrar ou 0 se não encontrar */
bool arvoreB_busca(ArvoreB t, int chave, ArvoreB* pos);

/* copia página */

ArvoreB copia_page(ArvoreB src, short int ordem);

/* imprime árvore 2-3. */
void arvoreB_imprime(ArvoreB t);





void pVert(ArvoreB t, char* str);
void pVert_aux(ArvoreB t, short int s);
void spaces(short int s);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/


/*programa que implementa arvores 2-3 com chaves inteiras*/

int main(){
	ArvoreB t = NULL, lixo = NULL, *plixo = &lixo;
	int i,N,chave;
	char comando[9];

	/*le quantidade de entradas*/
	scanf("%d\n",&N);
	for(i = 0; i < N; i++) {
	    /*le instrução*/
		scanf("%s", comando);
		if (!strcmp(comando,"inserir")){
			scanf("%d", &chave);
			
			printf("\033[93mInserir %d\033[97m\n", chave);/** db identifica **/
			
			pVert(t, "Indent"); /** db pIdent **/
			/** arvoreB_imprime(t); db pArv **/
			/** printf("\n"); db pArv **/

			arvoreB_insere(&t, chave);
		}
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			
			printf("\033[93mBuscar %d\033[97m\n", chave);/** db identifica **/
			pVert(t, "Indent"); /** db pIdent **/
			/** arvoreB_imprime(t); db pArv **/
			/** printf("\n"); db pArv **/

			if (!arvoreB_busca(t, chave, plixo))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			printf("\033[93mImprimir\033[97m\n");/** db identifica **/
			arvoreB_imprime(t);
			printf("\n");
		}
		pVert(t, "Indent"); /** db pIdent **/
		arvoreB_imprime(t);/** db pArv **/
		printf("\n");/** db pArv **/
	} 
	/* libera memória */
	arvoreB_libera(t, MAX_CHAVES);

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

/* Libera árvore 2-3. */
void arvoreB_libera(ArvoreB t, short int ordem){
	int i;
	if(t){
		for(i = 0; i <= ordem; i++){
			arvoreB_libera(t->filho[i], ordem);
		}
		/*
		free(t->chave);
		free(t->filho);
		*/
		free(t);
	}
}

ArvoreB cria_pagina_arvoreB(short int ordem){
	int i;
	ArvoreB nova;
	nova = (ArvoreB) malloc(sizeof(Pagina));
	/*
	nova->chave = (int*) malloc(sizeof(int)*  ordem);
	nova->filho = (ArvoreB*) malloc(sizeof(ArvoreB)* (ordem+1));
	*/
	nova->tam = 0;
	nova->pai = NULL;
	for(i = 0; i < ordem; i++){
		nova->chave[i] = -1;
		nova->filho[i] = NULL;
	}
	nova->filho[i] = NULL;
	
	return nova;
}

short int insere_pagina(ArvoreB *t, int chave, short int ordem){
	short int i, j, posicao, meio, return_value;
	ArvoreB pai, aux = NULL;
	if(*t == NULL) /*se t for vazia*/{
		(*t) = cria_pagina_arvoreB(ordem);
		(*t)->chave[0] = chave;
		((*t)->tam)++;
		return 0;
	}if((*t)->tam < ordem){
		i = (*t)->tam;
		while(chave < (*t)->chave[i-1] && i > 0){
			(*t)->filho[i+1] = (*t)->filho[i];
			(*t)->chave[i] = (*t)->chave[i-1];	
			i--;
		}
		(*t)->chave[i] = chave;
		(*t)->tam++;
		return i;
	}else{
		/*split()*/
		aux = copia_page(*t, ordem+1);
		return_value = insere_pagina(&aux, chave, ordem +1);

		meio = (aux->tam)/2;
		
		posicao = insere_pagina( &((*t)->pai), aux->chave[meio], ordem);
		
		pai = (*t)->pai;



		pai->filho[posicao] = *t;

		pai->filho[posicao+1] = cria_pagina_arvoreB(ordem);
	
		pai->filho[posicao+1]->pai = pai;
		for(i = 0; i < meio; i++){
			pai->filho[posicao]->filho[i] = aux->filho[i];
			pai->filho[posicao]->chave[i] = aux->chave[i];
		}
		pai->filho[posicao]->filho[meio] = aux->filho[i];
		pai->filho[posicao]->chave[meio] = -1;
		pai->filho[posicao]->tam = meio;
		for(j = 0, i = meio + 1; i < aux->tam; i++, j++){
			pai->filho[posicao+1]->filho[j] = aux->filho[i];
			pai->filho[posicao+1]->chave[j] = aux->chave[i];
			pai->filho[posicao]->chave[i] = -1;
			pai->filho[posicao]->filho[i] = NULL;
		}
		pai->filho[posicao+1]->filho[j] = aux->filho[i];
		pai->filho[posicao+1]->tam = j;

		if(aux->chave[return_value] <= pai->chave[posicao]){
			*t = pai->filho[posicao];
		}else{
			*t = pai->filho[posicao+1];
			return_value -= meio + 1;
		}
		free(aux);
		return return_value;
	}
}

ArvoreB copia_page(ArvoreB src, short int ordem){
	short int i;
	ArvoreB nova = NULL;
	if(src){
		nova = cria_pagina_arvoreB(ordem);
		nova->tam = src->tam;
		for(i = 0; i < src->tam; i++){
			nova->chave[i] = src->chave[i];
			nova->filho[i] = src->filho[i];
		}
		nova->filho[i] = src->filho[i];
	}
	return nova;
}

void arvoreB_insere(ArvoreB *t, int chave){
	ArvoreB inicial = NULL;
	ArvoreB *pos = &inicial;
	if(*t == NULL){ /*se t for vazia*/
		insere_pagina(t, chave, MAX_CHAVES);
		return;
	}
	if(arvoreB_busca(*t, chave, pos)) /*se chave ja existe em árvore*/ 
		return;

	if(*pos){
		insere_pagina(pos, chave, MAX_CHAVES);
	}else{
		insere_pagina(t, chave, MAX_CHAVES);
	}
	while((*t)->pai) *t = (*t)->pai;
	
}

bool arvoreB_busca(ArvoreB t, int chave, ArvoreB* pos){
	short int i;
	ArvoreB p = t;
	*pos = NULL;
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
void arvoreB_imprime(ArvoreB t){
	if(t!=NULL){
		printf("( ");
		if (t->tam == 1){
			arvoreB_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvoreB_imprime(t->filho[1]);
		}
		else /*t->tam == 2*/{
			arvoreB_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvoreB_imprime(t->filho[1]);
			printf("%d ",t->chave[1]);
			arvoreB_imprime(t->filho[2]);
		}
		printf(") ");
    }
}



void pVert(ArvoreB t, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(t, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);

}
void pVert_aux(ArvoreB t, short int s){
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
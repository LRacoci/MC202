/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 09 - Árvores B (inserção) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_CHAVES 2

typedef enum bool{false, true} bool;

/* Define um nó de Árvore B sem nó pai, por que este é desnecessário */
typedef struct arvB_no {
	/*valor das chaves do no, se existirem*/
	int *chave;
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvB_no ** filho;	
} Page, *ArvB;

/* TAD: Pagina de Arvore B */
/**************************/

/* Cria e inicializa uma página de Árvore B */
ArvB cria_page(short int ordem);

/* Retorna a posição que uma chave está ou deveria 
 * estar, também se a chave foi encontrada */
short int busca_page(ArvB pagina, int chave, bool *achou);

/* Copia página */
ArvB copia_page(ArvB src, short int ordem);

/* Insere a chave na árvore com ajuda das 
 * funções promove, split, busca, insere_pagina */
void insere_chave(ArvB pagina, int chave, ArvB filho_dir);

/* Divide o nó temp criado na função em page e new_page */
void split(int i_chave, ArvB i_RRN, ArvB page, int *promove_chave, ArvB *filho_dir, short int ordem);


/* TAD: Arvores B */
/*******************/

/* Libera árvore B. */
void arvB_libera(ArvB pagina, short int ordem);

/* Insere chave na árvore B. Não insere se chave já existir na árvore */
void arvB_insere(ArvB *raiz, int chave, short int ordem);

/* Retorna true se a chave foi achada e false se não foi */
bool arvB_busca(ArvB pagina, int chave);

/* imprime árvore B. */
void arvB_imprime(ArvB pagina);

/* Essa é a função insere das folhas do neucimar eu sh mudei o nome por causa do retorno */
bool promove(ArvB atual, int chave, ArvB *filho_dir, int *promove_chave, short int ordem);



/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

/* Funções pra imprimir identado (debugação) */
void pVert(ArvB pagina, char* str);
void pVert_aux(ArvB pagina, short int s);
void spaces(short int s);

/* Programa que implementa Arvores B com chaves inteiras na memória */
int main(){
	ArvB pagina = NULL;
	int i, N, chave;
	char comando[9];

	/*le quantidade de entradas*/
	scanf("%d\n",&N);
	for(i = 0; i < N; i++) {
	    /*le instrução*/
		scanf("%s", comando);
		if (!strcmp(comando,"inserir")){
			scanf("%d", &chave);
			
			/** printf("\033[93mInserir %d\033[97m\n", chave); db identifica **/
			
			/** pVert(pagina, "Indent");  db pIdent **/
			/** arvB_imprime(pagina); db pArv **/
			/** printf("\n"); db pArv **/

			arvB_insere(&pagina, chave, MAX_CHAVES);
		}
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			
			/** printf("\033[93mBuscar %d\033[97m\n", chave); db identifica **/
			/** pVert(pagina, "Indent");  db pIdent **/
			/** arvB_imprime(pagina); db pArv **/
			/** printf("\n"); db pArv **/

			if (!arvB_busca(pagina, chave))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			/** printf("\033[93mImprimir\033[97m\n"); db identifica **/
			arvB_imprime(pagina);
			printf("\n");
		}
		/** pVert(pagina, "Indent");  db pIdent **/
		/** arvB_imprime(pagina); db pArv **/
		/** printf("\n"); db pArv **/
	} 
	/* libera memória */
	arvB_libera(pagina, MAX_CHAVES);

    return 0;
}

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/* Funções para imprimir a arvore identada na vertical */
                 /* (As próximas 3) */
void pVert(ArvB pagina, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(pagina, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
}
void pVert_aux(ArvB pagina, short int s){
	int i;
	if(pagina){
		for(i = 0; i < pagina->tam; i++){
			pVert_aux(pagina->filho[i], s+2);
			spaces(s); printf("%d \n",pagina->chave[i]);
		}
		if(pagina->filho[i]){
			pVert_aux(pagina->filho[i], s+2);
		}
	}
}
void spaces(short int s){
	while(s--){
		printf("  ");
	}
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: Arvores B */
/*****************/

/* Libera árvore B. */
void arvB_libera(ArvB pagina, short int ordem){
	int i;
	if(pagina){
		for(i = 0; i <= ordem; i++){
			arvB_libera(pagina->filho[i], ordem);
		}
		free(pagina->chave);
		free(pagina->filho);
		free(pagina);
	}
}
/* Função auxiliar de arvB_insere, é a funcção insere 
 * que o Neucimar passou, mudei o nome por causa do retorno */
bool promove(ArvB atual, int chave, ArvB *filho_dir, int *promove_chave, short int ordem){
	bool return_value, achou;
	ArvB p_b_RRN;
	short int pos;
	int p_b_chave;

	if(atual == NULL){
		*promove_chave = chave;
		*filho_dir = NULL;
		return true;
	}
	/*POS = posição onde árvore está ou deveria estar*/
	pos = busca_page(atual, chave, &achou);
	/*se chave ja existe na página*/ 
	if(achou) 
		return false;

	return_value = promove(atual->filho[pos], chave, &p_b_RRN, &p_b_chave, ordem);
	if(!return_value){
		return return_value;
	}else if(atual->tam < ordem){
		insere_chave(atual, p_b_chave, p_b_RRN);
		return false;
	}else{
		split(p_b_chave, p_b_RRN, atual, promove_chave, filho_dir, ordem);
		return true;
	}
	return false;
}
/* Tradução do pseudo código passado em sala de aula */
void arvB_insere(ArvB *raiz, int chave, short int ordem){
	ArvB filho_dir, nova_raiz = NULL;
	int promove_chave;
	if(*raiz == NULL){ 
		(*raiz) = cria_page(ordem);
		(*raiz)->chave[0] = chave;
		((*raiz)->tam)++;
	}
	/* É verificado se o nó está na página durante 
	 * a função promove conforme passado em sala de aula */
	if(promove(*raiz, chave, &filho_dir, &promove_chave, ordem)){
		arvB_insere(&nova_raiz, promove_chave, ordem);
		nova_raiz->filho[0] = *raiz;
		nova_raiz->filho[1] = filho_dir;
		*raiz = nova_raiz;
	}
}

/* Retorna true se a chave foi achada e false se não foi */
bool arvB_busca(ArvB pagina, int chave){
	short int i;
	ArvB p = pagina;
	while(p != NULL){
		for(i = 0; i < p->tam; i++){
			if(chave == p->chave[i]){
				return true;
			}else if(chave < p->chave[i]){
				break;
			}
		}
		p = p->filho[i];
	}
	return false;
}

/* Função não alterada, essa é a única 
 * função que só funciona com Arvores 2-3 */
void arvB_imprime(ArvB pagina){
	if(pagina!=NULL){
		printf("( ");
		if (pagina->tam == 1){
			arvB_imprime(pagina->filho[0]);
			printf("%d ",pagina->chave[0]);
			arvB_imprime(pagina->filho[1]);
		}
		else /*pagina->tam == 2*/{
			arvB_imprime(pagina->filho[0]);
			printf("%d ",pagina->chave[0]);
			arvB_imprime(pagina->filho[1]);
			printf("%d ",pagina->chave[1]);
			arvB_imprime(pagina->filho[2]);
		}
		printf(") ");
    }
}

/* TAD: Pagina de Arvore B */
/**************************/

/* Cria e inicializa uma nova página */
ArvB cria_page(short int ordem){
	int i;
	ArvB nova;
	nova = (ArvB) malloc(sizeof(Page));

	nova->chave = (int*) malloc(sizeof(int)*  ordem);
	nova->filho = (ArvB*) malloc(sizeof(ArvB)* (ordem+1));

	nova->tam = 0;
	for(i = 0; i < ordem; i++){
		nova->chave[i] = -1;
		nova->filho[i] = NULL;
	}
	nova->filho[i] = NULL;
	
	return nova;
}
/* Insere uma chave e seu filho direito em uma página */
void insere_chave(Page *pagina, int chave, ArvB filho_dir){
	int i;
	
	/* realiza o remanejamento para manter as chave ordenadas */
	for(i = pagina->tam; i > 0 && pagina->chave[i-1] > chave; i--){
		pagina->chave[i] = pagina->chave[i-1];
		pagina->filho[i+1] = pagina->filho[i];
	}
	/* insere a chave na posição ideal */
	pagina->chave[i] = chave;
	pagina->filho[i+1] = filho_dir;
	pagina->tam++;
}

short int busca_page(ArvB pagina, int chave, bool *achou){
	short int pos;
	*achou = false;
	for(pos = 0; pos < pagina->tam; pos++){
		if(chave <= pagina->chave[pos]){
			if(chave == pagina->chave[pos]){
				*achou = true;
			}
			return pos;
		}
	}
	return pos;
}

/* Tradução do pseudo código passado em sala de aula */
void split(int i_chave, ArvB i_RRN, ArvB page, int *promove_chave, ArvB *filho_dir, short int ordem){
	short int i, j, meio, tam;
	ArvB temp, new_page;
	
	temp = copia_page(page, ordem + 1);
	insere_chave(temp, i_chave, i_RRN);
	
	new_page = cria_page(ordem);
	*filho_dir = new_page;

	meio = temp->tam/2;
	*promove_chave = temp->chave[meio];
	
	for(i = 0; i < meio; i++){
		page->filho[i] = temp->filho[i];
		page->chave[i] = temp->chave[i]; 
	}
	page->filho[i] = temp->filho[i];
	tam = page->tam;
	page->tam = i;

	for(i = meio; i < tam; i++){
		page->filho[i+1] = NULL;
		page->chave[i] = -1; 
	}
	
	for(i = 0, j = meio + 1; j < temp->tam; i++, j++){
		new_page->filho[i] = temp->filho[j];
		new_page->chave[i] = temp->chave[j];
	}
	new_page->filho[i] = temp->filho[j];
	new_page->tam = i;
	free(temp);
}

/* Retorna uma copia de src, com os mesmos filhos, e não copia dos filhos */
ArvB copia_page(ArvB src, short int ordem){
	short int i;
	ArvB nova = NULL;
	if(src){
		nova = cria_page(ordem);
		nova->tam = src->tam;
		for(i = 0; i < src->tam; i++){
			nova->chave[i] = src->chave[i];
			nova->filho[i] = src->filho[i];
		}
		nova->filho[i] = src->filho[i];
	}
	return nova;
}

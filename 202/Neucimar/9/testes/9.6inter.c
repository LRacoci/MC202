/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 09 - Árvores 2-3 (inserção) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_CHAVES 2
#define MIN_OCUP 1

typedef enum bool{false, true} bool;

/*arvB_no_t - define tipo nó de uma arv 2-3*/
typedef struct arvB_no {
	/*valor das chaves do no, se existirem*/
	int chave[3];
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvB_no * filho[4];	
	/*struct arvB_no * pai;*/
} Page, *ArvB;

/*Novos campos podem ser acrescentados ou retirados da estrutura de dados a gosto.*/
/*Mas cuidado! Excluir um campo pode alterar a corretude da função imprime*/

/* TAD: Arvores 2-3 */
/*******************/

ArvB cria_page(short int ordem);

/* Libera árvore 2-3. */
void arvB_libera(ArvB atual, short int ordem);

/* insere chave na árvore 2-3. Não insere se chave já existir na árvore */
void arvB_insere(ArvB *raiz, int chave, short int ordem);

/* insere chave numa página da árvore 2-3 */
short int insere_pagina(ArvB *atual, int chave, short int ordem);

/* busca chave na árvore 2-3. Retorna true se encontrar ou false se não encontrar */
bool arvB_busca(ArvB atual, int chave, ArvB* RRN_pos, short int* i_pos);

/* busca numa pagina e retorna a posição que a chave esta ou deveria estar */
short int busca_page(ArvB t, int chave);

/* copia página */
ArvB copia_page(ArvB src, short int ordem);

/* imprime árvore 2-3. */
void arvB_imprime(ArvB atual);

void insere_chave(ArvB atual, int chave, ArvB filho_dir);

bool promove(ArvB atual, int chave, ArvB *filho_dir, int *promove_chave, short int ordem);

void split(int i_chave, ArvB i_RRN, ArvB page, int *promove_chave, ArvB *filho_dir);



void pVert(ArvB atual, char* str);
void pVert_aux(ArvB atual, short int s);
void spaces(short int s);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/


/*programa que implementa arvs 2-3 com chaves inteiras*/

int main(){
	ArvB atual = NULL, lixo = NULL, *plixo = &lixo;
	int i, N, chave;
	short int lixo2;
	char comando[9];

	/*le quantidade de entradas*/
	scanf("%d\n",&N);
	for(i = 0; i < N; i++) {
	    /*le instrução*/
		scanf("%s", comando);
		if (!strcmp(comando,"inserir")){
			scanf("%d", &chave);
			
			printf("\033[93mInserir %d\033[97m\n", chave);/** db identifica **/
			
			pVert(atual, "Indent"); /** db pIdent **/
			/** arvB_imprime(atual); db pArv **/
			/** printf("\n"); db pArv **/

			arvB_insere(&atual, chave, MAX_CHAVES);
		}
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			
			printf("\033[93mBuscar %d\033[97m\n", chave);/** db identifica **/
			pVert(atual, "Indent"); /** db pIdent **/
			/** arvB_imprime(atual); db pArv **/
			/** printf("\n"); db pArv **/

			if (!arvB_busca(atual, chave, plixo, &lixo2))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			printf("\033[93mImprimir\033[97m\n");/** db identifica **/
			arvB_imprime(atual);
			printf("\n");
		}
		pVert(atual, "Indent"); /** db pIdent **/
		arvB_imprime(atual);/** db pArv **/
		printf("\n");/** db pArv **/
	} 
	/* libera memória */
	arvB_libera(atual, MAX_CHAVES);

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
void arvB_libera(ArvB atual, short int ordem){
	int i;
	if(atual){
		for(i = 0; i <= ordem; i++){
			arvB_libera(atual->filho[i], ordem);
		}
		/*
		free(atual->chave);
		free(atual->filho);
		*/
		free(atual);
	}
}

ArvB cria_page(short int ordem){
	int i;
	ArvB nova;
	nova = (ArvB) malloc(sizeof(Page));
	/*
	nova->chave = (int*) malloc(sizeof(int)*  ordem);
	nova->filho = (ArvB*) malloc(sizeof(ArvB)* (ordem+1));
	*/
	nova->tam = 0;
	/*nova->pai = NULL;*/
	for(i = 0; i < ordem; i++){
		nova->chave[i] = -1;
		nova->filho[i] = NULL;
	}
	nova->filho[i] = NULL;
	
	return nova;
}

void insere_chave(ArvB atual, int chave, ArvB filho_dir){
	int i;
	/* realiza o remanejamento para manter as chave ordenadas */
	for(i = atual->tam; (i > 0) && (atual->chave[i-1] > chave); i--){
		atual->chave[i] = atual->chave[i-1];
		atual->filho[i+1] = atual->filho[i];
	}
	/* insere a chave na posição ideal */
	atual->chave[i] = chave;
	atual->filho[i+1] = filho_dir;
	atual->tam++;
}

bool promove(ArvB atual, int chave, ArvB *filho_dir, int *promove_chave, short int ordem){
	bool return_value;
	ArvB p_b_RRN, pos_rrn;
	short int pos;
	int p_b_chave;
	if(atual == NULL){
		*promove_chave = chave;
		*filho_dir = NULL;
		return true;
	}
	if(arvB_busca(atual, chave, &pos_rrn, &pos)) /*se chave ja existe em árvore*/ 
		return false;

	return_value = promove(atual->filho[pos], chave, &p_b_RRN, &p_b_chave, ordem);
	if(!return_value){
		return return_value;
	}else if(atual->tam < ordem){
		insere_chave(atual, p_b_chave, p_b_RRN);
		return false;
	}else{
		split(p_b_chave, p_b_RRN, atual, promove_chave, filho_dir);
		return true;
	}
	return false;
}

ArvB insere(ArvB atual, int chave, bool *promove, int *promove_chave, short int ordem){
	/* auxiliar para armazenar a chave que irá subir para o pai */
	int chave_meio; 
	/* ponteiro para o filho à direita da chave  */
	ArvB new_page, filho_dir; 
	short int i, pos;

	/*ArvB inicial = NULL, *RRN_achado = &inicial;*/
	
	if(atual == NULL){
		/* O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha) */
		*promove = true;
		*promove_chave = chave;
		return NULL;
	}
	pos = busca_page(atual,chave);
	
	if(atual->tam > pos && atual->chave[pos] == chave){
         *promove = false;
         return NULL;
	}
	/* desce na árvore até encontrar o nó folha para inserir a chave. */
	filho_dir = insere(atual->filho[pos],chave, promove, promove_chave, ordem);
	 /* Se promove for true deve inserir a promove_chave no nó. */
	if(*promove){
		/* Tem espaço na página */
		if(atual->tam < ordem) {
			insere_chave(atual, *promove_chave, filho_dir);
			*promove = false;
		/* Overflow. Precisa subdividir */
		}else{ 
			/*split()*/
			new_page = (ArvB ) malloc(sizeof(ArvB));
			new_page->tam = 0;
			/* inicializa filho com NULL */
			for(i = 0; i < ordem; i++)
				new_page->filho[i] = NULL;

			
			/* elemento mediano que vai subir para o pai */
			chave_meio = atual->chave[MIN_OCUP];

			/* insere metade do nó atual no new_page (efetua subdivisão) */
			new_page->filho[0] = atual->filho[MIN_OCUP+1];
			for(i = MIN_OCUP + 1; i < ordem; i++)
				insere_chave(new_page, atual->chave[i], atual->filho[i+1]);

			/* atualiza nó atual.  */
			for(i = MIN_OCUP; i < ordem; i++){
				atual->chave[i] = 0;
				atual->filho[i+1] = NULL;
			}
			atual->tam = MIN_OCUP;

			/* Verifica em qual nó será inserida a nova chave */
			if(pos <= MIN_OCUP){
				insere_chave(atual, *promove_chave, filho_dir);
			}else {
				insere_chave(new_page, *promove_chave, filho_dir);
			}

			/* retorna o mediano para inserí-lo no nó pai e o new_page como filho direito do mediano. */
			*promove_chave = chave_meio;
			return new_page;
		}
	}
	return NULL;
}

void split(int i_chave, ArvB i_RRN, ArvB page, int *promove_chave, ArvB *filho_dir){
	short int i, j, meio, tam;
	ArvB temp, new_page;
	
	temp = copia_page(page, MAX_CHAVES + 1);
	insere_chave(temp, i_chave, i_RRN);
	
	new_page = cria_page(MAX_CHAVES);
	*filho_dir = new_page;

	meio = temp->tam/2;
	*promove_chave = temp->chave[meio];
	
	for(i = 0; i < meio; i++){
		page->filho[i] = temp->filho[i];
		page->chave[i] = temp->chave[i]; 
	}
	page->chave[i] = temp->chave[i];
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
	page->filho[i] = NULL;
	new_page->tam = i;
	free(temp);
}

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
/* NOVA */
void arvB_insere(ArvB *raiz, int chave, short int ordem){
	bool promove;
	ArvB filho_dir, nova_raiz = NULL;
	int promove_chave;
	/*se *raiz for vazia*/
	if(*raiz == NULL){ 
		(*raiz) = cria_page(ordem);
		(*raiz)->chave[0] = chave;
		((*raiz)->tam)++;
	}
	filho_dir = insere(*raiz, chave, &promove, &promove_chave, ordem);
	/* Aumetará a altura da árvore */
	if(promove){
 		arvB_insere(&nova_raiz, promove_chave, ordem);
 		nova_raiz->filho[0] = *raiz;
 		nova_raiz->filho[1] = filho_dir;
 		*raiz = nova_raiz;
 	}
}

/*MODIFICADA*/
void arvB_insere2(ArvB *raiz, int chave, short int ordem){
	ArvB inicial = NULL, *RRN_achado = &inicial;
	ArvB filho_dir, nova_raiz = NULL;
	int promove_chave;
	short int k;
	if(*raiz == NULL){ /*se raiz for vazia*/
		(*raiz) = cria_page(ordem);
		(*raiz)->chave[0] = chave;
		((*raiz)->tam)++;
	}
	/*se chave ja existe em árvore*/ 
	if(arvB_busca(*raiz, chave, RRN_achado, &k)) 
		return;
	
	if(promove(*raiz, chave, &filho_dir, &promove_chave, ordem)){
		arvB_insere(&nova_raiz, promove_chave, ordem);
		nova_raiz->filho[0] = *raiz;
		nova_raiz->filho[1] = filho_dir;
		*raiz = nova_raiz;
	}
	/*if(*pos){
		insere_pagina(pos, chave, MAX_CHAVES);
	}else{
		insere_pagina(atual, chave, MAX_CHAVES);
	}
	while((*atual)->pai) *atual = (*atual)->pai;*/
	
}
short int busca_page(ArvB t, int chave){
	short int pos;
	for(pos = 0; pos < t->tam; pos++){
		if(chave <= t->chave[pos]){
			return pos;
		}
	}
	return pos;
}
/*MODIFICADA*/
bool arvB_busca(ArvB atual, int chave, ArvB* RRN_pos, short int* i_pos){
	short int i;
	ArvB p = atual;
	*RRN_pos = NULL;
	while(p != NULL){
		for(i = 0; i < p->tam; i++){
			if(chave == p->chave[i]){
				*i_pos = i;
				*RRN_pos = p;
				return true;
			}else if(chave < p->chave[i]){
				*i_pos = i;
				break;
			}else{
				*i_pos = i+1;
			}
		}
		*RRN_pos = p;
		p = p->filho[i];
	}
	return false;
}

void arvB_imprime(ArvB atual){
	if(atual!=NULL){
		printf("( ");
		if (atual->tam == 1){
			arvB_imprime(atual->filho[0]);
			printf("%d ",atual->chave[0]);
			arvB_imprime(atual->filho[1]);
		}
		else /*atual->tam == 2*/{
			arvB_imprime(atual->filho[0]);
			printf("%d ",atual->chave[0]);
			arvB_imprime(atual->filho[1]);
			printf("%d ",atual->chave[1]);
			arvB_imprime(atual->filho[2]);
		}
		printf(") ");
    }
}

void pVert(ArvB atual, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(atual, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);

}
void pVert_aux(ArvB atual, short int s){
	int i;
	if(atual){
		for(i = 0; i < atual->tam; i++){
			pVert_aux(atual->filho[i], s+2);
			spaces(s); printf("%d \n",atual->chave[i]);
		}
		if(atual->filho[i]){
			pVert_aux(atual->filho[i], s+2);
		}
	}

}
void spaces(short int s){
	while(s--){
		printf("  ");
	}
}
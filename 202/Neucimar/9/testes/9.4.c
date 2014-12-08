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

/*arvB_no_t - define tipo nó de uma arvore 2-3*/
typedef struct arvB_no {
	/*valor das chaves do no, se existirem*/
	int chave[3];
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvB_no * filho[4];	
	/*ponteiro para o nó pai (não é usado na função imprime)*/
	struct arvB_no *pai;
} Page, *ArvB;

/*Novos campos podem ser acrescentados ou retirados da estrutura de dados a gosto.*/
/*Mas cuidado! Excluir um campo pode alterar a corretude da função imprime*/

/* TAD: Arvores 2-3 */
/*******************/

ArvB cria_page(short int ordem);

/* Libera árvore 2-3. */
void arvB_free(ArvB t, short int ordem);

/* insere chave na árvore 2-3. Não insere se chave já existir na árvore */
void arvB_insere(ArvB *t, int chave);

/* insere chave numa página da árvore 2-3 */
short int insere_page(ArvB  *t, int chave, short int ordem, 
                      ArvB **f_esq, ArvB **f_dir);

/* busca chave na árvore 2-3. Retorna 1 se encontrar ou 0 se não encontrar */
bool arvB_busca(ArvB t, int chave, ArvB* pos);

/* copia página */

ArvB copia_page(ArvB src, short int ordem);

/* imprime árvore 2-3. */
void arvB_imprime(ArvB t);





void pVert(ArvB t, char* str);
void pVert_aux(ArvB t, short int s);
void spaces(short int s);

/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/


/*programa que implementa arvores 2-3 com chaves inteiras*/

int main(){
	ArvB t = NULL, lixo = NULL, *plixo = &lixo;
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
			/** arvB_imprime(t); db pArv **/
			/** printf("\n"); db pArv **/

			arvB_insere(&t, chave);
		}
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			
			printf("\033[93mBuscar %d\033[97m\n", chave);/** db identifica **/
			pVert(t, "Indent"); /** db pIdent **/
			/** arvB_imprime(t); db pArv **/
			/** printf("\n"); db pArv **/

			if (!arvB_busca(t, chave, plixo))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			printf("\033[93mImprimir\033[97m\n");/** db identifica **/
			arvB_imprime(t);
			printf("\n");
		}
		pVert(t, "Indent"); /** db pIdent **/
		arvB_imprime(t);/** db pArv **/
		printf("\n");/** db pArv **/
	} 
	/* libera memória */
	arvB_free(t, MAX_CHAVES);

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
void arvB_free(ArvB t, short int ordem){
	int i;
	if(t){
		for(i = 0; i <= ordem; i++){
			arvB_free(t->filho[i], ordem);
		}
		/*
		free(t->chave);
		free(t->filho);
		*/
		free(t);
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
	nova->pai = NULL;
	for(i = 0; i < ordem; i++){
		nova->chave[i] = -1;
		nova->filho[i] = NULL;
	}
	nova->filho[i] = NULL;
	
	return nova;
}

short int insere_page(ArvB  *t, int chave, short int ordem, 
                      ArvB **f_esq, ArvB **f_dir){
	
	short int i, j, a, meio;
	ArvB pai, aux = NULL, *lixo;

	if(*t == NULL) /*se t for vazia*/{
		(*t) = cria_page(ordem);
		(*t)->chave[0] = chave;
		((*t)->tam)++;
		
		*f_esq = &((*t)->filho[0]);
		(*t)->filho[0]->pai = **f_esq;
		*f_dir = &((*t)->filho[1]);
		(*t)->filho[1]->pai = **f_dir;

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
		
		*f_esq = &((*t)->filho[i]);
		(*t)->filho[i]->pai = **f_esq;
		*f_dir = &((*t)->filho[i+1]);
		(*t)->filho[i+1]->pai = **f_dir;

		return i;

	}else{
		/*split()*/
		aux = copia_page(*t, ordem+1);
		a = insere_page(&aux, chave, ordem +1, &lixo, &lixo);

		meio = (aux->tam)/2;

		insere_page( &((*t)->pai), aux->chave[meio], ordem, f_esq, f_dir);
		
		for(i = 0; i < meio; i++){
			(**f_esq)->filho[i] = aux->filho[i];
			(**f_esq)->chave[i] = aux->chave[i];
		}
		(**f_esq)->filho[meio] = aux->filho[i];
		(**f_esq)->chave[meio] = -1;
		(**f_esq)->tam = meio;
		for(j = 0, i = meio + 1; i < aux->tam; i++, j++){
			(**f_dir)->filho[j] = aux->filho[i];
			(**f_dir)->chave[j] = aux->chave[i];
			(**f_esq)->chave[i] = -1;
			(**f_esq)->filho[i] = NULL;
		}
		(**f_dir)->filho[j] = aux->filho[i];
		(**f_dir)->tam = j;

		if(chave <= aux->chave[meio]){
			*t = **f_esq;
			
			*f_esq = &((*t)->filho[a]);
			(*t)->filho[a]->pai = **f_esq;
			*f_dir = &((*t)->filho[a+1]);
			(*t)->filho[a+1]->pai = **f_dir;

			return a;
		}/*else if(chave == aux->chave[meio]){

		}*/else{
			a -= meio + 1;
			*t = **f_dir;
			
			*f_esq = &((*t)->filho[a]);
			(*t)->filho[a]->pai = **f_esq;
			*f_dir = &((*t)->filho[a+1]);
			(*t)->filho[a+1]->pai = **f_dir;
		}

		free(aux);
		
		return a;

	}
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

void arvB_insere(ArvB *t, int chave){
	ArvB inicial_1 = NULL, inicial_2;
	ArvB *pos = &inicial_1, *lixo = &inicial_2;
	if(*t == NULL){ /*se t for vazia*/
		insere_page(t, chave, MAX_CHAVES, &lixo, &lixo);
		return;
	}
	if(arvB_busca(*t, chave, pos)) /*se chave ja existe em árvore*/ 
		return;

	if(*pos){
		insere_page(pos, chave, MAX_CHAVES, &lixo, &lixo);
	}else{
		insere_page(t, chave, MAX_CHAVES, &lixo, &lixo);
	}
	while((*t)->pai) *t = (*t)->pai;
	
}

bool arvB_busca(ArvB t, int chave, ArvB* pos){
	short int i;
	ArvB p = t;
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
void arvB_imprime(ArvB t){
	if(t!=NULL){
		printf("( ");
		if (t->tam == 1){
			arvB_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvB_imprime(t->filho[1]);
		}
		else /*t->tam == 2*/{
			arvB_imprime(t->filho[0]);
			printf("%d ",t->chave[0]);
			arvB_imprime(t->filho[1]);
			printf("%d ",t->chave[1]);
			arvB_imprime(t->filho[2]);
		}
		printf(") ");
    }
}



void pVert(ArvB t, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(t, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);

}
void pVert_aux(ArvB t, short int s){
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
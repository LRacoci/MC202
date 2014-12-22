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
	/* valor das chaves do no, se existirem
	 * Aloca-se uma a mais para o no temp da split */
	int chave[MAX_CHAVES+1];
	/*numero de chaves existentes no nó. (Pode ser 1 ou 2) */
	int tam;
	/*ponteiros para os nós filhos*/
	struct arvB_no * filho[MAX_CHAVES+2];	
} Page, *ArvB;

/* TAD: Pagina de Arvore B */
/**************************/

/* Cria e inicializa uma página de Árvore B */
ArvB cria_page(short int ordem);

/* Retorna a posição que uma chave está ou deveria 
 * estar, também se a chave foi encontrada */
short int busca_page(ArvB tree, int chave, bool *achou);

/* Copia página */
ArvB copia_page(ArvB src, short int ordem);

/* Insere a chave na árvore com ajuda das 
 * funções promove, split, busca, insere_tree */
void insere_chave(ArvB tree, int chave, ArvB filho_dir);

/* Divide o nó temp criado na função em page e new_page */
void split(int i_chave, ArvB i_RRN, ArvB page, int *promove_chave, ArvB *filho_dir, short int ordem);


/* TAD: Arvores B */
/*******************/

/* Libera árvore B. */
void arvB_libera(ArvB tree, short int ordem);

/* Insere chave na árvore B. Não insere se chave já existir na árvore */
void arvB_insere(ArvB *raiz, int chave, short int ordem);

/* Retorna true se a chave foi achada e false se não foi */
bool arvB_busca(ArvB tree, int chave);

/* imprime árvore B. */
void arvB_imprime(ArvB tree);

/* Essa é a função insere das folhas do neucimar eu sh mudei o nome por causa do retorno */
bool promove(ArvB atual, int chave, ArvB *filho_dir, int *promove_chave, short int ordem);



/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

/* Funções pra imprimir identado (debugação) */
void pVert(ArvB tree, char* str);
void pVert_aux(ArvB tree, short int s);
void spaces(short int s);

/* Programa que implementa Arvores B com chaves inteiras na memória */
int main(){
	ArvB arvore = NULL;
	int i, N, chave;
	char comando[9];

	/*le quantidade de entradas*/
	scanf("%d\n",&N);
	for(i = 0; i < N; i++) {
	    /*le instrução*/
		scanf("%s", comando);
		if (!strcmp(comando,"inserir")){
			scanf("%d", &chave);
			
			arvB_insere(&arvore, chave, MAX_CHAVES);
		}
		else if(!strcmp(comando,"buscar")){
			scanf("%d", &chave);
			if (!arvB_busca(arvore, chave))
				printf(":(\n");
			else
				printf(":)\n");		
		}
		else if(!strcmp(comando,"imprimir")){
			/** printf("\033[93mImprimir\033[97m\n"); db identifica **/
			arvB_imprime(arvore);
			printf("\n");
		}
	} 
	/* libera memória */
	arvB_libera(arvore, MAX_CHAVES);

    return 0;
}

/* IMPLEMENTAÇÃO DES OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/* Funções para imprimir a arvore identada na vertical */
                 /* (As próximas 3) */
void pVert(ArvB tree, char* str){
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
	 pVert_aux(tree, 2);
	 printf("\033[94m/*** %s ***/\033[97m\n", str);
}
void pVert_aux(ArvB tree, short int s){
	int i;
	if(tree){
		for(i = 0; i < tree->tam; i++){
			pVert_aux(tree->filho[i], s+2);
			spaces(s); printf("%d \n",tree->chave[i]);
		}
		if(tree->filho[i]){
			pVert_aux(tree->filho[i], s+2);
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
void arvB_libera(ArvB tree, short int ordem){
	int i;
	if(tree){
		for(i = 0; i <= ordem; i++){
			arvB_libera(tree->filho[i], ordem);
		}
		free(tree);
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
	/*POS = posição onde chave está ou deveria estar*/
	pos = busca_page(atual, chave, &achou);
	/*se chave ja existe na página*/ 
	if(achou) 
		return false;

	/* Retorna se há algo a promover */
	return_value = promove(atual->filho[pos], chave, &p_b_RRN, &p_b_chave, ordem);
	
	if(!return_value){
		return false;
	/* Se há espaço pra inserção do que foi promovido */
	}else if(atual->tam < ordem){
		insere_chave(atual, p_b_chave, p_b_RRN);
		return false;
	/* Senão o nó é quebrado novamente */
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
	/* Verifica se deve-se promover o que foi devolvido em filho_dir e em promove_chave */
	if(promove(*raiz, chave, &filho_dir, &promove_chave, ordem)){
		arvB_insere(&nova_raiz, promove_chave, ordem);
		nova_raiz->filho[0] = *raiz;
		nova_raiz->filho[1] = filho_dir;
		*raiz = nova_raiz;
	}
}

/* Retorna true se a chave foi achada e false se não foi */
bool arvB_busca(ArvB tree, int chave){
	short int i;
	ArvB p = tree;
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
void arvB_imprime(ArvB tree){
	if(tree!=NULL){
		printf("( ");
		if (tree->tam == 1){
			arvB_imprime(tree->filho[0]);
			printf("%d ",tree->chave[0]);
			arvB_imprime(tree->filho[1]);
		}
		else /*tree->tam == 2*/{
			arvB_imprime(tree->filho[0]);
			printf("%d ",tree->chave[0]);
			arvB_imprime(tree->filho[1]);
			printf("%d ",tree->chave[1]);
			arvB_imprime(tree->filho[2]);
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

	nova->tam = 0;
	for(i = 0; i < ordem; i++){
		nova->chave[i] = -1;
		nova->filho[i] = NULL;
	}
	nova->filho[i] = NULL;
	
	return nova;
}
/* Insere uma chave e seu filho direito em uma página */
void insere_chave(Page *tree, int chave, ArvB filho_dir){
	int i;
	
	/* realiza o remanejamento para manter as chave ordenadas */
	for(i = tree->tam; i > 0 && tree->chave[i-1] > chave; i--){
		tree->chave[i] = tree->chave[i-1];
		tree->filho[i+1] = tree->filho[i];
	}
	/* insere a chave na posição ideal */
	tree->chave[i] = chave;
	tree->filho[i+1] = filho_dir;
	tree->tam++;
}

short int busca_page(ArvB tree, int chave, bool *achou){
	short int pos;
	*achou = false;
	for(pos = 0; pos < tree->tam; pos++){
		if(chave <= tree->chave[pos]){
			if(chave == tree->chave[pos]){
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

/* Nome: Lucas Alves Racoci
* RA: 156331 
* Laboratorio 01 - O problema do acesso à lista */


#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */ 
/*************************************************************/
typedef struct No{
	int info;
	int freq;
	struct No *dir, *esq;
} No, *Lista, **Head; 

/*Funções básicas de lista, só as necessárias*/
void cria_lista(Head nova_lista);
void cria_no(Lista ini, int info, int freq);
void RemoveLista(Lista * p);
void Realoca_no(Lista ini, No * p);
void Transp(Lista ini, No* A, No* B);

/*Funções Principais*/
int Calcula_Custo_Total(char tipo, int N, int *requisicao, int R);
int MTF (Lista ini, int chave);
int  TR (Lista ini, int chave);
int  FC (Lista ini, int chave);

/*Função de ler entrada*/
void LeEntrada(int *N, int *R, int **requisicoes);
/*Função de incializar lista de acordo com o enunciado*/
void inicializaLista(Lista * lista, int R);

/*FUNÇÕES DE DEBUGAR*/
void pLst(Lista ini, char indicador);
void pVet(int v[], int n);


/* MEU PROGRAMA - MAIN */
/***********************/
int main() { 
	int N, R, *requisicao;
	int MTF_total = 0, TR_total = 0, FC_total = 0;

	
	/*Se a entrada for muito estranha*/
	LeEntrada(&N, &R, &requisicao);

	MTF_total = Calcula_Custo_Total('M', N, requisicao, R);
	TR_total  = Calcula_Custo_Total('T', N, requisicao, R);
	FC_total  = Calcula_Custo_Total('F', N, requisicao, R);
	
	/*Imprime os custos totais*/
	printf("%d %d %d\n", MTF_total, TR_total, FC_total);

	/*Desnecessário, mas para manter a prática*/
	free(requisicao);
	
	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/******************************************/

/* Calcula o custo de realizar todas as requisições, usando
 * a operação indicada na variavel tipo.
 * Legenda:
 *   M para MTF
 *   T para TC
 *   F para FC
 */
int Calcula_Custo_Total(char tipo, int N, int *req, int R){
	int i, custo, total = 0;
	Lista arqs;

	cria_lista(&arqs);
	inicializaLista(&arqs, N);

	for (i = 0; i < R; i++){
		/*Os algoritmos ja dovolveriam isso, mas assim é mais eficiente*/
		if (req[i] < 1 || req[i] > N) 
			custo = N;
		/* Realizar estas comparações a seguir a cada iteração do loop 
		 * é menos eficiente, porém repete menos código*/
		else if 
			(tipo == 'M') custo = MTF(arqs, req[i]);
		else if 
			(tipo == 'T') custo = TR (arqs, req[i]);
		else if 
			(tipo == 'F') custo = FC (arqs, req[i]);
		/*Só pra fazer uma função mais geral...*/
		else
			return 0;
		
		total += custo;

	}

	RemoveLista(&arqs);
	return total;

}
/*Cria o nó cabeça*/
void cria_lista(Head nova_lista){
	*nova_lista = (Lista)malloc(sizeof(No));
	(*nova_lista)->info = -1;
	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
/*Le a entrada de acordo com o enunciado*/
void LeEntrada(int *N, int *R, int **requisicoes){
	int i;

	scanf("%d %d", N, R);
	if(*R > 0) *requisicoes = malloc((*R) * sizeof(int));
	for(i = 0; i < (*R); i++){
		scanf("%d", &((*requisicoes)[i]));
	}
}
/*Inicializa lista de acordo com o enunciado e com 0 nos contadores freq*/
void inicializaLista(Head h, int N){
	int i;
	for(i = 1; i <= N; i++){
		cria_no(*h, i, 0);
	}
}
/*Cria um nó e o insere no final da lista, antes do no cabeça*/
void cria_no(Lista ini, int info, int freq){
	No* novo;
	novo = malloc(sizeof(No));
	novo->info = info;
	novo->freq = freq;

	novo->dir = ini;
	novo->esq = (ini)->esq;
	(ini)->esq = novo;
	novo->esq->dir = novo;
}
/*Desaloca uma lista inteira*/
void RemoveLista(Head h){
	/*(*h)->dir é a primeira posição já que (*h) aponta para o no cabeça*/
	Lista temp, p = (*h)->dir;
	while(p != *h){
		temp = p;
		p = p->dir;
		free(temp);
	}
	free(p);
	*h = NULL;
}
/*Realoca o nó p para a primeira posição com frequencia menor que a própria*/
void Realoca_no(Lista ini, No * p){
	Lista i;

	for(i = (ini)->dir; (i != ini) && (i->freq > p->freq); i = i->dir);
		
	Transp(ini, i, p);
}
/*Retira da lista o nó na posição B e insere antes de A*/
void Transp(Lista ini, No* A, No* B){
	if(A == ini || B == ini || A == B)
		return;

	B->dir->esq = B->esq;
	B->esq->dir = B->dir;

	B->dir = A;
	B->esq = A->esq;

	A->esq->dir = B;
	A->esq = B;
	
}
/*Custo de usar o algoritmo MTF para a requisição chave*/
int MTF(Lista ini, int chave){
	/*ini->dir é a primeira posição, porque ini é o nó cabeça*/
	Lista p = ini->dir;
	int MTF = 0;
	
	/*Se a lista for vazia não há custo, pq nenhm elemento foi acessado*/
	while(p != ini){
		MTF++;
		if(p->info == chave){
			Transp(ini, ini->dir, p);
			return MTF;
		}
		p = p->dir;
	}
	return MTF;
}
/*Custo de usar o algoritmo TR para a requisição na variável chave*/
int TR(Lista ini, int chave){
	Lista p = ini->dir;
	int TR = 0;

	/*Se a chave está na primeira pos, o custo é 1 e nda precisa ser feito*/
	if(p->info == chave)
		return 1;
	
	/*Percorre-se a lista até achar o elemento p, que contém a chave*/
	while(p != ini){
		TR++;
		if(p->info == chave){
			Transp(ini, p->esq, p);
			return TR + 1;
		}
		p = p->dir;
	}
	return TR;
}
/*Custo de usar o algoritmo FC para a requisição chave*/
int FC(Lista ini, int chave){
	No* p = (ini)->dir;
	int FC = 0;

	while(p != ini){
		FC++;
		if(p->info == chave){
			(p->freq)++;
			Realoca_no(ini, p);
			return FC;
		}
		p = p->dir;
	}
	return FC;
}
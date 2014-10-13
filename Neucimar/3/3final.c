/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 03 - Linha Divisora de Aguas */

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>


typedef struct fila { 
	int i, j;
	char rotulo;
	struct fila * prox;

} No, *Fila; 

typedef struct fila_ordenada { 
	int tamanho; /* Útil pra imprimir pra debugar */
	int num_filas; /* Contador útil pra saber se a fila ordenada esta vazia */
	Fila *fila;

} No_Fila_Ordenada, *FilaOrdenada;

#define MAX 100

typedef enum bool{false, true} bool;

/* TAD de Matrizes Dinâmicas */
/****************************/

/* TAD: Filas Ordenadas */
void criaFilaOrdenada(FilaOrdenada * F, int n);
void removeFilaOrdenada(FilaOrdenada F);
void criaFila(FilaOrdenada F, int pos);
void enfila(FilaOrdenada F, int i, int j, int pos, char rotulo);
void desenfila(int *i, int *j, char *rotulo, FilaOrdenada F, int pos);
void removeFila(FilaOrdenada F, int pos);
void pintFilaOrdenada(FilaOrdenada F); /* Função pra debugar */

/* TAD: Matrizes Dinâmicas */
int ** alocaMatriz(int H, int W);
void desalocaMatriz(int ** m, int H);
void obtem_matriz(int **matriz, int linhas, int colunas);
void imprime_matriz(int **matriz, int linhas, int colunas);

/* assinatura de outras funções */
/********************************/

bool dissipador(int ** m, int H, int W, int i, int j);

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int ** entrada, H, W, i, j, k;
	FilaOrdenada alturas;
	char rotulo;
	
	/* Ler entrada */
	scanf("%d %d", &H, &W);
	
	entrada = alocaMatriz(H, W);

	obtem_matriz(entrada, H, W);

	criaFilaOrdenada(&alturas, MAX);

	k = 0;
	for(i = 0; i < H; i++){
		for(j = 0; j < W; j++){
			if(dissipador(entrada, H, W, i, j)){
				/* Usa números negativos como caracteres */
				enfila(alturas, i, j, entrada[i][j], (char)('a' + k));
				k++;
			}
		}
	}
	k = 0;
	/* Enquanto as filas ainda não estão vazias */
	while(alturas->num_filas > 0 && k < MAX){
		/* Avança pra próxima quando encontrar uma fila vazia */
		if(alturas->fila[k] == NULL){
			k++;
		/* Quando achar uma fila não vazia... */
		}else{
			/* Retira-se o ponto da fila ordenada */
			desenfila(&i, &j, &rotulo, alturas, k);
			/* Pra só reotular da primeira vez */
			if(entrada[i][j] >= 0){
				/* A rotulação é feita somente nesse ponto */
				/* A ordem original do algoritmo teve de ser modificada
				 * pra ser possivel usar apenas uma matriz pras alturas e 
				 * rótulos, os primeiros positivos e os ultimos negativos */
				entrada[i][j] = -rotulo;
			}
			/* Cada ponto Y que não esta rotulado entra na fila 
			 * ordenada pra rotulagem */
			if((i-1 >= 0) && (entrada[i-1][j] >= 0)){
				enfila(alturas, i-1, j, entrada[i-1][j], rotulo);
			} 
			if((j-1 >= 0) && (entrada[i][j-1] >= 0)){
				enfila(alturas, i, j-1, entrada[i][j-1], rotulo);
			} 
			if((j+1 <  W) && (entrada[i][j+1] >= 0)){
				enfila(alturas, i, j+1, entrada[i][j+1], rotulo);
			} 
			if((i+1 <  H) && (entrada[i+1][j] >= 0)){
				enfila(alturas, i+1, j, entrada[i+1][j], rotulo);
			}
			/* O contador zera, porque o adjacente pode 
			 * ter altura menor que a atual, se não voltasse, 
			 * este novo menor nunca seria rotulado */
			k = 0;
		}
	}
	removeFilaOrdenada(alturas);
	
	imprime_matriz(entrada, H, W);

	desalocaMatriz(entrada, H);



	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD de Filas Ordenadas */
/*************************/

void criaFilaOrdenada(FilaOrdenada * F, int n){
	int i;

	*F  = (FilaOrdenada)malloc(sizeof(No_Fila_Ordenada));
	(*F)->fila = (Fila*)malloc(sizeof(Fila) * n);
	(*F)->num_filas = 0;
	(*F)->tamanho = n;
	
	for(i = 0; i < n; i++){
		(*F)->fila[i] = NULL;
	}
}
void removeFilaOrdenada(FilaOrdenada F){
	int i;
	for(i = 0; F->num_filas > 0; i++){
		if(F->fila[i] != NULL){
			removeFila(F, i);
		}
	}
	free(F->fila);
	free(F);
}

void criaFila(FilaOrdenada F, int pos){
	Fila * f = &(F->fila[pos]);
	*f = (Fila)malloc(sizeof(No));
	/* Cria nó cabeça */
	(*f)->i = -1;
	(*f)->j = -1;
	(*f)->rotulo = 'R';
	(*f)->prox = *f;
	
	(F->num_filas)++;
}

void enfila(FilaOrdenada F, int i, int j, int pos, char rotulo){
	Fila * f = &(F->fila[pos]), novo;
	if((*f) == NULL){
		criaFila(F, pos);
	}
	novo = (Fila)malloc(sizeof(No));

	novo->i = i;
	novo->j = j;
	novo->rotulo = rotulo;

	novo->prox = (*f)->prox;
	(*f)->prox = novo;
	*f = novo;
}

/* Desenfila um ou remove a fila se só tiver um elemento */
void desenfila(int *i, int *j, char *rotulo, FilaOrdenada F, int pos){
	Fila f = F->fila[pos], aux;
	if(f == NULL){
		exit(1);
	}
	/* Posiciona os ponteiros */
	f = f->prox;
	aux = f->prox;
	/* Salva os valores principais */
	*i = aux->i;
	*j = aux->j;
	*rotulo = aux->rotulo;

	/* Se a fila só tiver um elemento, além do nó cabeça... */
	if(f == aux || f == aux->prox){
		/* ...desaloca-se esta fila */
		removeFila(F, pos);
	}else{
		/* ...remove-se o primeiro no depois do no cabeça */
		f->prox = aux->prox;
		free(aux);
	}
}

/* Remove a fila na posição pos da Fila Ordenada F */
void removeFila(FilaOrdenada F, int pos){
	Fila f = F->fila[pos]; 
	Fila aux, ff = f->prox;
	while(ff != f){
		aux = ff;
		ff = ff->prox;
		free(aux);
	}
	free (f);
	/*Serve de marcação pra função principal*/
	F->fila[pos] = NULL;
	(F->num_filas)--;
}

/* Função pra debugar */
void pintFilaOrdenada(FilaOrdenada F){
	int i;
	Fila f;
	for(i = 0; i < F->tamanho; i++){
		printf("Fila %d:\n", i);
		f = F->fila[i]->prox;
		for(f = f->prox; f != F->fila[i]->prox; f=f->prox){
			printf("    (i,j) = (%d,%d)\n", f->i, f->j);
		}
	}
}

/* TAD de Matrizes Dinâmicas */
/****************************/

int ** alocaMatriz(int H, int W){
	int **m, i;
	m = (int**) malloc(H *sizeof(int*));
	for(i = 0; i < H; i++){
		m[i] = (int*)malloc(W * sizeof(int));
	}

	return m;
}
void desalocaMatriz(int ** m, int H){
	int i;
	for(i = 0; i < H; i++){
		free(m[i]);
	}
	free(m);
}
void obtem_matriz(int **m, int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			scanf("%d", &m[i][j]);
}
void imprime_matriz(int **m, int linhas, int colunas){
	int i, j;
	
	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++){
			/* Imprime negativos como caracteres */
			if(m[i][j] < 0) 
				printf("%c ",(char)(-m[i][j]));
			/* Muito útil pra debugar */
			else 
				printf("%3d ", m[i][j]);
		}
		printf("\n");
	}
}

/* implementação de outras funções */
/**********************************/
/*********************************/

bool dissipador(int ** m, int H, int W, int i, int j){
	/* Só é verdadeiro se for o menor entre os adjacentes */
	if( (i-1 >= 0) && (m[i-1][j] < m[i][j]) ) 
		return false;
	if( (j-1 >= 0) && (m[i][j-1] < m[i][j]) ) 
		return false;
	if( (j+1 <  W) && (m[i][j+1] < m[i][j]) ) 
		return false;
	if( (i+1 <  H) && (m[i+1][j] < m[i][j]) ) 
		return false;
	return true;
}
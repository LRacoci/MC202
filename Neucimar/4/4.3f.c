/* Nome: Seu nome aqui 
* RA: Seu RA aqui 
* Laboratorio 04 - Quicksort aleatorizado */

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

/* Função genérica que troca dois inteiros */
void troca(int* a, int* b);
/* Função auxiliar que só funciona nesse programa */
void copia(int aux[], int v[], int inicio, int fim);
/* Função auxiliar do quicksort que retorna a posição real do pivo escolhido */
int partition(int v[], int n, int pivo, double *custo);
/* Função principal, que retorna o custo medio de todas as 
 *possiveis formas de se escolher pivos para o quick sort */
double quicksort(int v[], int inicio, int fim);

/* assinatura de outras funções */
/********************************/

/* Função útil para debugar */
void pvet(int v[], int ini, int fim);
/* Le a entrada separadamente */
int *leEntrada(int*);

/* MEU PROGRAMA - MAIN */
/***********************/

int main() { 
	double custo;
	int n;
	int *in = leEntrada(&n);

	custo = quicksort(in, 0, n - 1);

	printf("%.10f\n", custo);

	/* Libera a memoria alocada em leEntrada */
	free(in);

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/****************************************/

void troca(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void copia(int aux[], int v[], int inicio, int fim){
	int i, n = fim - inicio + 1;
	for(i = 0; i < n; i++){
		aux[i] = v[inicio + i];
	}
}
int partition(int v[], int n, int indice_pivo, double *custo) {
	int i, j, menores = 0, maiores = n - 1;
	
	int *aux = (int*)malloc(n * sizeof(int));

	for(i = 0; i < n; i++){
		/* Se o atual é menor que o pivo... */
		if(v[i] < v[indice_pivo]){
			/* ...é copiado para o vetor aux na ordem em que aparece */
			aux[menores] = v[i]; 
			menores++;
			/* Se além de ser menor estiver a direita, incrementa-se o custo */
			if(i > indice_pivo){
				(*custo)++;
			}
		/* Se o atual é maior que o pivo... */
		}else if(v[i] > v[indice_pivo]){
			/* ...é copiado para o vetor aux na ordem inversa a que aparece */
			aux[maiores] = v[i];
			maiores--;
			/* Se além de ser maior estiver a esquerda incrementa-se o custo */
			if(i < indice_pivo){
				(*custo)++;
			}
		}
		/* Se o atual é igual ao pivo, mas não é o pivo */
		else if(i != indice_pivo){
			printf("\033[91mERRO\n\033[97m\n");
			exit(1);
		}
	}
	/* Passa o pivo para a posição certa */
	v[menores] = v[indice_pivo];
	/* Retorna a primeira particao de aux para o vetor de entrada na ordem */
	for(i = 0; i < menores; i++){
		v[i] = aux[i];
	}
	/* Retorna a segunda particao, desinvertendo-a, ao vetor de entrada */
	for(i = menores + 1, j = n - 1; i < n; i++, j--) {
		v[i] = aux[j];
	}

	free(aux);
	/* Retorna a nova posição do pivo */
	return menores;
}
double quicksort(int v[], int inicio, int fim){
	int i, pivo = 0, *aux;
	int n = fim - inicio + 1;
	double custo = 0;
	/* Se existirem pelo menos dois elementos para serem ordenados... */
	if (inicio < fim) {
		/* Percorre todas as possibilidades de pivos com i */
		for(i = 0; i < n; i++){
			
			/* Aloca vetor aux para não modificar o original */
			aux = (int*)malloc(n * sizeof(int));
			/* Copia os valores em v de inicio a fim para aux de 0 a n-1 */
			copia(aux, v, inicio, fim);

			/* particiona o vetor */
			pivo = partition(aux, n, i, &custo); 
			
			/* ordena a primeira particao */
			custo += quicksort(aux, 0, pivo - 1); 
			/* ordena a segunda particao */
			custo += quicksort(aux, pivo + 1, n - 1);
			
			free(aux);
		}
	}
	/* Para não dividir zero por zero */
	if (n == 0) return 0;
	/* Retorna média de custo */
	return custo/n;
}

/* implementação de outras funções */
/***********************************/

void pvet(int v[], int ini, int fim){
	int i;

	printf("{%d", v[ini]);
	for(i = ini + 1; i <= fim; i++)
		printf(", %d", v[i]);
	printf("}\n");
}
int *leEntrada(int* n){
	int i, *v;
	scanf("%d", n);

	v = (int*)malloc((*n) * sizeof(int));

	for(i = 0; i < (*n); i++){
		scanf("%d", &v[i]);
	}
	
	return v;
}
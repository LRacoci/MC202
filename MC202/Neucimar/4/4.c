/* Nome: Seu nome aqui 
* RA: Seu RA aqui 
* Laboratorio 04 - Quicksort aleatorizado */

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

void troca(int* a, int* b);
void copia(int aux[], int v[], int n);
int partition(int v[], int inicio, int fim, int pivo, double *custo);
double quicksort(int v[], int inicio, int fim, int pivo);

/* assinatura de outras funções */
/********************************/

void pvet(int v[], int n);
int *leEntrada(int*);


/* MEU PROGRAMA - MAIN */
/***********************/

int main() { 
	double custo = 0;
	int n, i, *aux;
	int *in = leEntrada(&n);

	for (i = 0; i < n; i++){
		aux = (int*)malloc(n * sizeof(int));
		copia(aux, in, n);
		custo += quicksort(aux, 0, n - 1, i);
		free(aux);
	}

	printf("%.10f\n", custo);

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
void copia(int *aux, int *v, int n){
	int i;
	for (i = 0; i <  n; i++){
		aux[i] = v[i];
	}
}
int partition(int v[], int inicio, int fim, int pivo, double *custo) {
	int i, menores = inicio, maiores = fim;
	int n = fim - inicio + 1;
	
	int *v2 = (int*)malloc(n * sizeof(int));
	
	
	for (i = inicio; i <= fim; i++){
		if(v[i] < v[pivo]){
			v2[menores - inicio] = v[i]; 
			menores++;
			if(i < pivo){
				(*custo)++;
			}
		}else if(v[i] > v[pivo]){
			v2[maiores - inicio] = v[i];
			maiores--;
			if(i < pivo){
				(*custo)++;
			}
		}
	}
	v2[menores - inicio] = v[pivo];
	for (i = inicio; i <= fim; i++){
		v[i] = v2[i - inicio];
	}

	free(v2);
	
	return menores;
}
double quicksort(int v[], int inicio, int fim, int pivo) {
	int i, *aux;
	int n = fim - inicio + 1;
	double custo = 0;
	/* se existirem pelo menos dois elementos para serem ordenados... */
	if (inicio < fim) {
		for(i = inicio; i <= fim; i++){
			aux = (int*)malloc(n * sizeof(int));
			copia(aux, v, n);
			
			
			printf("pivo = %d\n", pivo);
			pvet(aux, n);

			/* particiona o vetor */
			pivo = partition(aux, inicio, fim, i, &custo); 
			pvet(aux, n);
			printf("\n");
			

			/* ordena a primeira particao */
			custo += quicksort(aux, inicio, pivo - 1, i); 
			/* ordena a segunda particao */
			custo += quicksort(aux, pivo + 1, fim, i);
			free(aux);
		}
	}
	if (n == 0) return 0;
	return custo/n;
}

/* implementação de outras funções */
/***********************************/

void pvet(int v[], int n){
	int i;

	printf("{%d", v[0]);
	for(i = 1; i < n; i++)
		printf(", %d", v[i]);
	printf("}\n");
}
int *leEntrada(int* n){
	int i, *v;
	scanf("%d", n);

	v = (int*)malloc((*n) * sizeof(int));

	for (i = 0; i < (*n); i++){
		scanf("%d", &v[i]);
	}
	
	return v;
}
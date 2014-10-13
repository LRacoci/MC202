/* Nome: Seu nome aqui 
* RA: Seu RA aqui 
* Laboratorio 04 - Quicksort aleatorizado */

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

void troca(int* a, int* b);
void copia(int aux[], int v[], int inicio, int fim);
int partition(int v[], int inicio, int fim, int pivo, double *custo);
double quicksort(int v[], int inicio, int fim);

/* assinatura de outras funções */
/********************************/

void pvet(int v[], int ini, int fim);
int *leEntrada(int*);

int recur = 0;
void tab(){
	int i;
	for (i = 0; i < recur; i++)
		printf("    ");
}


/* MEU PROGRAMA - MAIN */
/***********************/

int main() { 
	double custo;
	int n;
	int *in = leEntrada(&n);

	custo = quicksort(in, 0, n - 1);

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
void copia(int aux[], int v[], int inicio, int fim){
	int i;
	for (i = inicio; i <= fim; i++){
		aux[i] = v[i];
	}
}
int partition(int v[], int inicio, int fim, int pivo, double *custo) {
	int i, j, menores = inicio, maiores = fim;
	int n = fim - inicio + 1;
	
	int *v2 = (int*)malloc(n * sizeof(int));
	
	
	for (i = inicio; i <= fim; i++){
		if(v[i] < v[pivo]){
			v2[menores - inicio] = v[i]; 
			menores++;
			if(i > pivo){
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
	v[menores] = v[pivo];
	/* Retorna a primeira particao ao vetor de entrada */
	for (i = inicio; i < menores; i++){
		v[i] = v2[i - inicio];
	}
	/* inverte a segunda particao e retorna ao vetor de entrada */
	for (i = menores + 1, j = n - 1; 
		 (i <= fim) && (j >= menores); 
		                   i++, j--) {
		v[i] = v2[j];
	}

	free(v2);
	
	return menores;
}
double quicksort(int v[], int inicio, int fim){
	int i, pivo = 0, *aux;
	int n = fim - inicio + 1;
	double custo = 0;
	recur++;
	/* se existirem pelo menos dois elementos para serem ordenados... */
	if (inicio < fim) {
		for(i = inicio; i <= fim; i++){
			aux = (int*)malloc((fim + 1) * sizeof(int));
			copia(aux, v, inicio, fim);

			tab(); printf("De %d a %d\n", inicio, fim);
			tab(); pvet(aux, inicio, fim);
			
			/* particiona o vetor */
			pivo = partition(aux, inicio, fim, i, &custo); 
			
			tab(); printf("pivo[%d] = %d\n", pivo, aux[pivo]);
			tab(); pvet(aux, inicio, fim);
			tab(); printf("custo = %f\n\n", custo);
			
			/* ordena a primeira particao */
			custo += quicksort(aux, inicio, pivo - 1); 
			/* ordena a segunda particao */
			custo += quicksort(aux, pivo + 1, fim);
			free(aux);
		}
	}
	recur--;
	if (n == 0) return 0;
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

	for (i = 0; i < (*n); i++){
		scanf("%d", &v[i]);
	}
	
	return v;
}
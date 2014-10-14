/* Nome: Seu nome aqui 
* RA: Seu RA aqui 
* Laboratorio 04 - Quicksort aleatorizado */

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

void troca(int* a, int* b);
void copia(int aux[], int v[], int inicio, int fim);
int partition(int v[], int n, int pivo, double *custo);
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
	int i, n = fim - inicio + 1;
	for (i = 0; i < n; i++){
		aux[i] = v[inicio + i];
	}
}
int partition(int v[], int n, int i_pivo_0, double *custo) {
	int i, j, menores = 0, maiores = n - 1;
	
	int *aux = (int*)malloc(n * sizeof(int));
	
	if(i_pivo_0 > n){
		printf("\033[91mPIVO OUT OF RANGE\033[92m\n");
		printf("pivo[%d] = %d e n = %d\033[97m\n", i_pivo_0, v[i_pivo_0], n);
		exit(1);
	}
	
	for (i = 0; i < n; i++){
		/* Se o atual é menor que o pivo... */
		if(v[i] < v[i_pivo_0]){
			/* ...é copiado para o vetor aux na ordem em que aparece */
			aux[menores] = v[i]; 
			menores++;
			/* Se for menor e estava a direita, incrementa-se o custo */
			if(i > i_pivo_0){
				(*custo)++;
			}
		/* Se o atual é maior que o pivo... */
		}else if(v[i] > v[i_pivo_0]){
			/* ...é copiado para o vetor aux na ordem inversa a que aparece */
			aux[maiores] = v[i];
			maiores--;
			/* Se além for maior e estva a esquerda incrementa-se o custo */
			if(i < i_pivo_0){
				(*custo)++;
			}
		}
		/* Se o atual for o pivo não se faz nada */
	}
	if(menores != maiores){
		printf("\033[91mERRO: maiores + menores != n\n");
		printf("\033[92menores = %d\033[97m, \033[94mmaiores = %d\n\033[97m", menores, maiores);
		exit(1);
	}
	v[menores] = v[i_pivo_0];
	/* Retorna a primeira particao ao vetor de entrada */
	for (i = 0; i < menores; i++){
		v[i] = aux[i];
	}
	/* Retorna a segunda particao desinvertida ao vetor de entrada */
	for (i = menores + 1, j = n - 1; i < n; i++, j--) {
		v[i] = aux[j];
	}

	free(aux);
	
	return menores;
}
double quicksort(int v[], int inicio, int fim){
	int i, pivo = 0, *aux;
	int n = fim - inicio + 1;
	double custo = 0;
	recur++;
	/* se existirem pelo menos dois elementos para serem ordenados... */
	if (inicio < fim) {
		for(i = 0; i < n; i++){
			
			aux = (int*)malloc(n * sizeof(int));
			copia(aux, v, inicio, fim);

			/*tab(); printf("De %d a %d\n", inicio, fim);
			tab(); pvet(aux, 0, n);*/
			
			/* particiona o vetor */
			pivo = partition(aux, n, i, &custo); 
			
			/*tab(); printf("pivo[%d] = %d\n", pivo, aux[pivo]);
			tab(); pvet(aux, 0, n);
			tab(); printf("custo = %f\n\n", custo);*/
			
			/* ordena a primeira particao */
			custo += quicksort(aux, 0, pivo - 1); 
			/* ordena a segunda particao */
			custo += quicksort(aux, pivo + 1, n - 1);
			
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
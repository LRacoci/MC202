#include <stdio.h>
#include <stdlib.h>

#define MAX 1026

int iguais(char *T, int k, int a, int b){
	int i, iguais = 1;
	for(i = 0; i < k; i++){
		if(T[a + i] != T[b + i]){
			iguais = 0;
		}
	}
	
	return iguais;
}
int nova(int a, int k, char *T, int *f, int m, int maxf){
	int i, nova = 1;
	for(i = 0; i < a; i++){
		if(f[i] == maxf && iguais(T, k, a, i)){
			nova = 0;
		}
	}
	return nova;
}
void imprime_vetor(int *v, int n){
	int i;
	printf("{%d", v[0]);
	for(i = 1; i < n; i++){
		printf(" %d", v[i]);
	}
	printf("}\n");
}
int main() {
	
	char T[MAX];
	int n, k, i, j, a, b, sf, maxf = 0, *f;

	scanf("%s", T);
	scanf("%d", &k);

	for(n = 0; T[n]; n++);

	f = malloc((n-k+1) * sizeof(int));
	for(i = 0; i < n-k+1; i++){
		f[i]=0;
	}

	for(b = 0; b + k <= n; b++){
		if(nova(b, k, T, f, n-k+1, maxf)){
			for(a = 0; a + k <= n; a++){
				for(sf = 0, i = 0; i < k; i++){
					if(T[a + i] == T[b + i]){
						sf++;
					}
				}
				if(sf == k){
					f[b]++;
				}
			}
			if(f[b] >= maxf){
				maxf = f[b];
			}
		}
	}
	for(i = 0; i < n-k+1; i++){
		if(f[i] == maxf){
			for(j = 0; j < k; j++){
				printf("%c", T[i + j]);

			}
			printf(" ");
		}
	}
	printf("\n");

	free(f);

	return 0;
}
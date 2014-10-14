#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int n, int * vet){
	int i, min = v[0];
	
	for(i = 1; i < n; i++)
		if(v[i] < min)
			min = v[i];
	
	return min;
}

int ** aloca_Matriz(int L, int C){
	int i, **m;
	m = malloc(L * sizeof(int*));
	for(i = 0; i < L; i++){
		m[i] = malloc(C * sizeof(int));
	}
	return m;
}
void imprime_matriz(int **m, int L, int C){
	int i, j;
	for(i = 0; i <= L; i++){
		for(j = 0; j <= C; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}
int main (){
	int n;
	int tam_s, tam_t, **m, L, C,i, j;
	char *s, *t;
	
	printf("\033[91mDigite o tamanho aproximado das strings: \033[0m");
	scanf("%d", &n);

	s = malloc((n + 10) * sizeof(char));
	printf("\033[92mDigite a primeira string: \033[0m");
	scanf("%s.", s);

	t = malloc((n + 10) * sizeof(char));
	printf("\033[94mDigite a segunda string: \033[0m");
	scanf("%s.", t);

	tam_s = strlen(s);
	tam_t = strlen(t);

	C = tam_s; /*percorrido por j*/
	L = tam_t;

	m = aloca_Matriz(L + 1, C + 1);

	for(i = 0; i < L; i++){
		m[i][C] = 0;
		m[L][i] = 0;
	}
	m[L][C] = 0;
	
	for(i = L-1; i > 0; i--){
		for(j = C-1; j > 0; j--){
			if (s[j] == t[i]){
				m[i][j] = min(3, {m[i+1][j+1], m[i+1][j], m[i][j+1]});
			}else{
				m[i][j] = 1 + min(3, {m[i+1][j+1], m[i+1][j], m[i][j+1]});
			}
		}
	}
	
	printf("\n");

	imprime_matriz(m, L, C);
	


	free(s);
	free(t);

	return 0;
}

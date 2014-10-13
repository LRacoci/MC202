#include <stdio.h>
#include <stdlib.h>

#define N 10000

int main() {
	long int candidato, i, pi, v[N], primo;
	v[0] = 2;
	for(pi = 1, candidato = 3; pi < N; candidato++){
		primo = 1;
		for (i = 0; i < pi && primo; i++){
			if(candidato % v[i] == 0){
				primo = 0;
			}
	    }
	    if (primo==1){
	    	v[pi] = candidato;
			pi++;
			printf("%ld\n", candidato);
		}
	}
	

	return 0;
}
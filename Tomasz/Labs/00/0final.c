/***********************************************************
 * Autor: Lucas Alves Racoci
 * RA: 156331
 * Laboratorio 00a: Contar caracteres e linhas
 ***********************************************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	long int c;
	int linhas = 0, caracteres = 0;
	while(scanf("%ld", &c) != EOF){
		
		if((char)c == '\n'){
			linhas++;
		}else{
			caracteres++;
		}
	}
	printf("Caracteres: %d\n", caracteres);
	printf("Linhas:     %d\n", linhas);
   	
    return 0;
}


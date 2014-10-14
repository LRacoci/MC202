/***********************************************************
 * Autor: Lucas Alves Racoci
 * RA: 156331
 * Laboratorio 00a: Contar caracteres e linhas
 ***********************************************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char c;
	int linhas = 0, caracteres = 0, carac = 0;
	while(scanf("%c", &c) != EOF){
		
		if(c == '\n'){
			linhas++;
			carac++;
			printf("\033[93mAvaliando: \033[91m'%c'\033[97m\n", c);
			printf("\033[97mCaracteres: \033[94m%d\n", carac);
			printf("\033[97mLinhas:     \033[92m%d\n", linhas);
			printf("\n");
			carac = 0;
		}else{
			caracteres++;
			carac++;
		}
	}
	printf("\033[93mCaracteres: \033[94m%d\033[97m\n", caracteres);
	printf("\033[93mLinhas:     \033[92m%d\033[97m\n", linhas);
   	
   	printf("\033[97m"); 
    return 0;
}


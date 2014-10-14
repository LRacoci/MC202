/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 05 - Gerente do Espaço */

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>


/* Fila mono-ligada circular com no cabeça */
typedef struct fila { 
	int i, j;
	char rotulo;
	struct fila * prox;

} No, *Fila; 

typedef enum bool{false, true} bool;

/* TAD: */

/* TAD: */

/* assinatura de outras funções */
/********************************/
bool LeEntrada(int N){
	int i, D, tam;
	char unidade, lixo;
	if(N == 0) return false;

	for(i = 0, i < N; i++){
		scanf("%d%c%c", &D, &unidade, &lixo);
		tam = Converte(unidade);


	}
	return true;
}

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int N;
	do{
		scanf("%d", &N);
	}while(LeEntrada(N));

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD de  */
/*************************/

/* TAD de  */
/****************************/

/* implementação de outras funções */
/**********************************/
/*********************************/
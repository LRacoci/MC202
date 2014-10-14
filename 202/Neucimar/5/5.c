/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 05 - Gerente do Espaço */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_TIPO 8
#define MAX_NOME 10

/* Lista Duplamente Ligada, com Nó Cabeça e Circular*/
typedef enum bool{false, true} bool;

typedef struct lista { 
	int tamanho;
	bool ocupado;
	struct lista *e, *d;
} No, *Lista, **Head;



/* TAD: Lista Duplamente Ligada, c*/

/* TAD: */

/* assinatura de outras funções */
/********************************/
int Converte_pra_K(char X){
	switch ((int) X)) {
	case ((int)'K'):
		return 1;
	case ((int)'M'):
		return 1024;
	case ((int)'G'):
		return 1024 * 1024;
	}
}

void imprime_disco(Disco){

}

bool Continua(int N){
	int i, D, tam;
	char unidade, lixo;
	char tipo[MAX_TIPO], nome[MAX_NOME];
	if(N == 0) return false;
	
	scanf("%d%c%c", &D, &unidade, &lixo);
	D = D * Converte_pra_K(unidade);
	
	for(i = 0, i < N; i++){
		scanf("%s %s", tipo, nome);
		if(strcmp(tipo, "insere") == 0){
		}else if(strcmp(tipo, "remove") == 0){

		}else if(strcmp(tipo, "otimiza") == 0){

		}
	}
	return true;
	if(cheio) printf("ERRO: disco cheio\n");
	else imprime_disco(Disco);
}

/* MEU PROGRAMA - MAIN */
/**********************/
/*********************/

int main() { 
	int N;
	do{
		scanf("%d", &N);
	}while(Continua(N));

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
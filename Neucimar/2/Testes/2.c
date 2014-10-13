/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/************************************************************/

/* Guarda seu volume e o volume que contem, respectivamente */
typedef struct Mtk{
	int dado;
	int soma;
} Mtk, *pMtk;

/* Pilha, que contêm um vetor para matrioshcas (Mtk's) */
typedef struct Pilha{ 
	int topo;
	Mtk** pilha;
} Pilha;

void criaPilha(Pilha ** nova, int n);
void empilha(Pilha * p, int data);
void desempilha(Pilha * p);
void destroiPilha(Pilha * p);

/* Utilizada para debugar */
void printPilha(Pilha * p);

/* assinatura de outras funções */ 
/********************************/
int continuaValido(Pilha * p, int aux);

/* MEU PROGRAMA - MAIN */
/***********************/
int main() { 
	int n;
	int aux;
	int i;
	int matrioshka;
	Pilha * p;
	
	/* Loop total */
	do{
		/*Adquire o numero de entradas*/
		scanf("%d", &n);
		
		/* Aloca a pilha */
		criaPilha(&p, n);
		
		/*O brinquedo é válido ateh que se prove o contrario*/
		matrioshka = 1;
		
		for(i = 0; i < n; i++){
			/* Pega o próximo indicador */
			scanf("%d", &aux);
			/*Testa se continua válido, e atualisa a flag*/
			if (matrioshka) 
				matrioshka = continuaValido(p, aux);
		}
		/* Libera memória */
		destroiPilha(p);
		
		/* Impressão ao final de cada teste */
		if(n){
			if(matrioshka){
				printf(":-) Matrioshka!\n");
			}else{
				printf(":-( Tente novamente.\n");
			}
		}
	}while(n);

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/******************************************/

void criaPilha(Pilha ** nova, int n){
	(*nova) = (Pilha*)malloc(sizeof(Pilha));
	(*nova)->pilha = (pMtk*)malloc(n * sizeof(Mtk*));
	(*nova)->topo = -1;
}
void empilha(Pilha * p, int data){
	(p->pilha[++(p->topo)]) = (pMtk)malloc(sizeof(Mtk));
	(p->pilha[p->topo])->soma = 0;
	(p->pilha[p->topo])->dado = data;
}
void desempilha(Pilha * p){
	if(p != NULL && p->topo >= 0)
		free(p->pilha[(p->topo)--]);
}
void destroiPilha(Pilha * p){
	while(p != NULL && p->topo >= 0){
		free(p->pilha[(p->topo)--]);
	}
	free(p->pilha);
	free(p);
	p = NULL;
}
void printPilha(Pilha * p){
	int i;
	for(i = 0; i < p->topo; i++){
		printf("dado = %d soma = %d\n", (p->pilha[i])->dado, (p->pilha[i])->soma);
	}
	printf("\n");
}

/* implementação de outras funções */
/***********************************/
int continuaValido(Pilha * p, int aux){
	/* Para aux positivo, ao fechar um brinquedo... */
	if(aux > 0){
		/* Se já tiver algum brinquedo na pilha */
		if(p->topo >= 0){
			/* Se o brinquedo aberto é igual ao que está para fechar */
			if(aux == (p->pilha[p->topo])->dado){
				desempilha(p);
			/* Abriu diferente do que fechou... */
			}else{
				/* ...Sequencia inválida */
				return 0;
			}
		}else{
			/* Se não tiver nenhum brinquedo aberto, fechá-lo eh absurdo */
			return 0;
		}
	/* Para aux negativo, ou seja ao abrir um novo brinquedo... */
	}else{
		/* ...Se não eh o primeiro... */
		if(p->topo >= 0){
			/* ...Decrementa-se a soma porque o valor de aux, 
			 * aqui, eh negativo */
			(p->pilha[p->topo])->soma -= aux;
			/* Confere se ainda cabe algum brinquedo dentro do anterior */
			if ( (p->pilha[p->topo])->soma < 
				 (p->pilha[p->topo])->dado ){
				/* Se couber, eh empilhado, com valor positivo */
				empilha(p, (-1)*aux);
			}else{
				/* Se não couber não eh mais valido */
				return 0;
			}
		/* ...Se for o primeiro, é empilhado com valor positvo*/
		}else{
			empilha(p, (-1)*aux);
		}
	}
	return 1;
}
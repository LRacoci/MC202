/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/************************************************************/
typedef struct Mtk{
	int dado;
	int soma;
} Mtk, *pMtk, **VpMtk;

typedef struct Pilha{ 
	int topo;
	Mtk** pilha;

} Pilha;


void criaPilha(Pilha ** nova, int n){
	(*nova) = (Pilha*)malloc(sizeof(Pilha));
	(*nova)->pilha = (Mtk**)malloc(n * sizeof(Mtk*));
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

void pPilha(Pilha * p){
	int i;
	for(i = 0; i < p->topo; i++){
		printf("dado = %d soma = %d\n", (p->pilha[i])->dado, (p->pilha[i])->soma);
	}
	printf("\n");
}

/* assinatura de outras funções */ 
/********************************/

/* MEU PROGRAMA - MAIN */
int main() { 
	int n;
	int aux;
	int i;
	int matrioshka = 1;
	Pilha * p;
	
	/* Loop total */
	do{
		scanf("%d", &n);
		criaPilha(&p, n);
		for(i = 0; i < n; i++){
			scanf("%d", &aux);
			if(aux > 0){
				if(p->topo >= 0){
					if(aux == (p->pilha[p->topo])->dado){
						desempilha(p);
					}else{
						matrioshka = 0;
						break;
					}
				}else{
					matrioshka = 0;
					break;
				}
			}else{
				if(p->topo >= 0){
					(p->pilha[p->topo])->soma -= aux;
					if ( (p->pilha[p->topo])->soma < 
						 (p->pilha[p->topo])->dado ){

						empilha(p, (-1)*aux);

					}else{
						matrioshka = 0;
						break;
					}
				}else{
					empilha(p, (-1)*aux);
				}
			}
		}
		/* Final */
		if(matrioshka){
			printf(":-) Matrioshka!\n");
		}else{
			printf(":-( Tente novamente.\n");
		}
	}while(n);

	return 0; 
} 

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/******************************************/


/* implementação de outras funções */
/***********************************/

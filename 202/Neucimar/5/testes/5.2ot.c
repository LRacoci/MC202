/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratorio 05 - Gerente do Espaço */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/

#define MAX_TIPO 8
#define MAX_NOME 11
#define MAX_DISCO 8


typedef enum bool{false, true} bool;

/* Lista Duplamente Ligada, com Nó Cabeça e Circular*/
typedef struct lista { 
	char *nome;
	int tam;
	bool ocupado;
	struct lista *esq, *dir;
} No, Arq, *Lista, *Disco, **Head;

/* TAD: Listas Duplamente Ligadas, Circulares com Nós Cabeças*/
/************************************************************/

void cria_lista(Head nova_lista, int D);
void cria_ultimo(Lista ini, char nome[], int tam);
void cria_antes(Lista ini, No* P, char nome[], int tam, bool flag);

void atribui_tam(Lista ini, No* p, int tam);
void libera_arq(Lista ini, No * p);
void removeNo(Lista ini, No * A);
void removeLista(Head h);
bool vazia(Lista ini);


/* Útil pra debugar */
void pLst(Lista ini);

/* TAD: Disco, implementado com Listas Ligadas */
/**********************************************/
void copia_disco(Lista A, Lista B);
void imprime_celula(double P);
void imprime_disco(Disco ini, int D);
void picotaDisco(Lista A, double parte);
void picotaArquivo(Lista A, No* p, double slice);

/* Verifica, após inserir um arquivo, se o disco está cheio */
bool insere_arquivo(Disco disco, int D, int tam, char* nome);
/* Verifica, após otimizar o disco, se o disco está cheio */
bool otimiza_disco(Disco disco, int D);
/* Verifica, após Remover um arquivo, se o disco está cheio */
void remove_arquivo(Disco disco, char* nome);
void mescla(Disco disco, No * p);

/* assinatura de outras funções */
/********************************/
int Converte_pra_K(char X);
bool Continua(int N);

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
/* implementação de outras funções */
/**********************************/
/*********************************/

bool Continua(int N){
	int i, D, tam;
	char unidade, lixo;
	char tipo[MAX_TIPO], nome[MAX_NOME];
	bool cheio = false;

	Lista disco;

	if(N == 0) return false;
	
	scanf("%d%c%c", &D, &unidade, &lixo);
	D = D * Converte_pra_K(unidade);
	
	cria_lista(&disco, D);
	cria_ultimo(disco, "", D);
	
	for(i = 0; i < N; i++){
		scanf("%s", tipo);
		if(strcmp(tipo, "insere") == 0){
			scanf("%s %d%c%c", nome, &tam, &unidade, &lixo);
			if(!cheio){
				tam = tam * Converte_pra_K(unidade);
				cheio = insere_arquivo(disco, D, tam, nome);
			}
		}else if(strcmp(tipo, "remove") == 0){
			scanf("%s", nome);
			if(!cheio)
				remove_arquivo(disco, nome);
		}else if(strcmp(tipo, "otimiza") == 0){
			if(!cheio) 
				cheio = otimiza_disco(disco, D);
		/* Além de servir pra debugar, impede o programa de fazer besteira
		 * caso o usuário seja descuidado */
		}else{
			printf("\033[91mERRO: Operaçao desconhecida: %s\033[97m\n", tipo);
			exit(1);
		}
	}
	
	if(cheio) printf("ERRO: disco cheio\n");
	else imprime_disco(disco, D);

	removeLista(&disco);
	
	return true;
}
/* Converte únidades */
int Converte_pra_K(char X){
	switch ((int)(X)) {
	case ((int)('K')):
		return 1;
	case ((int)('M')):
		return 1024;
	case ((int)('G')):
		return 1024 * 1024;
	}
	return -1;
}

/* TAD de Disco, implementado com Listas Ligadas */
/************************************************/
/***********************************************/

/* Foi usada pra debugar, salvava o disco original antes de picotar */
void copia_disco(Lista A, Lista B){
	No* pB;
	if(vazia(A)){
		return;
	}
	for(pB = B->dir; pB != B; pB = pB->dir){
		cria_antes(A, A, pB->nome, pB->tam, pB->ocupado);
	}
}
/* Imprime uma única célula de acordo com as especificações do enunciado */
void imprime_celula(double P){
	P *= 100;
	if ((75 < P) && (P <= 100)) 
		printf("[ ]");
	else if((25 < P) && (P <= 75)) 
		printf("[-]");
	else if((0 <= P) && (P <= 25)) 
		printf("[#]");
	/*printf("\n");*/
}
/* Picota a lista em tamanhos fixos, estratégicos para imprimir 8 células */
void imprime_disco(Disco ini, int D){
	double parte = D/8.0;
	double jl = 0, livres = 0;
	double resto, tam;
	Arq* p;
	/*pLst(ini);*/
	for(p = ini->dir; p != ini; p = p->dir){
		jl += p->tam;
		if(p->ocupado == false){
			livres += p->tam;
		}
		if(jl == parte){
			imprime_celula(livres/parte);
			livres = 0;
			jl = 0;
		}else {
			tam = p->tam;
			while(jl > parte){
				jl -= tam;
				if(p->ocupado == false){
					livres -= tam;	
				}
				resto = parte - jl;
				jl += resto;
				if(p->ocupado == false){
					livres += resto;
				}
				imprime_celula(livres/jl);
				tam -= resto;
				jl = tam;
				if(p->ocupado == false){
					livres = tam;
				}else{
					livres = 0;
				}
			}
		}
	}if(jl > 0){
		imprime_celula(livres/parte);
	}

	/*picotaDisco(ini, parte);
	
	for(p = ini->dir; p != ini; p = p->dir){
		jl += p->tam;
		if(p->ocupado == false){
			livres += p->tam;
		}
		if(jl == parte){
			imprime_celula(livres/parte);
			livres = 0;
			jl = 0;
		}
	}*/
	
	printf("\n");
}
/* Picota os arquivos do disco de forma a fascilitar a impressão */
void picotaDisco(Disco A, double parte){
	double jl = 0;
	Arq *p;
	for(p = A->dir; p != A;){
		jl += p->tam;	
		if(jl < parte && jl + p->dir->tam > parte){
			p = p->dir;
			if(p != A) picotaArquivo(A, p, parte - jl);
			jl = 0;
		}else if(jl > parte){
			jl -= p->tam;
			picotaArquivo(A, p, parte - jl);
			jl = 0;
		}else{
			p = p->dir;
		}
	}
}
/* Divide um arquivo em duas partes, a primeira de tamanho slice */
void picotaArquivo(Disco A, Arq * p, double slice){
	if(p->tam <= slice || slice <= 0){
		return;
	}
	cria_antes(A, p, p->nome, slice, p->ocupado);
	atribui_tam(A, p, p->tam - slice);
}
/* Insere na prmeira menor posição livre, otimiza se necessário */
bool insere_arquivo(Disco disco, int D, int tam, char* nome){
	Arq *p, *menorlivre;
	bool tem_menor_livre = false;

	/* Serve apenas para inicializar menorlivre */
	Lista aux = (Lista)malloc(sizeof(No));
	/* Pra garantir que mesmo que o tamanho da menor partição 
	 * seja D a função insira nessa partição*/
	aux->tam = D*2;
	menorlivre = aux;

	if(disco->tam < tam) return true;

	/* Acha a posição com menor espaço livre, se tiver */
	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado == false && p->tam < menorlivre->tam && p->tam >= tam){
			menorlivre = p;	
			tem_menor_livre = true;		
		}
	}
	/* Se algum menor livre foi achado */
	if(tem_menor_livre){
		p = menorlivre;
		/* O arquivo é inserido */
		atribui_tam(disco, p, p->tam - tam);
		
		cria_antes(disco, p, nome, tam, true);
		
		/* Se a atribuição zerou p->tam, o nó pode ser removido */
		if(p->tam == 0)
			removeNo(disco, p);

		/* ... e o disco não está cheio */
		return false;
	}
	/* Se a função continua executando, nenhuma posição foi encontrada então
	 * o disco deve ser otimizado, se essa função retornar disco cheio, 
	 * essa informação é repassada para o retorno de insere_arquivo */
	if(otimiza_disco(disco, D))
		return true;
	
	/* Se a função continua executando a otimização teve sucesso
	 * então p é posicionado na ultima posição do disco */
	p = disco->esq;
	/* Se nessa posição o arquivo a ser inserido couber... */
	if(p->ocupado == false && tam <= p->tam){
		/* ... o arquivo é inserido ... */
		atribui_tam(disco, p, p->tam - tam);
		
		cria_antes(disco, p, nome, tam, true);
		
		/* Se a atribuição zerou p->tam, o nó pode ser removido */
		if(p->tam == 0)
			removeNo(disco, p);
		/* ... e o disco não está cheio */
		return false;
	/* Caso o arquivo não caiba, o disco está cheio */
	}else return true;
	return false;
}
/* Remove nós livres e, no final, insere um livre com o tamnho livre total */
bool otimiza_disco(Disco disco, int D){
	Arq* p;
	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado == false){
			removeNo(disco, p);
		}
	}
	if(disco->tam < 0) return true;
	
	cria_ultimo(disco, "", disco->tam);
	
	return false;
}
/* Libera arquivos ainda não liberados e mescla com adjacentes livres */
void remove_arquivo(Disco disco, char* nome){
	Arq* p;
	for(p = disco->dir; p != disco; p = p->dir){
		if(p->ocupado && strcmp(nome, p->nome) == 0){
			libera_arq(disco, p);
			
			/* Mescla com adjacentes livres */
			mescla(disco, p);
			return;
		}
	}
}
/* Mescla nós adjacentes livres e mantém o nome do nó central */
void mescla(Disco disco, Arq * p){
	if(!(p->dir->ocupado)){
		atribui_tam(disco, p, p->tam + p->dir->tam);
		removeNo(disco, p->dir);
	}
	if(!(p->esq->ocupado) && (p->esq != disco)){
		atribui_tam(disco, p, p->tam + p->esq->tam);
		removeNo(disco, p->esq);
	}
}



/* TAD de Listas Duplamente Ligadas, Circulares com Nós Cabeças  */ 
/****************************************************************/
/***************************************************************/

/* Cria o nó cabeça */
void cria_lista(Head nova_lista, int D){
	*nova_lista = (Lista)malloc(sizeof(No));
	
	(*nova_lista)->nome = (char*)malloc(10 * sizeof(char));
	(*nova_lista)->nome = strcpy((*nova_lista)->nome, "Head");

	/* No inicio o disco está todo livre */
	(*nova_lista)->tam = D;
	(*nova_lista)->ocupado = true;

	(*nova_lista)->dir = *nova_lista;
	(*nova_lista)->esq = *nova_lista;
}
/* Cria um nó e o insere no final da lista, antes do no cabeça */
void cria_ultimo(Lista ini, char nome[], int tam){
	if(tam != 0) cria_antes(ini, ini, nome, tam, false);
}
/* Cria nó e o insere antes de P, até quando P é o nó cabeça */
void cria_antes(Lista ini, No* P, char nome[], int tam, bool flag){
	No* novo;
	novo = (No*)malloc(sizeof(No));
	
	novo->tam = tam;
	/* Conforme explicado na função atribui, o tamnho livre só é contabilizado
	 * com base nos nós ocupados */
	if(flag == true) ini->tam -= tam;

	novo->nome = (char*)malloc(MAX_NOME * sizeof(char));
	novo->nome = strcpy(novo->nome, nome);

	novo->ocupado = flag;

	novo->dir = P;
	novo->esq = P->esq;
	P->esq = novo;
	novo->esq->dir = novo;
}

/* Atribui um tamanho e modifica o tamanho livre do disco usando o tamanho de 
 * nós ocupados como base, o que permite guardar o tamanho livre no nó cabeça
 * mesmo que não haja nenhum nó livre no disco, o que é muito útil pra decidir
 * se o disco está cheio ou não e para otimizar */
void atribui_tam(Lista ini, No* p, int tam){
	/* Só modifica o tamnho livre quando um nó ocupado é modificado */
	if (p->ocupado) {
		ini->tam += p->tam;
		p->tam = tam;
		ini->tam -= p->tam;
	/* Apesar dessa atribuição parecer irresponsável, os cuidados para manter
	 * os tamanhos de nós livres coerentes é tomado externamente a essa função
	 * garantindo sempre que a soma total dos tamnhos de nos livres seja igual
	 * a do nó cabeça, com excessão da função otimização */
	}else{
		p->tam = tam;
	}
}
/* Libera um arquivo sem remover o nó */
void libera_arq(Lista ini, No * p){
	if(p->ocupado){
		p->ocupado = false;
		ini->tam += p->tam;
	}
}
/* Remove o nó na posição A */
void removeNo(Lista ini, No * A){
	if(A == ini)
		return;
	/* No caso contrário nada é feito porque o 
	 * tamnho dos nós livres não é contabilizado */
	if(A->ocupado){
		libera_arq(ini, A);
	}

	free(A->nome);

	A->dir->esq = A->esq;
	A->esq->dir = A->dir;
	free(A);
}
/* Desaloca uma lista inteira */
void removeLista(Head h){
	/* (*h)->dir é a primeira posição já que (*h) aponta para o no cabeça */
	Lista temp, p = (*h)->dir;
	/* Percorre toda a lista até o nó cabeça */
	while(p != (*h)){
		temp = p;
		p = p->dir;
		/* Desolaca a memória alocada pra string e o nó*/
		free(temp->nome);
		free(temp);
	}
	/* Desolaca a memória alocada pra string e o nó cabeça */
	free(p->nome);
	free(p);
	*h = NULL;
}
/* Verifica se a lista está vazia */
bool vazia(Lista ini) {
	
	return ((ini) && (ini->esq == ini) && (ini->dir == ini));
}
/* Útil pra debugar */
void pLst(Lista ini){
	No* p;
	
	p = ini;
	if (p->tam >= 1024*1024)
			if (p->tam % (1024*1024))
				printf("Disco com %.2fGb livres\n", p->tam/(1024*1024.0));
			else
				printf("Disco com %.0fGb livres\n", p->tam/(1024*1024.0));
		else if (p->tam >= 1024)
			if (p->tam % 1024)
				printf("Disco com %.2fMb livres\n", p->tam/(1024.0));
			else
				printf("Disco com %.0fMb livres\n", p->tam/(1024.0));
		else
			printf("Disco com %dKb livres\n", p->tam);
	
	for(p = ini->dir; p != ini; p = p->dir){
		if(p->ocupado == true)
			printf("\033[94m");
		else
			printf("\033[91m");
		
		if (p->tam >= 1024*1024)
			if (p->tam % (1024*1024))
				printf("%s: %.2fGb\n", p->nome, p->tam/(1024*1024.0));
			else
				printf("%s: %.0fGb\n", p->nome, p->tam/(1024*1024.0));
		else if (p->tam >= 1024)
			if (p->tam % 1024)
				printf("%s: %.2fMb\n", p->nome, p->tam/(1024.0));
			else
				printf("%s: %.0fMb\n", p->nome, p->tam/(1024.0));
		else
			printf("%s: %dKb\n", p->nome, p->tam);
	}
	printf("\033[97m\n");
}

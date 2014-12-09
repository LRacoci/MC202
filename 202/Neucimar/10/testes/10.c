/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratório 10 - Hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/


/*tamanho máximo de nome de aluno*/
#define TAMMAXNOME 100 
#define TAM_TABELA 13

typedef enum bool{false, true} bool;

/* Define um nó de Árvore B sem nó pai, por que este é desnecessário */
typedef struct Aluno{
	int ra;
	char *nome;
} Aluno;

typedef struct No{
	Aluno *a;
	struct No *prox;
} No, *Lista;

typedef struct TabelaHash{
	Lista *l;
} TabelaHash;


/* TAD: Lista Ligada */
/********************/

/* TAD: Tabela */
/**************/

TabelaHash* CriaTabela();
void LiberaTabela(TabelaHash *t);
bool InsereTabela(TabelaHash *t, Aluno *a);
bool ConsultaTabela(TabelaHash *t, char buf[TAMMAXNOME], Aluno *a);
bool RemoveTabela(TabelaHash *t, char buf[TAMMAXNOME]);
void ImprimeTabela(TabelaHash *t);
int NumeroAlunosTabela(TabelaHash *t);




/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

/*le RA e nome de aluno*/
void LeAluno(Aluno *a);

/*le linha de comando*/
void lelinha();

/* Programa que implementa Arvores B com chaves inteiras na memória */
int main(int argc, char *argv[]) {

	TabelaHash *t = CriaTabela();
	char comando[100], buf[TAMMAXNOME];
	Aluno a;  

	/*loop para ler entrada*/
	while (scanf("%s", comando) > 0 ){
		if(strcmp(comando,"insere") == 0){
			LeAluno(&a);
			printf("Insere: %06d \"%s\"\n", a.ra, a.nome);
			/* Insere aluno 'a' na tabela 't' */
			if (!InsereTabela(t, &a)) {	
				printf("Nome repetido: \"%s\"\n", a.nome);
				free(a.nome);
			}

		} else if ( strcmp(comando, "remove") == 0 ) {

			scanf(" \"%[^\"]\"", buf);
			printf("Remove: \"%s\"\n", buf);
			/* remove aluno de nome 'buf' da tabela 't'*/
			if (!RemoveTabela(t, buf))	
			printf("Nome inexistente: \"%s\"\n", buf);

		} else if ( strcmp(comando, "consulta") == 0 ) {

			scanf(" \"%[^\"]\"", buf);
			printf("Consulta: \"%s\"\n", buf);
			if (ConsultaTabela(t, buf, &a)) 
			/*consulta aluno de nome 'buf' na tabela 't', grava dados em 'a', retorna 0 se nao encontrou aluno*/
			printf("%06d \"%s\"\n", a.ra, a.nome);
			else
			printf("Nome inexistente: \"%s\"\n", buf);

		} else if ( strcmp(comando, "imprime") == 0 ) {
			/*Calcula numero de alunos na tabela 't'*/
			printf("\nImprime Tabela: %d aluno(s):\n", NumeroAlunosTabela(t)); 
			ImprimeTabela(t);
			printf("\n");
		/*termina programa*/
		} else if ( strcmp(comando, "sair") == 0 ) { 
			break;
		} else {
			printf("Comando desconhecido: `%s´\n", comando);
		}
	}

	LiberaTabela(t); /*libera memoria*/

	return 0;
}

/* IMPLEMENTAÇÃO DE OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/*le RA e nome de aluno*/
void LeAluno(Aluno *a) {
	char buf[TAMMAXNOME];
	scanf("%d \"%[^\"]\"", &a->ra, buf);

	a->nome = malloc(strlen(buf)+1);
	strcpy(a->nome, buf);
	return;
}

/*le linha de comando*/
void lelinha() {
	int c;
	do { 
		c = getchar(); 
	} while (c != '\n');
}

short int hash(char* nome){
	short int i;
	unsigned char resp = 0;

	for(i = 0; nome[i]; i++){
		resp ^= nome[i];
	}
	return (short int)resp%TAM_TABELA;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */ 
/*****************************************/
/****************************************/

/* TAD: TAbela Hash */
/********************/

TabelaHash* CriaTabela(){
	short int i;
	TabelaHash *nova_tabela;
	nova_tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
	nova_tabela->l = (Lista*)malloc(TAM_TABELA * sizeof(Lista));
	for(i = 0; i < TAM_TABELA; i++){
		nova_tabela->l[i] = NULL;
	}
	return nova_tabela;
}
void LiberaTabela(TabelaHash *t){
	short int i;
	Lista temp, p;
	for(i = 0; i < TAM_TABELA; i++){
	p = t->l[i];
		while(p){
			temp = p;
			p = p->prox;
			free(temp->a->nome);
			free(temp->a);
			free(temp);
		}
	}
	free(t);
}
bool InsereTabela(TabelaHash *t, Aluno *a){
	short int h = hash(a->nome);
	/*Aluno lixo;*/
	Lista nova, aux = t->l[h];
	/*if(ConsultaTabela(t, a->nome, &lixo)) 
		return false;
	*/
	if(aux == NULL){
		nova = (Lista)malloc(sizeof(No));
		nova->a = (Aluno*)malloc(sizeof(Aluno));
		nova->a->nome = (char*)malloc((strlen(a->nome) + 1) * sizeof(char));
		strcpy(nova->a->nome, a->nome);
		nova->a->ra = a->ra;
		nova->prox = NULL;
		t->l[h] = nova;
		return true;
	}
		
	while(aux->prox && strcmp(aux->prox->a->nome, a->nome) < 0){
		printf("aux->prox->nome = %s \n", aux->prox->a->nome);
		printf("a->nome = %s \n", a->nome);
		aux = aux->prox;
	}
	if(strcmp(a->nome, aux->a->nome) == 0){
		return false;
	}
	
	/*insere_lista(t->l[h], a);*/
	nova = (Lista)malloc(sizeof(No));
	nova->a = (Aluno*)malloc(sizeof(Aluno));
	nova->a->nome = (char*)malloc((strlen(a->nome) + 1) * sizeof(char));
	strcpy(nova->a->nome, a->nome);
	nova->a->ra = a->ra;
	
	nova->prox = aux->prox;
	aux->prox = nova;
	

	return true;
}
bool ConsultaTabela(TabelaHash *t, char buf[TAMMAXNOME], Aluno *a){
	short int h = hash(buf);
	Lista ini = t->l[h], p = ini;
	while(p && strcmp(p->a->nome, buf)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}
		
	a->nome = p->a->nome;
	a->ra = p->a->ra;
	return true;
}
bool RemoveTabela(TabelaHash *t, char buf[TAMMAXNOME]){
	short int h = hash(buf);
	Lista ini = t->l[h];
	Lista p = ini, temp;
	
	if(!p){
		return false;
	}

	while(p->prox && strcmp(p->prox->a->nome, buf)){
		p = p->prox;
	}
	if(p->prox == NULL){
		return false;
	}
	temp = p->prox;
	p = p->prox->prox;
	free(temp);
	return true;
}
void ImprimeTabela(TabelaHash *t){
	short int i;
	Lista aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			printf("(%d) %d \"%s\"\n", i, aux->a->ra, aux->a->nome);
			aux = aux->prox;
		}

	}
}
int NumeroAlunosTabela(TabelaHash *t){
	short int i;
	int r = 0;
	Lista aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			r++;
			aux = aux->prox;
		}
	}
	return r;
}

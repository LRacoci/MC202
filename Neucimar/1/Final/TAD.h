/*Funções básicas de lista*/
Lista cria_lista();
Lista insere_no(No* p, int info, int k);
void remove_no(No* p, int *info, int *k);
/*Funções de remover lista r = recursiva; i = interativa*/
void RemoveLst_i(Lista *p);
void RemoveLst_r(Lista ini);

/*Funcções de debugar*/
void pLst(Lista ini, char nome[]) ;
void pVet(int v[], int n);

/*Funções principais*/

int MTF(Lista* ini, int chave);
int TR(Lista* ini, int chave);
int FC(Lista* ini, int chave);

/*Funções auxiliares direta das principais*/
void TrocaNos(Lista * ini; No* A, No* B);
void Ordena_Lst(Lista * ini);
void zera_K(Lista ini);
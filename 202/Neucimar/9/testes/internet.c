
const
     T = 2,
     MAX_CHAVES = 2 * T - 1, /* Quantidade máxima de chaves */
     MAX_FILHOS = 2 * T, /* Quantidade máxima de filho */
     MIN_OCUP = T - 1; /* Ocupação mínima em cada nó */
typedef struct Page ArvB;

struct Page {
   int tam; /* Quantidades de chaves contida no nó */
   int chave[MAX_CHAVES]; /* Chaves armazenadas no nó */
   ArvB filho[MAX_FILHOS]; /* Ponteiro para os filho */
};

/* Insere uma chave e o ponteiro para o filho da direita em um nó */
void insere_chave(ArvB t, int info, ArvB filhodir){
	int i, pos;

	/* busca para obter a posição ideal para inserir a nova chave */
	pos = busca_binaria(t, info);
	i = t->tam;

	/* realiza o remanejamento para manter as chave ordenadas */
	while (i > pos && info < t->chave[i-1]){
		t->chave[i] = t->chave[i-1];
		t->filho[i+1] = t->filho[i];
		i--;
	}
	/* insere a chave na posição ideal */
	t->chave[pos] = info;
	t->filho[pos+1] = filhodir;
	t->tam++;
}

/* Realiza a busca do nó para inserir a chave e faz as subdivisões quando necessárias */
ArvB insere(ArvB t, int info, bool *h, int *info_retorno){
	/* auxiliar para armazenar a chave que irá subir para o pai */
	int i, j, pos, chave_meio; 
	/* ponteiro para o filho à direita da chave  */
	ArvB temp, filho_dir; 
	if(t == NULL){
		/* O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha) */
		*h = true;
		*info_retorno = info;
		return(NULL);
	}
	pos = busca_binaria(t,info);
	if(t->tam > pos && t->chave[pos] == info){
         printf("Chave já contida na Árvore");
         *h = false;
	}else{
		/* desce na árvore até encontrar o nó folha para inserir a chave. */
		filho_dir = insere(t->filho[pos],info, h, info_retorno);
		 /* Se h for true deve inserir a info_retorno no nó. */
		if(*h){
			/* Tem espaço na página */
			if(t->tam < MAX_CHAVES) {
				insere_chave(t, *info_retorno, filho_dir);
				*h = false;
			/* Overflow. Precisa subdividir */
			}else{ 
				
				temp = (ArvB ) malloc(sizeof(ArvB));
				temp->tam = 0;
				/* inicializa filho com NULL */
				for(i = 0; i < MAX_FILHOS; i++)
					temp->filho[i] = NULL;

				/* elemento mediano que vai subir para o pai */
				chave_meio = t->chave[MIN_OCUP];

				/* insere metade do nó t no temp (efetua subdivisão) */
				temp->filho[0] = t->filho[MIN_OCUP+1];
				for(i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
					insere_chave(temp, t->chave[i], t->filho[i+1]);

				/* atualiza nó t.  */
				for(i = MIN_OCUP; i<MAX_CHAVES; i++){
					t->chave[i] = 0;
					t->filho[i+1] = NULL;
				}
				t->tam = MIN_OCUP;

				/* Verifica em qual nó será inserida a nova chave */
				if(pos <= MIN_OCUP){
					insere_chave(t, *info_retorno, filho_dir);
				}else {
					insere_chave(temp, *info_retorno, filho_dir);
				}

				/* retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano. */
				*info_retorno = chave_meio;
				return(temp);
			}
		}
	}
}

ArvB insere_ArvB(ArvB t, int info){
	bool h;
	int info_retorno, i;
	ArvB filho_dir, nova_t;

	filho_dir = insere(t, info, &h, &info_retorno);
	/* Aumetará a altura da árvore */
	if(h){
 		nova_t = (ArvB ) malloc(sizeof(ArvB));
 		nova_t->tam = 1;
 		nova_t->chave[0] = info_retorno;
 		nova_t->filho[0] = t;
 		nova_t->filho[1] = filho_dir;
 		for (i = 2; i <= MAX_CHAVES; i++)
			nova_t->filho[i] = NULL;
 		return(nova_t);
	}else{
		return(t);
	}
}
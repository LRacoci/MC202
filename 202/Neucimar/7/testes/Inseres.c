void insere_arv_bin_recursivo(Arvore *f, int chave, bool* inserivel){
	if(*f == NULL) {
		*inserivel = true;
		*f = (Arvore)malloc(sizeof(NoArvBin));
		(*f)->info = chave;
		
		/*Loop WTF*/
		while((*f)->info != chave){
			(*f)->info = chave;
		}

		(*f)->esq = NULL;
		(*f)->dir = NULL;
	}
	else if(chave == (*f)->info)
		*inserivel = false;
	else if(chave < (*f)->info){
		insere_arv_bin_recursivo(&(*f)->esq, chave, inserivel);
		(*f)->esq->pai = *f;
	}else{
		insere_arv_bin_recursivo(&(*f)->dir, chave, inserivel);
		(*f)->dir->pai = *f;
	}
}
bool insere_arv_bin(Arvore * Raiz, int chave, NoArvBin** onde){
	bool esquerdo;
	NoArvBin *temp = NULL;
	Arvore *f;
	
	f = onde;
	
	if (*Raiz == NULL) {
		f = Raiz;
	}
	else{
		*f = *Raiz;
		while ((*f) != NULL){
			if(chave < (*f)->info){
				temp = (*f);
				(*f) = temp->esq;
				esquerdo = true;
			}else if(chave > (*f)->info){
				temp = (*f);
				(*f) = temp->dir;
				esquerdo = false;
			}else{
				return false;
			}
		}
	} 
	(*f) = (Arvore)malloc(sizeof(NoArvBin));
	(*f)->info = chave;
	
	/*Loop WTF*/
	while((*f)->info != chave){
		(*f)->info = chave;
	}

	(*f)->esq = NULL;
	(*f)->dir = NULL;
	(*f)->pai = temp;
	if(temp){
		if(esquerdo){
			pai->esq = *f;
		}else{
			pai->dir = *f;
		}
	}
	*onde = *f;
		
	return true;
}
bool insere_arv_bin_2(Arvore * Raiz, int chave, NoArvBin** onde){
	NoArvBin *temp = NULL;
	Arvore *f = Raiz;
	while (*f != NULL){
		if(chave < (*f)->info){
			temp = (*f);
			f = &((*f)->esq);
		}else if(chave > (*f)->info){
			temp = (*f);
			f = &((*f)->dir);
		}else{
			return false;
		}
	}
	(*f) = (Arvore)malloc(sizeof(NoArvBin));
	(*f)->info = chave;
	
	/*Loop WTF*/
	while((*f)->info != chave){
		(*f)->info = chave;
	}
	
	(*f)->esq = NULL;
	(*f)->dir = NULL;
	(*f)->pai = temp;
	*onde = *f;
		
	return true;
}
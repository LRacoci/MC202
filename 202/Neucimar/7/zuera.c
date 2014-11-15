void rot_esq(PArvBin *q) {
    PArvBin p;
    
    p = (*q)->pai;
    (*q)->pai = p->pai;
    p->dir = (*q)->esq;
    (*q)->esq = p;
    p->dir->pai = p;
    if (p->pai != NULL) {
        if (p->pai->esq == p) {
            p->pai->esq = *q;
        } else {
            p->pai->dir = *q;
        }
    }
    p->pai = *q;
    
}

void rot_dir(PArvBin *q) {
    PArvBin p;
    
    p = (*q)->pai;
    (*q)->pai = p->pai;
    p->esq = (*q)->dir;
    (*q)->dir = p;
    p->esq->pai = p;
    if (p->pai != NULL) {
        if (p->pai->esq == p) {
            p->pai->esq = *q;
        } else {
            p->pai->dir = *q;
        }
    }
    p->pai = *q;
    
}
void rotacao(NoArvBin * f) {
    /* Nesse caso f é o filho esquerdo */
    if(f->pai->esq == f){
        f->dir->pai = f->pai;
        f->pai->esq = f->dir;
        f->dir = f->pai;
        f->pai = f->dir->pai;
        if(f->pai){
            if(f->pai->dir == f->dir) f->pai->dir = f;
            else f->pai->esq = f;
        }
        f->dir->pai = f;
    }else{
        f->esq->pai = f->pai;
        f->pai->dir = f->esq;
        f->esq = f->pai;
        f->pai = f->esq->pai;
        if(f->pai){
            if(f->pai->dir == f->esq) f->pai->dir = f;
            else f->pai->esq = f;
        }
        f->esq->pai = f;
    }
}
int custo_TR(Arquivo *p, int *requerimentos, int R, int N) {
    int custo = 0, i, flag_inicio;
    PArquivo aux;
    
    /* Procura cada requerimento na lista */
    for (i = 0; i < R; i++) {
        flag_inicio = 0;
        
        custo++;
        
        aux = p;
        if (aux->prox->info == requerimentos[i]) {
            flag_inicio = 1;
        }
        
        while ((aux->prox->prox != NULL) && (!flag_inicio)) {
            custo++;
            if (aux->prox->prox->info == requerimentos[i]) {
                break;
            }
            aux = aux->prox;
        }
        
        if ((aux->prox->prox != NULL) && (!flag_inicio)) {
            custo++;
            troca(&aux, aux->prox);
        }
    }
    
    return custo;
}
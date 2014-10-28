/* Nome: Luiz Fernando Rodrigues da Fonseca
 * RA: 156475
 * Laboratorio 05 - Gerente do Espaço */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
#define MAX_NOME 11
#define MAX_MEM 3
#define MAX_TAM 8
typedef struct Disco {
    int mem;
    char formato[MAX_MEM];
    char arq[MAX_NOME];
    int usado;
    struct Disco *prox;
} Disco, *PDisco;
typedef struct Disco_Final {
    double mem_parte;
    double mem_livre;
    double mem_usada;
    double P;
} Disco_Final;
/* funcao Converte_memoria: converte o valor de memoria para Kb */
void Converte_memoria(int *mem_disco, char *tam_disco);
/* funcao inicia_disco: cria uma lista com no cabeca e cria um primeiro
 * bloco que contem toda a memoria livre no disco */
void inicia_disco(PDisco disco, int *mem_disco, char *tam_disco);
/* funcao remove_no: remove um no da lista */
void remove_no(PDisco aux);
/* funcao junta_espacos_livres: junta espacos livres subsequentes no disco */
void junta_espacos_livres(PDisco disco);
/* funcao otimiza_disco: desloca todos os espacos livres para o fim do disco */
void otimiza_disco(PDisco disco);
/* funcao procura_espaco: procura um espaco onde caiba o arquivo
 * a ser inserido */
Disco *procura_espaco(PDisco disco, Disco temp);
/* funcao insere_no: insere um no na lista */
void insere_no(PDisco aux, PDisco temp);
/* funcao modifica_no: modifica um no da lista */
void modifica_no(PDisco aux, PDisco temp);
/* funcao insere_disco: insere o arquivo com suas informacoes em
 * um espaco disponivel no disco, se existir */
void insere_disco(PDisco disco, int *erro);
/* funcao remove_disco: remove um arquivo com um determinado nome do disco */
void remove_disco(PDisco disco);
/* funcao divide_disco_em_oito: divide a representacao final do disco
 * em 8 partes, cada uma com um oitavo da memoria total do disco */
void divide_disco_em_oito(Disco_Final *est_f, int mem_disco);
/* funcao atribui_memoria: vai atribuindo a memoria do disco
 * para o vetor da representacao final */
void atribui_memoria(Disco_Final *est_f, PDisco disco);
/* funcao imprime_disco: imprime uma representacao do disco com 8 partes */
void imprime_disco(Disco_Final *est_f);
/* funcao libera_disco: libera a memoria alocada para o disco */
void libera_disco(PDisco disco);
/* funcao operacoes_disco: simula as operacoes do disco */
void operacoes_disco(int N);
void imprimelista(PDisco disco);
/* SEU PROGRAMA - MAIN */
int main() {
    int N;
    
    /* Entrada do numero de operacoes do primeiro caso de teste */
    scanf("%d", &N);
    
    /* Enquanto N for diferente de 0, realiza as N operacoes no disco */
    while (N != 0) {
        operacoes_disco(N);
        
        /* Entrada do numero de operacoes de outro caso teste */
        scanf("%d", &N);
    }
    
    return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
void Converte_memoria(int *mem_disco, char *tam_disco) {
    
    /* Converte as grandezas de memoria para Kb */
    if (strcmp(tam_disco, "Mb") == 0) {
        *mem_disco = (*mem_disco) * 1024;
    } else if (strcmp(tam_disco, "Gb") == 0) {
        *mem_disco = (*mem_disco) * 1024 * 1024;
    }
    
}

void inicia_disco(PDisco disco, int *mem_disco, char *tam_disco) {
    PDisco aux;
    
    /* Inicia o no cabeca com as informacoes do tamanho da memoria
     * convertido para Kb e um indicador de -1 para o inicio do disco */
    Converte_memoria(mem_disco, tam_disco);
    disco->mem = *mem_disco;
    strcpy(disco->formato, "Kb"); 
    disco->usado = -1;
    disco->prox = NULL;
    
    /* Inicia o disco com um bloco de memoria do tamanho total do
     * disco, com a flag igual a 0, ja que nao esta sendo usado */
    aux = (PDisco)malloc(sizeof(Disco));
    aux->mem = disco->mem;
    aux->usado = 0;
    aux->prox = disco->prox;
    disco->prox = aux;
    
}

void remove_no(PDisco aux) {
    PDisco temp;
    
    /* Remove o no posterior a aux */
    temp = aux->prox;
    aux->prox = temp->prox;
    free(temp);
    
}

void junta_espacos_livres(PDisco disco) {
    PDisco aux = disco->prox;
    
    /* Procura espacos vazios ate o final do disco */
    while (aux->prox != NULL) {
        /* Se algum for achado, checa se o proximo dele tambem e vazio:
         * se for, une os dois; se nao, procura nas proximas posicoes */
        if (aux->usado == 0) {
            if (aux->prox->usado == 0) {
                aux->mem += aux->prox->mem;
                remove_no(aux);
            } else {
                aux = aux->prox;
            }
        } else {
            aux = aux->prox;
        }
    }
    
}

void otimiza_disco(PDisco disco) {
    PDisco aux, novo;
    
    /* Percorre o disco procurando espacos livres */
    for (aux = disco; aux->prox != NULL; aux = aux->prox) {
        /* Junta os espacos livres subsequentes */
        junta_espacos_livres(disco);
        /* Se um espaco em branco for encontrado, retira esse no de sua
         * posicao e cria outro no final com as mesmas caracteristicas
         * e com a memoria livre disponivel no disco */
        if (aux->prox->usado == 0) {
            novo = aux;
            while (novo->prox != NULL) {
                novo = novo->prox;
            }
            insere_no(novo, aux->prox);
            novo->prox->usado = 0;
            remove_no(aux);
        }
        
    }
    
    aux->mem = disco->mem;
    
}

Disco *procura_espaco(PDisco disco, Disco temp) {
    PDisco aux = disco, menor = NULL;
    
    /* Checa se existe um espaco livre disponivel no disco
     * que suporte o tamanho de memoria do novo arquivo */
    while (aux->prox != NULL) {
        if ((aux->prox->usado == 0) && (aux->prox->mem >= temp.mem)) {
            /* Se uma posicao foi achada, ela e a menor possivel
             * para o arquivo; se outra menor for encontrada,
             * muda o local de insercao do arquivo */
            if (menor == NULL) {
                menor = aux;
            } else if (menor->prox->mem > aux->prox->mem) {
                menor = aux;
            }
        }
        aux = aux->prox;
    }
    
    /* Se nenhuma posicao de memoria foi encontrada, otimiza
     * o disco e procura novamente pela menor posicao */
    if (menor == NULL) {
        otimiza_disco(disco);
        aux = disco;
        
        while (aux->prox != NULL) {
            if ((aux->prox->usado == 0) && (aux->prox->mem >= temp.mem)) {
                if (menor == NULL) {
                    menor = aux;
                } else if (menor->prox->mem > aux->prox->mem) {
                    menor = aux;
                }
            }
            aux = aux->prox;
        }
    }
    
    /* Se nao ouverem espacos em branco que suportem o arquivo,
     * retorna a posicao anterior ao final do disco */
    if ((aux->prox == NULL) && (menor == NULL)) {
        return aux;
    }
    
    /* Se nao, retorna a posicao anterior a do menor */
    return menor;
}

void insere_no(PDisco aux, PDisco temp) {
    PDisco novo;
    
    /* Cria um novo no do tipo disco e o insere no final
     * do disco, com todas as informacoes do tipo */
    novo = (PDisco)malloc(sizeof(Disco));
    novo->mem = temp->mem;
    strcpy(novo->formato, temp->formato);
    strcpy(novo->arq, temp->arq);
    novo->prox = aux->prox;
    aux->prox = novo;
    
}

void modifica_no(PDisco aux, PDisco temp) {
    
    /* Modifica as informacoes do no com as informacoes do tipo */
    aux->mem = temp->mem;
    strcpy(aux->formato, temp->formato);
    strcpy(aux->arq, temp->arq);
    aux->usado = 1;
    
}

void insere_disco(PDisco disco, int *erro) {
    PDisco aux;
    Disco temp;
    int mem_aux = 0;
    
    /* Le os dados do arquivo para a insercao e armazena num no temporario */
    scanf("%s %d %s", temp.arq, &temp.mem, temp.formato);
    
    /* Transforma o tamanho da memoria do arquivo */
    Converte_memoria(&temp.mem, temp.formato);
    
    /* Procura um espaco para o arquivo no disco */
    aux = procura_espaco(disco, temp);
    
    /* Se houver espaco disponivel faz as operacoes;
     * se nao, muda o valor da flag de erro */
    if (disco->mem - temp.mem >= 0) {
        /* Se existir bloco disponivel, coloca a memoria
         * que restar do bloco numa variavel auxiliar */
        if (aux->prox->mem - temp.mem > 0) {
            mem_aux = aux->prox->mem - temp.mem;
        }
        /* Decrementa a memoria livre no disco e modifica o no */
        disco->mem -= temp.mem;
        modifica_no(aux->prox, &temp);
        /* Se houver memoria sobrando daquele bloco, cria um novo no
         * com aquela quantidade de memoria e muda para nao usado */
        if (mem_aux != 0) {
            temp.mem = mem_aux;
            insere_no(aux->prox, &temp);
            aux->prox->prox->usado = 0;
        }
        /* Zera a variavel auxiliar */
        mem_aux = 0;
    } else {
        *erro = 1;
    }
    
}

void remove_disco(PDisco disco) {
    PDisco aux;
    Disco temp;
    
    /* Le os dados do arquivo para a remocao */
    scanf("%s", temp.arq);
    
    /* Procura o arquivo com aquele nome para a remocao: se achar,
     * muda ele para nao usado e incrementa a memoria do disco */
    for (aux = disco; aux->prox != NULL; aux = aux->prox) {
        if ((strcmp(aux->prox->arq, temp.arq) == 0) &&
            (aux->prox->usado == 1)) {
            aux->prox->usado = 0;
            disco->mem += aux->prox->mem;
            break;
        }
    }
    
    /* Junta espacos livres de memoria nao usada subsequentes */
    junta_espacos_livres(disco);
    
}

void divide_disco_em_oito(Disco_Final *est_f, int mem_disco) {
    int i;
    
    /* Divide a memoria do disco em 8 partes, inicia a memoria livre
     * com a memoria total da parte, inicia a memoria usada com zero
     * e a porcentagem de memoria livre de cada parte com zero */
    for (i = 0; i < MAX_TAM; i++) {
        est_f[i].mem_parte = (double) mem_disco / (double) MAX_TAM;
        est_f[i].mem_livre = (double) mem_disco / (double) MAX_TAM;
        est_f[i].mem_usada = 0.0;
        est_f[i].P = 0.0;
    }
    
}

void atribui_memoria(Disco_Final *est_f, PDisco disco) {
    PDisco aux = disco->prox;
    int i = 0;
    double mem_aux = (double) aux->mem;
    
    /* Percorre o disco ate o final colocando a memoria
     * na representacao de 8 partes que saira */
    while (aux != NULL) {
        /* Se a memoria do no que esta sendo tratada somada da
         * memoria ja usada da representacao sao menores ou
         * igual a memoria total da parte, realiza operacoes */
        if ((mem_aux + est_f[i].mem_usada) <= est_f[i].mem_parte) {
            /* Se a memoria do no esta sendo usado, acrescenta a
             * memoria usada e decrementa a memoria livre do vetor,
             * e coloca zera a memoria auxiliar; se a memoria
             * nao esta sendo usada, nao decrementa a livre */
            if (aux->usado == 1) {
                est_f[i].mem_usada += mem_aux;
                est_f[i].mem_livre -= mem_aux;
                mem_aux = 0;
            } else if (aux->usado == 0) {
                est_f[i].mem_usada += mem_aux;
                mem_aux = 0;
            }
        } else {
            /* Se a soma e maior que o total da parte, realiza as operacoes:
             * se o no esta sendo usado, decrementa a memoria auxiliar e a
             * memoria livre com a memoria da parte subtraida da memoria
             * usada, e acrescenta a memoria usada com este mesmo valor;
             * se o no nao esta sendo usado, nao decrementa a livre */
            if (aux->usado == 1) {
                mem_aux -= est_f[i].mem_parte - est_f[i].mem_usada;
                est_f[i].mem_livre -= est_f[i].mem_parte - est_f[i].mem_usada;
                est_f[i].mem_usada += est_f[i].mem_parte - est_f[i].mem_usada;
            } else if (aux->usado == 0) {
                mem_aux -= est_f[i].mem_parte - est_f[i].mem_usada;
                est_f[i].mem_usada += est_f[i].mem_parte - est_f[i].mem_usada;
            }
        }
        /* Se a memoria usada estiver igual a memoria total da parte,
         * incrementa a posicao do vetor de representacao final */
        if (est_f[i].mem_usada == est_f[i].mem_parte) {
            i++;
        }
        /* Se a memoria auxiliar for zero, toda ela ja foi passada para
         * o vetor, entao vai para o proximo no e atualiza a memoria
         * auxiliar se o proximo no nao for o final do disco */
        if (mem_aux == 0) {
            aux = aux->prox;
            if (aux != NULL) {
                mem_aux = aux->mem;
            }
        }
    }
    
}

void imprime_disco(Disco_Final *est_f) {
    int i;
    
    /* Para cada parte de 8, calcula a porcentagem de memoria livre
     * usada e: se for menor ou igual 25, sai o caractere '#'; se for
     * maior que 25 e menor ou igual 75, sai o caraactere '-'; e se
     * for maior que 75 e menor ou igual a 100, sai o caractere ' ' */
    for (i = 0; i < MAX_TAM; i++) {
        est_f[i].P = (est_f[i].mem_livre / est_f[i].mem_parte) * 100.0;
        if (est_f[i].P <= 25) {
            printf("[#]");
        } else if (est_f[i].P <= 75) {
            printf("[-]");
        } else if (est_f[i].P <= 100) {
            printf("[ ]");
        }
    }
    
    printf("\n");
    
}

void libera_disco(PDisco disco) {
    PDisco aux = disco;
    
    /* Libera os nos da lista que representa o disco;
     * com excecao do no cabeca, que e estatico */
    while (aux->prox != NULL) {
        remove_no(aux);
    }
    
}

void operacoes_disco(int N) {
    int i, mem_disco, erro = 0;
    char tam_disco[MAX_MEM], operacao[MAX_NOME];
    Disco disco;
    Disco_Final estado_final[MAX_TAM];
    
    /* Entrada do tamanho de memoria do disco */
    scanf("%d %s", &mem_disco, tam_disco);
    
    /* Cria o disco que é feito com uma lista ligada com no cabeca */
    inicia_disco(&disco, &mem_disco, tam_disco);
    
    /* Realiza as N operacoes de um caso teste */
    for (i = 1; i <= N; i++) {
        /* Le a operacao */
        scanf("%s", operacao);
        
        /* Ela pode ser: insere, remove ou otimiza */
        if (strcmp(operacao, "insere") == 0) {
            insere_disco(&disco, &erro);
        } else if (strcmp(operacao, "remove") == 0) {
            remove_disco(&disco);
        } else if (strcmp(operacao, "otimiza") == 0) {
            otimiza_disco(&disco);
        }
       /* imprimelista(&disco); */
    }
    
    /* Saida do estado final do disco se todas as operacoes foram
     * executadas sem erro; se nao, produz uma mensagem de erro */
    if (erro) {
        printf("ERRO: disco cheio\n");
    } else {
        /* Divide a memoria total do disco em 8 partes para a
         * saida de uma estimativa do estado final do disco */
        divide_disco_em_oito(estado_final, mem_disco);
        
        /* Atribui os valores de memoria nas posicoes
         * do disco para a representacao final */
        atribui_memoria(estado_final, &disco);
        
        /* Imprime a representacao do estado final do disco */
        imprime_disco(estado_final);
    }
    
    /* Libera a memoria do disco alocado */
    libera_disco(&disco);
    
}

void imprimelista(PDisco disco) {
    PDisco aux;
    printf("%d\n", disco->mem);
    for (aux = disco->prox; aux != NULL; aux = aux->prox) {
        printf("%d %s %s %d\n", aux->mem, aux->formato,
               aux->arq, aux->usado);
    }
    
}
/* Nome: Luiz Fernando Rodrigues da Fonseca
 * RA: 156475
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* STRUCTS, DEFINIÃ‡Ã•ES E CABEÃ‡ALHOS DAS FUNÃ‡Ã•ES DA TAD */
typedef struct Matrioshka {
    int dado;
    int soma_do_nivel;
} Matrioshka, *PMatrioshka;

typedef struct Pilha {
    int topo;
    struct Matrioshka **bonecas;
} Pilha;
/* funcao cria_pilha: cria a estrutura da pilha, que tera um
 * vetor para as Matrioshkas que serao empilhadas */
Pilha *cria_pilha(int n);
/* funcao empilha: insere uma nova Matrioshka na pilha */
void empilha(Pilha *p, int dado);
/* funcao desempilha: retira uma Matrioshka da pilha */
void desempilha(Pilha *p);
/* funcao Testa_Matrioshka: checa se a sequencia dada forma
 * uma Matrioshka Generalizada ou nao */
void Testa_Matrioshka(int n);

/* PROGRAMA - MAIN */
int main() {
    int n;
    
    /* Entrada do tamanho da primeira sequencia
     * de brinquedos a ser lida */
    scanf("%d", &n);
    
    /* Enquanto o valor n da entrada for diferente de 0, havera algum
     * caso para testar se e Matrioshka Generalizada */
    while (n != 0) {
        Testa_Matrioshka(n);
        
        scanf("%d", &n);
    }
    
    return 0;
}

/* IMPLEMENTAÃ‡ÃƒO DAS FUNÃ‡Ã•ES DA TAD */
Pilha *cria_pilha(int n) {
    Pilha *p;
    
    /* Aloca uma pilha que vai guardar um vetor, tambem alocado,
     * de ponteiros que apontam para as Matrioshkas, e inicializa
     * seu topo com o valor 0 */
    p = (Pilha *)malloc(sizeof(Pilha));
    p->bonecas = malloc(n * sizeof(Matrioshka *));
    p->topo = 0;
    
    return p;
}

void empilha(Pilha *p, int dado) {
    
    /* Coloca na pilha uma nova Matrioshka, atribui o valor do
     * tamanho da boneca, inicia a soma do tamanho do nivel
     * com o valor 0, e incrementa o topo da pilha */
    p->bonecas[p->topo] = malloc(sizeof(Matrioshka));
    (p->bonecas[p->topo])->dado = dado;
    (p->bonecas[p->topo])->soma_do_nivel = 0;
    p->topo++;
    
}

void desempilha(Pilha *p) {
    
    /* Decrementa o topo da pilha e libera a memoria alocada
     * para a Matrioshka que estava abaixo do topo */
    p->topo--;
    free(p->bonecas[p->topo]);
    
}

void Testa_Matrioshka(int n) {
    Pilha *p;
    int i, dado, generalizada;
    
    /* Cria a pilha */
    p = cria_pilha(n);
    
    /* Inicializa a flag com 1, pois no comeco as sequencias
     * podem se tornar Matrioshkas Generalizadas */
    generalizada = 1;
    
    /* Le os valores das bonecas e realiza as comparacoes para
     * saber se a sequencia forma uma Matrioshka Generalizada */
    for (i = 0; i < n; i++) {
        scanf("%d", &dado);
        
        /* Se o topo da pilha estiver vazio, coloca uma Matrioshka nele;
         * mas se ele nao estiver vazio, realiza operacoes diferentes
         * para quando o tamanho e positivo e para quando e negativo */
        if (p->topo == 0) {
            empilha(p, dado);
        } else if (dado < 0) {
            /* Sendo o tamanho negativo, se seu valor absoluto mais a soma
             * do nivel anterior for igual ou maior que o tamanho absoluto
             * da boneca anterior, nao pode ser Matrioshka Generalizada;
             * do contrario, acresce a soma do nivel anterior com o valor
             * absoluto do tamanho e coloca a nova boneca na pilha */
            if ((abs(dado) + p->bonecas[p->topo - 1]->soma_do_nivel) >=
                abs(p->bonecas[p->topo - 1]->dado)) {
                    generalizada = 0;
            } else {
                p->bonecas[p->topo - 1]->soma_do_nivel += abs(dado);
                empilha(p, dado);
            }
            
        } else if (dado > 0) {
            /* Sendo o tamanho positivo, se seu valor for igual ao valor
             * absoluto do tamanho do ultimo elemento da pilha, retira o
             * ultimo elemento; do contrario, nao pode ser uma Matrioshka 
             * Generalizada, pois sobrariam elementos na pilha */
            if (dado == abs(p->bonecas[p->topo - 1]->dado)) {
                desempilha(p);
            } else {
                generalizada = 0;
            }
            
        }
        
    }
    
    /* Se for generalizada, ou seja nao desemparelhou, e o topo da pilha
     * for igual a zero, e Matrioshka Generalizada; do contrario, nao e */
    if ((generalizada) && (p->topo == 0)) {
        printf(" Matrioshka!\n");
    } else {
        printf(" Tente novamente.\n");
    }
    
    /* Libera a memoria alocada para a pilha: comecando com as
     * Matrioshkas que restaram, se restou alguma; depois com
     * o vetor de ponteiros; e depois com a propria pilha */
    while ((p->bonecas[p->topo] != NULL) && (p->topo > 0)) {
        desempilha(p);
    }
    free(p->bonecas);
    free(p);
}
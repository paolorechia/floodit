#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"


tno * aloca_raiz(tmapa * m){
    tno * no;
    no = malloc(sizeof(tno));
    no->pai = NULL;
    no->filhos = NULL;
    no->cor = 0;
    no->m = aloca_mapa(m);
    copia_mapa(m, no->m);
    return no;
}

tno * aloca_filho(tno * no_pai){
    tno * filho;
    filho = malloc(sizeof(tno));
    filho->pai = no_pai;
    filho->filhos = NULL;
    filho->cor = 0;
    filho->m = aloca_mapa(no_pai->m);
    return filho;
}

void aloca_k_filhos(tno * no_atual, int k){
    no_atual->filhos = malloc(sizeof(tno *) * k);
    no_atual->nfilhos = k;
    for (int i = 0; i < k; i++){
        no_atual->filhos[i] = aloca_filho(no_atual);
    }
}

void expande_no(tno * no){
    int * vetor_cores;
    int i, j, cor, ncores;

    tfronteira *f;
    tmapa * m = no->m;
    f = aloca_fronteira(m);
//    printf("%d\n", m->ncores);
    vetor_cores= (int*) malloc((m->ncores + 1) * sizeof(int));

    for (i = 0; i < m->ncores; i++){
        vetor_cores[i] = 0;
    }
    fronteira_mapa(m, f);
    for (i = 0; i < f->tamanho; i++){
        cor = m->mapa[f->pos[i].l][f->pos[i].c];
//        printf(" %d ", cor);
        vetor_cores[cor-1]=1;
    }
//    printf("\n");
    ncores = 0;
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            ncores++;
//            printf("%d ", cor);
        }
    }
    int * opcoes = malloc(sizeof(int) * ncores);
    j = 0;
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            opcoes[j]=cor+1; 
        }
    }
    printf("Ncores: %d\n", ncores);

    aloca_k_filhos(no, ncores);
    for (i = 0; i < ncores; i++){
        copia_mapa(m, no->filhos[i]->m);
        pinta_mapa(no->filhos[i]->m, opcoes[i]);
/*
        tmapa * tmp_map;
        tmp_map = aloca_mapa(m);
        copia_mapa(m, tmp_map);
        pinta_mapa(tmp_map, opcoes[i]);
        printf("f: %d\n", heuristica_1(tmp_map));
//        libera_mapa(tmp_map);
*/
    }
    printf("\n");
    libera_fronteira(f);
    free(vetor_cores);
/*
*/
    return 0;
}

void desaloca_raiz(tno * no){
    free(no);
}

int main(int argc, char **argv) {
    // vars
    tmapa m;
    tno * arvore;


    // mallocs
    carrega_mapa(&m);
    arvore = aloca_raiz(&m);


    /* Busca gulosa */
    int distancia = 999999;
    int i;
    int j = 0;
    int limite = 1;
    tno * minimo = arvore;
    int min = heuristica_1(arvore->m);
    while (distancia > 0){
        tno * aux = minimo;
        mostra_mapa_cor(aux->m);
        expande_no(aux);
        distancia = heuristica_1(aux->m);
        for (i = 0; i < aux->nfilhos; i++){
            int res = heuristica_1(aux->filhos[i]->m);
            printf("f: %d\n", res);
            if (res <= min){
                min = res;
                minimo = aux->filhos[i];
                mostra_mapa_cor(aux->filhos[i]->m);
            }
        }
        j++;
    }
    printf("Usamos %d passos\n", j);
    // Conta quantas cores falta para solucionar o floodit
//    printf("%d\n", heuristica_1(&m));

    // frees
    desaloca_raiz(arvore);
    libera_mapa2(&m);


    return 0;
}

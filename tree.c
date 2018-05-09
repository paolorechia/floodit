#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"


tno * aloca_raiz(tmapa * m){
    tno * no;
    no = malloc(sizeof(tno));
    no->pai = NULL;
    no->filhos = NULL;
    no->cor = -1;
    no->passos = 0;
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
    filho->passos = no_pai->passos + 1;
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

    tmapa *m =  no->m;
    int * vetor_cores = malloc(sizeof(int) * no->m->ncores);
    obtem_cores(no->m, &vetor_cores);
    int ncores = 0;
    int i, j, cor;
    j = 0;
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            ncores++;
        }
    }
    int * opcoes = malloc(sizeof(int) * ncores);
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            opcoes[j]=cor+1; 
            j++;
        }
    }
    aloca_k_filhos(no, ncores);
    for (i = 0; i < ncores; i++){
        copia_mapa(m, no->filhos[i]->m);
        pinta_mapa(no->filhos[i]->m, opcoes[i]);
        no->filhos[i]->cor = opcoes[i];
    }
    free(vetor_cores);
    free(opcoes);
    return;
}

int * devolve_solucao(tno * no){
    int tam = no->passos + 1;
    int * tmp = malloc(sizeof(int) * tam);
    tno * aux = no;
    int i =0;
    tmp[i]=aux->cor;
    i++;
    while(aux->pai!= NULL){
        tmp[i]=aux->cor;
        aux = aux->pai;
        i++;
    }
    int * solucao = malloc(sizeof(int) * tam);
    int j = 0;
    int k = 0;
    for (k = tam-1; k > 0; k--){
        solucao[j]=tmp[k];
        j++;
    }
//    printf("Cor:%d passos:%d\n", aux->cor, aux->passos);
    return solucao;
}


void desaloca_no(tno * no){
    if (no == NULL) return;
    if (no->filhos != NULL){
        for (int i = 0; i < no->nfilhos; i++){
            free(no->filhos[i]);
        }
//        free(no->filhos);
//        no->filhos = NULL;
    }
    libera_mapa(no->m);
    free(no);
}

void desaloca_arvore(tno * no){
    tno * aux = NULL;
    for (int i = 0; i < no->nfilhos; i++){
        aux = no->filhos[i];
        if (aux != NULL){
            desaloca_arvore(aux);
        }
    }
    if (aux){
        desaloca_no(aux);
    }
}

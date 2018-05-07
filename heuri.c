#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"
#include "heuri.h"

// Conta quantas cores falta para solucionar o floodit
int heuristica_1(tmapa * m){
    int tam_vetor = m->ncores + 1;
    int * vetor_cores = (int*) malloc((tam_vetor) * sizeof(int));
    int i, j;
    for (i = 0; i < tam_vetor; i++){
        vetor_cores[i]=0;
    } 
    for (i = 0; i < m->nlinhas; i++){
        for (j = 0; j < m->ncolunas; j++){
            vetor_cores[m->mapa[i][j]]=1; 
        }
    }
    int qtde_cores = 0;
    for (i = 0; i < tam_vetor; i++){
        if (vetor_cores[i] != 0){
            qtde_cores++;
        }
    } 
    free(vetor_cores);
    return qtde_cores - 1;
}


/*
int main(int argc, char **argv) {
  tmapa m;

  carrega_mapa(&m);
  printf("%d\n", heuristica_1(&m));
  return 0;
}
*/
  

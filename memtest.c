#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"

static tmapa * carrega_mapa2() {
  int i, j;
  tmapa * m = malloc(sizeof(tmapa));
  scanf("%d", &(m->nlinhas));
  scanf("%d", &(m->ncolunas));
  scanf("%d", &(m->ncores));
  m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));
  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
    for(j = 0; j < m->ncolunas; j++)
      scanf("%d", &(m->mapa[i][j]));
  }
  return m;
}

static void desaloca_no2(tno * no){
    libera_mapa(no->m);
    free(no);
}

static void desaloca_arvore2(tno * no){
    for (int i = 0; i < no->nfilhos; i++){
        desaloca_arvore2(no->filhos[i]);
    }
    desaloca_no2(no);
}

int main(int argc, char **argv) {
    tno * arvore;

    // mallocs
    tmapa * m = carrega_mapa2();
    tmapa *aux = aloca_mapa(m);

    arvore = aloca_raiz(m);
    expande_no(arvore);


    desaloca_arvore2(arvore);
    // frees
    libera_mapa(m);
    libera_mapa(aux);
    return 0;
}

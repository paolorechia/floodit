#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"


int aloca_raiz(tno * no, tmapa * m){
    no = (tno*) malloc(sizeof(tno *));
    no->pai = NULL;
    no->cor = 0;
    no->m = m;
    return 0;
}

int expande_no(tno * no){

}

int desaloca_raiz(tno * no){
    free(no);
}


// Conta quantas cores falta para solucionar o floodit

int main(int argc, char **argv) {
    // vars
    tmapa m;
    tfronteira *f;
    tno * arvore;

    // mallocs
    f = aloca_fronteira(&m);
    aloca_raiz(arvore, &m);
    carrega_mapa(&m);

    // funcs
    fronteira_mapa(&m, f);
    printf("%d\n", heuristica_1(&m));

    // frees
    libera_fronteira(f);
    desaloca_raiz(arvore);
    libera_mapa2(&m);


    return 0;
}
  

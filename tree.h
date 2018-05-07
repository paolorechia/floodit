#ifndef __TREE_H__
#define __TREE_H__ 
#include "mapa.h"
#include "heuri.h"

// Define uma arvore para registrar o caminho percorrido

typedef struct no_struct{
    tmapa * m;
    struct no_struct * pai;
    struct no_struct ** filhos;
    int nfilhos;
    int cor;
    int passos;
} tno;

tno * aloca_raiz(tmapa * m);
tno * aloca_filho(tno * no_pai);
void aloca_k_filhos(tno * no_atual, int k);
void expande_no(tno * no);
void desaloca_no(tno * no);
void desaloca_arvore(tno * no);
int * devolve_solucao(tno * no);

#endif

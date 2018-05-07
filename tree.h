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
} tno;

tno * aloca_raiz(tmapa * m);
void expande_no(tno * no);
void desaloca_raiz(tno * no);


#endif

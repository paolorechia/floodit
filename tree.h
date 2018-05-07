#ifndef __TREE_H__
#define __TREE_H__ 
#include "mapa.h"
#include "heuri.h"

// Define uma arvore para registrar o caminho percorrido

typedef struct no_struct{
    tmapa * m;
    struct no_struct * pai;
    struct no_struct ** filhos;
    int cor;
} tno;

tno * aloca_raiz(tmapa * m);
int expande_no(tno * no);
void desaloca_raiz(tno * no);


#endif

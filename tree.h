#ifndef __TREE_H__
#define __TREE_H__ 
#include "mapa.h"
#include "heuri.h"

// Define uma arvore para registrar o caminho percorrido

typedef struct {
    tmapa * m;
    void * pai;
    int cor;
} tno;

int aloca_raiz(tno * no, tmapa * m);
int expande_no(tno * no);
int desaloca_raiz(tno * no);


#endif


#ifndef __HEURISTICAS_H__
#define __HEURISTICAS_H__ 

#include "mapa.h"

typedef int (*tipo_funcao)(tmapa *m);
tipo_funcao escolhe_heuristica(int numero);
int heuristica_1(tmapa * m);
int heuristica_2(tmapa * m);
int heuristica_3(tmapa * m);


#endif

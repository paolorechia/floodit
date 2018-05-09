
#ifndef __HEURISTICAS_H__
#define __HEURISTICAS_H__ 

#include "mapa.h"

void obtem_opcoes(tmapa *m, int ** vet_cor);
void obtem_cores(tmapa *m, int ** vet_cor);
typedef int (*tipo_funcao)(tmapa *m);
tipo_funcao escolhe_heuristica(int numero);
int heuristica_1(tmapa * m);
int heuristica_2(tmapa * m);
int heuristica_3(tmapa * m);
int heuristica_4(tmapa * m);


#endif

#include "tree.h"
#ifndef __HEAP_H__
#define __HEAP_H__ 

typedef struct{
    int chave;
    tno * ponteiro;
} tcelula_h;

typedef struct{
    int tam;
    int usado;
    tcelula_h * vetor;
} theap;

int aloca_h(theap ** heap, int cap);
int desaloca_h(theap * heap);

int pai_h(int i);
int esq_h(int i);
int dir_h(int i);

int min_heapify(theap * heap, int i);
int constroi_min_heap(theap * heap);

/* Funcoes para implementar a fila de prioridade */
int min_h(theap * heap);
tcelula_h * pega_min_h(theap * heap);
int insere_h(theap * heap, int chave, tno* p_dado);
int aumenta_chave_h(theap * heap, int i, int nova_chave);
#endif

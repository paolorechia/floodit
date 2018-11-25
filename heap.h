#ifndef __HEAP_H__
#define __HEAP_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"

typedef struct{
    int chave;
    tmapa * ponteiro;
} tcelula_h;

typedef struct{
    int tam;
    int usado;
    tcelula_h * vetor;
} theap;

theap * aloca_h(int cap);
int desaloca_h(theap * heap);

int pai_h(int i);
int esq_h(int i);
int dir_h(int i);

int min_heapify(theap * heap, int i);
int constroi_min_heap(theap * heap);

/* Funcoes para implementar a fila de prioridade */
int min_h(theap * heap);
tcelula_h * pega_min_h(theap * heap);
int insere_h(theap * heap, int chave, tmapa * mapa);
int aumenta_chave_h(theap * heap, int i, int nova_chave);
#endif

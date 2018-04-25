#ifndef __HEAP_H__
#define __HEAP_H__ 

typedef struct{
    int chave;
    int * ponteiro;
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

#endif

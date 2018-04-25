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
int left_h(int i);
int right_h(int i);
#endif

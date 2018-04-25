#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int aloca_h(theap ** heap, int cap){
    *heap = malloc(sizeof(theap));
    (*heap)->tam = cap;   
    (*heap)->vetor = malloc((*heap)->tam * sizeof(tcelula_h));
    (*heap)->usado = 0;
    return 0;
}

int desaloca_h(theap * heap){
    free(heap->vetor);
    free(heap);
    return 0;
}

int pai_h(int i)   { return i/2;     }
int esq_h(int i)  { return 2*i;     }
int dir_h(int i) { return 2*i + 1; }


// implementacao das funcoes de Heap do cormen
int min_heapify(theap * heap, int i){
    int esq = esq_h(i);
    int dir = dir_h(i);
    int menor;
    tcelula_h * V = heap->vetor;
    if (esq <= heap->tam && V[esq].chave < V[i].chave)
        menor = esq;
    else menor = i;
    if (dir <= heap->tam && V[dir].chave < V[menor].chave)
        menor = dir;
    if (menor != i) {
        int aux = V[i].chave;
        V[i].chave = V[menor].chave;
        V[i].chave = aux;
        min_heapify(heap, menor);
    }
    return 0;
}

int constroi_min_heap(theap * heap){
    int n = heap->tam/2;
    for (int i = n; i > -1; i--){
        min_heapify(heap, i);
    } 
}







int main(){
    int heap_size = 1000; // in bytes
    theap * heaptest;
    aloca_h(&heaptest, heap_size);
    for (int i = 0; i < heap_size; i++){
        heaptest->vetor[i].chave = 1000 - i;
    }
    min_heapify(heaptest, heap_size);
    constroi_min_heap(heaptest);
    for (int i = 0; i < 100; i++){
        printf("%d ", heaptest->vetor[i].chave);
    }
    printf("\n");
    desaloca_h(heaptest);
}

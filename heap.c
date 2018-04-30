#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"


int aloca_h(theap ** heap, int cap){
    *heap = malloc(sizeof(theap));
    (*heap)->tam = cap;   
    (*heap)->vetor = malloc((*heap)->tam * sizeof(tcelula_h));
    (*heap)->usado = 0;
    for (int i = 0; i < cap; i++){
        (*heap)->vetor[i].chave = 0;
    }
    return 0;
}

int desaloca_h(theap * heap){
    free(heap->vetor);
    free(heap);
    return 0;
}

int troca_h(tcelula_h * elem1, tcelula_h * elem2){
    int aux = (*elem1).chave;
    int * p_aux = (*elem1).ponteiro;
    (*elem1).chave = (*elem2).chave;
    (*elem1).ponteiro = (*elem2).ponteiro;
    (*elem2).chave = aux;
    (*elem2).ponteiro = p_aux;
    return 0;
}

int pai_h(int i)   { return i/2 - 1; }
int esq_h(int i)   { return 2*i + 1; }
int dir_h(int i)   { return 2*i + 2; }


// implementacao das funcoes de Heap do cormen
int min_heapify(theap * heap, int i){
    int esq = esq_h(i);
    int dir = dir_h(i);
    int menor;
    tcelula_h * V = heap->vetor;
    if (esq < heap->usado && V[esq].chave < V[i].chave)
        menor = esq;
    else menor = i;
    if (dir < heap->usado && V[dir].chave < V[menor].chave)
        menor = dir;
    if (menor != i) {
        troca_h(&V[i], &V[menor]);
        min_heapify(heap, menor);
    }
    return 0;
}

int constroi_min_heap(theap * heap){
    int n = (heap->usado/2);
    for (int i = n; i > -1; i--){
        min_heapify(heap, i);
    } 
    return 0;
}

int min_h(theap * heap){
    return heap->vetor[0].chave;
}
tcelula_h * pega_min_h(theap * heap){
    if (heap->usado < 1){
        return NULL;
    } 
    tcelula_h * minimo = malloc(sizeof(tcelula_h));
    minimo->chave = heap->vetor[0].chave;
    minimo->ponteiro = heap->vetor[0].ponteiro;
    troca_h(&(heap->vetor[0]), &(heap->vetor[heap->usado]));
    heap->usado--;
//    tcelula_h * minimo = &(heap->vetor[heap->usado]);
    min_heapify(heap, 0);
    return minimo;
}
int diminui_chave_h(theap * heap, int i, int nova_chave){
    tcelula_h * V = heap->vetor;
    if (nova_chave > V[i].chave){
        printf("Erro\n"); // nova chave ja eh maior
    }
    V[i].chave = nova_chave;
    while (i > 1 && V[pai_h(i)].chave > V[i].chave){
        troca_h(&(V[i]), &(V[pai_h(i)]));
        i = pai_h(i); 
    }
    return 0;
}
int insere_h(theap * heap, int chave, int * p_dado){
    if (heap->usado >= heap->tam - 1){
        return - 1; // heap cheia, impossivel inserir
    }
    else{
        heap->usado++;
        heap->vetor[heap->usado].chave = INT_MAX;
        heap->vetor[heap->usado].ponteiro = p_dado;
        diminui_chave_h(heap, heap->usado, chave);
        return 0;
    }
}

int main(){
    long unsigned int kb = 1024;
    long unsigned int mb = 1024 * kb;
    long unsigned int gb = 1024 * mb;
    
    long unsigned int max_memory = 4 * gb;

    int data_cell_size = 1024; // bytes
    printf("Tipo heap custa: %lu\n", sizeof(theap));
    printf("Tipo celula custa: %lu\n", sizeof(tcelula_h));
    printf("\n");

    printf("Available memory: %lu bytes\n", max_memory);
    long unsigned int max_heap_size = (max_memory - sizeof(theap))/(sizeof(tcelula_h) + data_cell_size);
    printf("Max size of heap: %ld cells\n", max_heap_size);

    int items_usados = 10;
    int * a = malloc(sizeof(int));
    int * b = malloc(sizeof(int));
    (*a) = 2;
    (*b) = 5;
    theap * heaptest;
//    aloca_h(&heaptest, kb);
    aloca_h(&heaptest, max_heap_size);
    char * MSG1="Inserindo items na heap";
    char * MSG2="Construindo min-heap";
    char * MSG3="Extraindo minimos da heap";
    char * MSG4="Heap construida por insercao";

    printf("%s\n", MSG1);
    for (int i = 0; i < items_usados; i++){
        printf("%d ", items_usados - i);
        insere_h(heaptest, items_usados - i, a);
    }
    printf("\n");
    
    printf("%s\n", MSG4);
    for (int i = 0; i < heaptest->usado; i++){
        printf("%d ", heaptest->vetor[i].chave);
    }
    printf("\n");

/*
    printf("%s\n", MSG2);
    constroi_min_heap(heaptest);
    for (int i = 0; i < heaptest->usado; i++){
        printf("%d ", heaptest->vetor[i].chave);
    }
    printf("\n");
*/
    printf("%s\n", MSG3);
    int heap_use_size = heaptest->usado;
    for (int i = 0; i < heap_use_size; i++){
        tcelula_h * teste =  pega_min_h(heaptest);
        if (teste != NULL){
            printf("%d ", teste->chave);
        }
    }
    printf("\n");

    printf("%s\n", MSG1);
    for (int i = 0; i < items_usados; i++){
        insere_h(heaptest, items_usados - i, a);
    }

    printf("%s\n", MSG2);
    constroi_min_heap(heaptest);
    for (int i = 0; i < heaptest->usado; i++){
        printf("%d ", heaptest->vetor[i].chave);
    }
    printf("\n");



    desaloca_h(heaptest);
    free(a);
    free(b);
    return 0;
}

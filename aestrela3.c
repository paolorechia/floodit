#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"
#include "heap.h"

int main(int argc, char **argv) {
    // vars
    tmapa m;
    tno * arvore;

    // mallocs
    carrega_mapa(&m);
    arvore = aloca_raiz(&m);

    unsigned long int kb = 1024;
    unsigned long int mb = 1024 * kb;
    unsigned long int gb = 1024 * mb;

    unsigned long int tam_mapa =sizeof(char) * m.ncolunas * m.nlinhas;
    // aproximacao grosseira para fator medio de ramificacao
//    unsigned long int fator_r= m.ncolunas;     
    unsigned long int tam_no = sizeof(tno) + tam_mapa * 4;
    unsigned long int numero_nos = 0;
    unsigned long int restricao_memoria = 2 * gb;
    unsigned long int maximo_nos = restricao_memoria / tam_no;
//    unsigned long int memoria_usada = numero_nos * tam_no;


   //  printf("tam_mapa %lu\n",tam_mapa);
   // aproximacao grosseira para fator medio de ramificacao
   //  printf("fator_r: %lu\n", fator_r);
   //  printf("tam_no: %lu\n", tam_no);
   //  printf("numero_nos: %lu\n", numero_nos);
    printf("restricao_memoria: %lu\n", restricao_memoria);
    // printf("memoria_usada: %lu\n", memoria_usada);
    printf("maximo_nos: %lu\n", maximo_nos);
    
    /* Busca aestrela */
    srand(time(NULL));
    int distancia = 999999;
    int i;

    // h eh ponteiro de funcao
    numero_nos = 1;
    
    tno * minimo = arvore;
    theap * heap;
    aloca_h(&heap, maximo_nos);

    tno * aux = minimo;

    int f;
    int (*h)(tmapa *m);
    int (*h3)(tmapa *m);
    int (*h4)(tmapa *m);

    h3 = escolhe_heuristica(3);
    h4 = escolhe_heuristica(4);

    h = h3;
    f = (*h)(minimo->m);
    while (f != 0){
        expande_no(minimo);
        /* Teste memoria */
        numero_nos += minimo->nfilhos;
//        memoria_usada = numero_nos * tam_no;
//            printf("numero_nos: %lu/%lu\n", numero_nos, maximo_nos);
//            printf("memoria_usada: %lu/%lu\n", memoria_usada, restricao_memoria);
        if (numero_nos > maximo_nos){
            printf("PANICK: Maximum safe memory use exceeded. Aborting\n");
            desaloca_arvore(arvore);
            return -1;
        }
        for (i = 0; i < minimo->nfilhos; i++){
            aux = minimo->filhos[i];
            f = (*h)(aux->m);
            distancia = aux->passos + f;
            insere_h(heap, distancia, aux);
        }
        tcelula_h * teste = pega_min_h(heap); 
        minimo = teste->ponteiro;            
        f = (*h)(minimo->m);
    }
    int passos_sol1 = minimo->passos;
    int * solucao = devolve_solucao(minimo);
    tmapa * m2 = aloca_mapa(&m);
    copia_mapa(minimo->m, m2);
    desaloca_h(heap);
    desaloca_arvore(arvore);

//    mostra_mapa(m2);
    arvore = aloca_raiz(m2);
    minimo = arvore;
    aloca_h(&heap, maximo_nos);

    h = h4;
    f = (*h)(minimo->m);
    while (f != 0){
        expande_no(minimo);
        /* Teste memoria */
        numero_nos += minimo->nfilhos;
//        memoria_usada = numero_nos * tam_no;
//            printf("numero_nos: %lu/%lu\n", numero_nos, maximo_nos);
//            printf("memoria_usada: %lu/%lu\n", memoria_usada, restricao_memoria);
        if (numero_nos > maximo_nos){
            printf("PANICK: Maximum safe memory use exceeded. Aborting\n");
            desaloca_arvore(arvore);
            return -1;
        }
        for (i = 0; i < minimo->nfilhos; i++){
            aux = minimo->filhos[i];
            f = (*h)(aux->m);
            distancia = aux->passos + f;
            insere_h(heap, distancia, aux);
        }
        tcelula_h * teste = pega_min_h(heap); 
        minimo = teste->ponteiro;            
        f = (*h)(minimo->m);
    }
    printf("%d\n", passos_sol1 + minimo->passos);
    int * solucao2 = devolve_solucao(minimo);
    for (i = 0; i < passos_sol1 ; i++){
        printf("%d ", solucao[i]);
    }
    for (i = 0; i < minimo->passos; i++){
        printf("%d ", solucao2[i]);
    }
    printf("\n");


    // frees
    free(solucao);
    free(solucao2);
    desaloca_h(heap);
    desaloca_arvore(arvore);

    return 0;
}

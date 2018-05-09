#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"
#include "heap.h"

int main(int argc, char **argv) {
    int numero_heuristica = -1;
    int (*h)(tmapa *m);
    if (argc < 2){
        printf("Uso: %s [numero_heuristica] < instancia_redirecionada.txt\n", argv[0]);
    }
    else{
        numero_heuristica = atoi(argv[1]);
        // h eh ponteiro de funcao
    }
    h = escolhe_heuristica(numero_heuristica);
    if (h == NULL){
        printf("Heuristica invalida\n");
        return -1;
    }
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
    unsigned long int fator_r= m.ncolunas;     
    unsigned long int tam_no = sizeof(tno) + tam_mapa * 4;
    unsigned long int numero_nos = 0;
    unsigned long int restricao_memoria = 2 * gb;
    unsigned long int maximo_nos = restricao_memoria / tam_no;
    unsigned long int memoria_usada = numero_nos * tam_no;


    printf("tam_mapa %lu\n",tam_mapa);
    // aproximacao grosseira para fator medio de ramificacao
    printf("fator_r: %lu\n", fator_r);
    printf("tam_no: %lu\n", tam_no);
    printf("numero_nos: %lu\n", numero_nos);
    printf("restricao_memoria: %lu\n", restricao_memoria);
    printf("memoria_usada: %lu\n", memoria_usada);
    printf("maximo_nos: %lu\n", maximo_nos);
    
    /* Busca aestrela */
    srand(time(NULL));
    int distancia = 999999;
    int i;
    int j = 0;
    int limite = 1;
    tno * minimo = arvore;

    // h eh ponteiro de funcao
    numero_nos = 1;
    
    theap * heap;
    aloca_h(&heap, maximo_nos);

    tno * aux = minimo;

    int f = (*h)(minimo->m);
    while (f != 0){
        expande_no(minimo);
        /* Teste memoria */
        numero_nos += minimo->nfilhos;
        memoria_usada = numero_nos * tam_no;
        printf("numero_nos: %lu/%lu\n", numero_nos, maximo_nos);
        printf("memoria_usada: %lu/%lu\n", memoria_usada, restricao_memoria);
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
    printf("%d\n", minimo->passos);
    int * solucao = devolve_solucao(minimo);
    for (i = 0; i < minimo->passos; i++){
        printf("%d ", solucao[i]);
    }
    printf("\n");

    // frees
    free(solucao);
    desaloca_h(heap);
//    desaloca_arvore(arvore);

    return 0;
}

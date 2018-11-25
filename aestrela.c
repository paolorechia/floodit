#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "hashtable.h"
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
    // map loading
    tmapa m;
    carrega_mapa(&m);

    unsigned long int kb = 1024;
    unsigned long int mb = 1024 * kb;
    unsigned long int gb = 1024 * mb;

    unsigned long int tam_mapa =sizeof(char) * m.ncolunas * m.nlinhas;
    // aproximacao grosseira para fator medio de ramificacao
    unsigned long int fator_r= m.ncolunas;     
    unsigned long int tam_no = sizeof(tmapa) + tam_mapa * 6;
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

    // vars
    tmapa * estado_atual;
    tfronteira * front;
    thashtable * hashtable;
    theap * heap;

    // mallocs and inits
    estado_atual = aloca_mapa(&m);
    copia_mapa(estado_atual, &m);

    front = aloca_fronteira(&m);
    fronteira_mapa(&m, front);

    int * vetor_cores = (int*) malloc((m.ncores) * sizeof(int));

    hashtable = h_init(maximo_nos);
    aloca_h(&heap, maximo_nos);

    /* Busca aestrela */
    srand(time(NULL));
    int distancia = 999999;

    tmapa * aux;

    int f = (*h)(estado_atual);
    while (f != 0){
        // pegar fronteira de cores
        obtem_cores(estado_atual, vetor_cores);
        // para cada cor da fronteira, gerar novo mapa e tentar inserir na tabela_hash
        for (int cor = 0; cor < estado_atual->ncores; ++cor){
          if (vetor_cores[cor]){
            aux = aloca_mapa(estado_atual);
            copia_mapa(aux, estado_atual); 
            pinta_mapa(aux, cor);
            if (h_insert(hashtable, aux)){
              aux->passos++;
              aux->sol[aux->passos]=cor;
              f = (*h)(aux); 
              distancia = aux->passos + f;
              insere_h(heap, distancia, aux);
            }
            // state already exists, free map
            else{
            libera_mapa(aux);
            }
          }
        }
        tcelula_h * elem_heap = pega_min_h(heap); 
        estado_atual = elem_heap->ponteiro;            
        free(elem_heap);
        f = (*h)(estado_atual);
    }
    printf("%d\n", estado_atual->passos);
    for (int i = 0; i < estado_atual->passos; i++){
      printf("%d ", estado_atual->sol[i]);
    }
    printf("\n");

    // frees
    libera_fronteira(front);
    free(vetor_cores);
    h_free(hashtable);
    desaloca_h(heap);
    return 0;
}

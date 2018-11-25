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
    tmapa * mapa_inicial = carrega_mapa();
    mostra_mapa(mapa_inicial);

    unsigned long int kb = 1024;
    unsigned long int mb = 1024 * kb;
    unsigned long int gb = 1024 * mb;

    unsigned long int tam_mapa =sizeof(char) * mapa_inicial->ncolunas * mapa_inicial->nlinhas;
    // aproximacao grosseira para fator medio de ramificacao
    unsigned long int fator_r= mapa_inicial->ncolunas;     
    unsigned long int tam_no = sizeof(tmapa) + tam_mapa * 6;
    unsigned long int numero_nos = 0;
    unsigned long int restricao_memoria = 1 * mb;
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
    theap * saved_elements;

    // mallocs and inits
    estado_atual = aloca_mapa(mapa_inicial);
    copia_mapa(mapa_inicial, estado_atual);

    front = aloca_fronteira(mapa_inicial);
    fronteira_mapa(mapa_inicial, front);

    int * vetor_cores = (int*) malloc((mapa_inicial->ncores) * sizeof(int));

    hashtable = h_init(maximo_nos);
    aloca_h(&heap, maximo_nos);

    int lim_inf = maximo_nos/2;
    aloca_h(&saved_elements, lim_inf + 1);

    libera_mapa(mapa_inicial);
    /* Busca aestrela */
    srand(time(NULL));
    int distancia = 999999;
    int removed = 0;

    tmapa * aux;

    int f = (*h)(estado_atual);
    while (f != 0){
        // pegar fronteira de cores
        obtem_cores(estado_atual, vetor_cores);
        // para cada cor da fronteira, gerar novo mapa e tentar inserir na tabela_hash
        for (int cor = 0; cor < estado_atual->ncores; ++cor){
          if (vetor_cores[cor]){
            aux = aloca_mapa(estado_atual);
            copia_mapa(estado_atual, aux);
            pinta_mapa(aux, cor+1);
//            mostra_mapa(aux);
            if (h_insert(hashtable, aux)){
              aux->sol[aux->passos]=(cor+1);
              aux->passos++;
              f = (*h)(aux); 
              distancia = aux->passos + f;
              insere_h(heap, distancia, aux);
              numero_nos++;
            } else{
            libera_mapa(aux);
            }
          }
        }
        if (heap->usado >= maximo_nos){
//          printf("Estouramos a memoria!\n");          
          while(heap->usado > lim_inf){
            tcelula_h * elem_heap = pega_min_h(heap); 
            insere_h(saved_elements, elem_heap->chave, elem_heap->ponteiro);
            free(elem_heap);
          }
          // Discard remainder
          tcelula_h * elem_heap = pega_min_h(heap); 
          while(elem_heap != NULL){
            if(h_removestate(hashtable, elem_heap->ponteiro)){
              removed++;
            }
            free(elem_heap); 
            elem_heap = pega_min_h(heap); 
          }
          elem_heap = pega_min_h(saved_elements);
          while(elem_heap != NULL){
            insere_h(heap, elem_heap->chave, elem_heap->ponteiro);
            free(elem_heap);
            elem_heap = pega_min_h(saved_elements);
          }
        }
//        printf("numero_nos: %lu\n", heap->usado);
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
    desaloca_h(saved_elements);
    return 0;
}

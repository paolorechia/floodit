#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"


int main(int argc, char **argv) {
    int numero_heuristica = -1;
    int (*h)(tmapa *m);
    if (argc < 2){
        printf("Uso: ./%s [numero_heuristica]\n", argv[0]);
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

    // define vars
    srand(time(NULL));
    int distancia = 999999;
    int menor_indice, min_distancia;
    int j = 0;
    int * vetor_dist;
    int * vetor_cores;
    tmapa m;
    tmapa * tmp;
    tplano *p;

    // Le mapa
    carrega_mapa(&m);
    tmp = aloca_mapa(&m);

    p = aloca_plano(&m);
    distancia = (*h)(&m);

    /* Busca gulosa */
    vetor_dist = malloc(sizeof(int) * m.ncores + 1);
    vetor_cores = malloc(sizeof(int) * m.ncores + 1);
    while (distancia > 0){
        obtem_cores(&m, &vetor_cores);
        for (int i = 0; i < m.ncores; i++){
            if (vetor_cores[i] == 1){
                copia_mapa(&m, tmp);
                pinta_mapa(tmp, i + 1);
                vetor_dist[i] = (*h)(tmp);
            }
            else{
                vetor_dist[i] = -1;
            }
        }
        min_distancia = 999999;
        menor_indice = 0;
        for (int k = 0; k < m.ncores; k++){
            if (vetor_dist[k] >= 0 && vetor_dist[k] <= min_distancia){
                min_distancia = vetor_dist[k];
                menor_indice = k;
            }
        }
        pinta_mapa(&m, menor_indice + 1);
        insere_plano(p, menor_indice + 1);
        distancia = (*h)(&m);
        j++;
    }
    mostra_plano(p);
    libera_plano(p);
    libera_mapa(tmp);
//    libera_mapa(&m);
    return 0;
}

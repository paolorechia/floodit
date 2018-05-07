#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mapa.h"
#include "heuri.h"
#include "tree.h"

int main(int argc, char **argv) {
    // vars
    tmapa m;
    tno * arvore;


    // mallocs
    carrega_mapa(&m);
    arvore = aloca_raiz(&m);


    /* Busca gulosa, aleatoria */
    srand(time(NULL));
    int distancia = 999999;
    int i;
    int j = 0;
    int limite = 1;
    tno * minimo = arvore;
    int min = heuristica_1(arvore->m);
    while (distancia > 0){
        tno * aux = minimo;
//        mostra_mapa_cor(aux->m);
        expande_no(aux);
        distancia = heuristica_1(aux->m);
        for (i = 0; i < aux->nfilhos; i++){
            int res = heuristica_1(aux->filhos[i]->m);
//            printf("f: %d\n", res);
            if (res < min){
                min = res;
                minimo = aux->filhos[i];
//                mostra_mapa_cor(aux->filhos[i]->m);
            }
        }
        // Nao encontramos melhor opcao, usar numero aleatorio
        if (aux == minimo && distancia > 0){
            minimo = aux->filhos[rand() % aux->nfilhos];
        }
        j++;
        printf("Escolhemos a cor: %d\n", minimo->cor);
    }
    printf("Usamos %d passos\n", minimo->passos);
    int * solucao = devolve_solucao(minimo);
    for (i = 0; i < minimo->passos; i++){
        printf("%d ", solucao[i]);
    }
    printf("\n");
    // Conta quantas cores falta para solucionar o floodit
//    printf("%d\n", heuristica_1(&m));

    // frees
    free(solucao);
    desaloca_arvore(arvore);
    libera_mapa2(&m);
    return 0;
}

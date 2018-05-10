#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"
#include "heuri.h"
#include "list.h"

// funcao auxiliar
void obtem_cores(tmapa * m, int ** vet_cor){
    tfronteira *f;
    int i, cor;
    int * vetor_cores = (*vet_cor);

    f = aloca_fronteira(m);
    fronteira_mapa(m, f);

    for (i = 0; i < m->ncores; i++){
        vetor_cores[i] = 0;
    }
    for (i = 0; i < f->tamanho; i++){
        cor = m->mapa[f->pos[i].l][f->pos[i].c];
        vetor_cores[cor-1]=1;
    }
    libera_fronteira(f);
}

// Conta quantas cores falta para solucionar o floodit
int heuristica_1(tmapa * m){
    int tam_vetor = m->ncores + 1;
    int * vetor_cores = (int*) malloc((tam_vetor) * sizeof(int));
    int i, j;
    for (i = 0; i < tam_vetor; i++){
        vetor_cores[i]=0;
    } 
    for (i = 0; i < m->nlinhas; i++){
        for (j = 0; j < m->ncolunas; j++){
            vetor_cores[m->mapa[i][j]]=1; 
        }
    }
    int qtde_cores = 0;
    for (i = 0; i < tam_vetor; i++){
        if (vetor_cores[i] != 0){
            qtde_cores++;
        }
    } 
    free(vetor_cores);
    return qtde_cores - 1;
}

// Conta quantas celulas falta para solucionar o floodit
int heuristica_2(tmapa * m){
    int count = 0;
    int cor_atual = m->mapa[0][0];
    for (int i =0; i < m->nlinhas;i++){
        for (int j = 0; j < m->ncolunas;j++){
            if (m->mapa[i][j] != cor_atual){
                count++; 
            }
        }
    } 
    printf("%d\n", count);
    return count;
}

static void fronteira2(tmapa *m, int l, int c, int fundo, tfronteira *f) {
  if(m->mapa[l][c] == fundo) {
    m->mapa[l][c] *= -1;
    if(l < m->nlinhas - 1)
      fronteira2(m, l+1, c, fundo, f);
    if(c < m->ncolunas - 1)
      fronteira2(m, l, c+1, fundo, f);
    if(l > 0)
      fronteira2(m, l-1, c, fundo, f);
    if(c > 0)
      fronteira2(m, l, c-1, fundo, f);
  }
  else if(m->mapa[l][c] != -fundo) {
    insere_fronteira(f, l, c, m->mapa[l][c]);
  }
}

// Funcao auxiliar
// Explora todas as fronteiras recursivamente
static void explora_fronteira(tfronteira * f, tmapa * tmp, int x, int y, int* saltos){
    if (f->tamanho == 0) return;
//    mostra_fronteira(f);
    for (int k = 0; k < f->tamanho; k++){
        tfronteira * f2 = aloca_fronteira(tmp);
        int x2, y2;
        x2 = f->pos[k].l;
        y2 = f->pos[k].c;
        int valor_celula = tmp->mapa[x2][y2];
        if (valor_celula > 0){
            // Na versao em Fila, nessa etapa seria criada a marcacao de vizinho
            // cria link (x,y) -> (x2,y2)
            (*saltos)++;
//            printf("%d\n", (*saltos));
            fronteira2(tmp, x2, y2, tmp->mapa[x2][y2], f2);
            explora_fronteira(f2, tmp, x2, y2, saltos);
        }
    }
}

int heuristica_3(tmapa * m){
    tmapa * tmp = aloca_mapa(m);
    copia_mapa(m, tmp);

    int vetor[1000];
    int numero_componentes = 0;
    int saltos = 0;
    tfronteira * f = aloca_fronteira(tmp);
    fronteira2(tmp, 0, 0, tmp->mapa[0][0], f);
    explora_fronteira(f, tmp, 0, 0, &saltos);
    libera_fronteira(f);
    libera_mapa(tmp);
    return saltos;
}

// Versao iterativa com fila, mais eficiente do ponto de vista da memoria
// associando arestas a vertices de um grafo (em que cada
// vertice eh um componente do floodit)
static void explora_fronteira_fila(tmapa * tmp, int* saltos, int* numero_componentes){
    thead * fila = l_init();
    tpos * pos_atual = (tpos *) malloc(sizeof(tpos));
    pos_atual->l=0;
    pos_atual->c=0;
    pos_atual->v=tmp->mapa[0][0];
    int x = 0;
    int y = 0;
    l_insert(fila, pos_atual);
    int k = 0;
    while(fila->size > 0){ //&& k < 100){
        k++;
        pos_atual= l_pop_first(fila);
        while(pos_atual != NULL && pos_atual->v < 0){
            free(pos_atual);
            pos_atual= l_pop_first(fila);
        }
        tfronteira * f2 = aloca_fronteira(tmp);
        x = pos_atual->l;
        y = pos_atual->c;
        fronteira2(tmp, x, y, pos_atual->v, f2);
        for (int k = 0; k < f2->tamanho; k++){
            x = f2->pos[k].l;
            y = f2->pos[k].c;
            int valor_celula = tmp->mapa[x][y];
            if (valor_celula > 0){
                // Nessa etapa podemos criar um grafo
                // cria link (x,y) -> (x2,y2)
                (*saltos)++;
                tpos * nova_pos = (tpos *) malloc(sizeof(tpos));
                nova_pos->l = f2->pos[k].l; nova_pos->c = f2->pos[k].c;
                nova_pos->v = f2->pos[k].v;
                l_insert(fila, nova_pos);
            }
        }
        (*numero_componentes)++;
        free(pos_atual);
        libera_fronteira(f2);
    }
    l_free(fila);
    return;
}
int heuristica_4(tmapa * m){
    tmapa * tmp = aloca_mapa(m);
    copia_mapa(m, tmp);

    int vetor[1000];
    int numero_componentes = 0;
    int saltos = 0;
    explora_fronteira_fila(tmp, &saltos, &numero_componentes);
    libera_mapa(tmp);
    return saltos;
}
int heuristica_5(tmapa * m){
    tmapa * tmp = aloca_mapa(m);
    copia_mapa(m, tmp);

    int vetor[1000];
    int numero_componentes = 0;
    int saltos = 0;
    explora_fronteira_fila(tmp, &saltos, &numero_componentes);
    libera_mapa(tmp);
    return (saltos + numero_componentes)/m->nlinhas / 2  - 1;
}

int heuristica_6(tmapa * m){
    tmapa * tmp = aloca_mapa(m);
    copia_mapa(m, tmp);

    int vetor[1000];
    int numero_componentes = 0;
    int saltos = 0;
    explora_fronteira_fila(tmp, &saltos, &numero_componentes);
    libera_mapa(tmp);
    return (saltos + numero_componentes)/50 - 1;
}

// Retorna ponteiro para funcao de heuristica
tipo_funcao escolhe_heuristica(int numero){
    tipo_funcao h;
    switch(numero){
        case 1:
            h = &heuristica_1;
        break;
        case 2:
            h = &heuristica_2;
        break;
        case 3:
            h = &heuristica_3;
        break;
        case 4:
            h = &heuristica_4;
        break;
        case 5:
            h = &heuristica_5;
        break;
        case 6:
            h = &heuristica_6;
        break;
        default:
            return NULL;
    }
    return h;
}

/*
int main(int argc, char **argv) {
  tmapa m;

  carrega_mapa(&m);
  printf("%d\n", heuristica_1(&m));
  return 0;
}
*/

  

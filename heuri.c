#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"
#include "heuri.h"

// funcao auxiliar
void obtem_opcoes(tmapa * m, int ** vet_cor){
    tfronteira *f;
//    printf("%d cores no inicio do jogo\n", m->ncores);
    int i, j, ncores, cor;
    int * vetor_cores = (*vet_cor);

    f = aloca_fronteira(m);

    for (i = 0; i < m->ncores; i++){
        vetor_cores[i] = 0;
    }
//    printf("Cores na fronteira: \n");
    fronteira_mapa(m, f);
    for (i = 0; i < f->tamanho; i++){
        cor = m->mapa[f->pos[i].l][f->pos[i].c];
//        printf(" %d ", cor);
        vetor_cores[cor-1]=1;
    }
//    printf("\n");
//    printf("Vetor de cores: \n");
    ncores = 0;
    for (cor = 0; cor < m->ncores; cor++){
//        printf("%d ", vetor_cores[cor]);
    }
//    printf("\n");
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            ncores++;
//            printf("%d ", cor);
        }
    }
//    printf("\n");
    int * opcoes = malloc(sizeof(int) * ncores);
    j = 0;
    for (cor = 0; cor < m->ncores; cor++){
        if (vetor_cores[cor] != 0){
            opcoes[j]=cor+1; 
            j++;
        }
    }
//    printf("Ncores: %d\n", ncores);
//    printf("Opcoes: ", ncores);

    for (int j = 0; j < ncores; j++){
//        printf("%d ",opcoes[j]);
    }
//    printf("\n");



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
// Essa versao nao eh muito util
// Reimplementar com recursao em FILA ao inves de PILHA,
// associando arestas a vertices de um grafo (em que cada
// vertice eh um componente do floodit)
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
    return saltos;
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

  

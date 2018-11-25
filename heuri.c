#include "heuri.h"

// funcao auxiliar
void obtem_cores(tmapa * m, int * vet_cor){
    tfronteira *f;
    int i, cor;
    f = aloca_fronteira(m);
    fronteira_mapa(m, f);

    for (i = 0; i < m->ncores; i++){
        vet_cor[i] = 0;
    }
    for (i = 0; i < f->tamanho; i++){
        cor = m->mapa[f->pos[i].l * m->nlinhas + f->pos[i].c];
        vet_cor[cor-1]=1;
    }
    libera_fronteira(f);
}

// Conta quantas cores falta para solucionar o floodit
int heuristica_1(tmapa * m){
    int tam_vetor = m->ncores + 1;
    int * vet_cor = (int*) malloc((tam_vetor) * sizeof(int));
    int i, j;
    for (i = 0; i < tam_vetor; i++){
        vet_cor[i]=0;
    } 
    for (i = 0; i < m->nlinhas; i++){
        for (j = 0; j < m->ncolunas; j++){
            vet_cor[m->mapa[i * m->nlinhas + j]]=1; 
        }
    }
    int qtde_cores = 0;
    for (i = 0; i < tam_vetor; i++){
        if (vet_cor[i] != 0){
            qtde_cores++;
        }
    } 
    free(vet_cor);
    return qtde_cores - 1;
}

// Conta quantas celulas falta para solucionar o floodit
int heuristica_2(tmapa * m){
    int count = 0;
    int cor_atual = m->mapa[0];
    for (int i =0; i < m->nlinhas;i++){
        for (int j = 0; j < m->ncolunas;j++){
            if (m->mapa[i*m->nlinhas+j] != cor_atual){
                count++; 
            }
        }
    } 
//    printf("%d\n", count);
    return count;
}

int heuristica_3(tmapa * m){
    int * histograma_cores = (int *) malloc(sizeof(int ) * m->ncores);

    // inicializando histograma
    for (int k = 0; k < m->ncores; k++){
      histograma_cores[k] = 0;
    }
    for (int i =0; i < m->nlinhas;i++){
        for (int j = 0; j < m->ncolunas;j++){
            histograma_cores[m->mapa[i*m->nlinhas+j]] += 1;
        }
    }
    // normalizando histograma
    int tab_size = m->nlinhas * m->ncolunas;
    int max_freq = 0;
    for (int k = 0; k < m->ncores; k++){
      if (histograma_cores[k] > max_freq){
        max_freq = histograma_cores[k];
      }
    }
    free(histograma_cores);
    return tab_size - max_freq;
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

  

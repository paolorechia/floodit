#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

int main(int argc, char **argv) {
  int i;
  int cor;
  int ncor;
  int *ncorfront;
  tmapa * mapa_inicial = carrega_mapa();
  tfronteira *f;
  tplano *p;

  

  mostra_mapa(mapa_inicial);

  f = aloca_fronteira(mapa_inicial);
  p = aloca_plano(mapa_inicial);
  
  ncorfront = (int*) malloc((mapa_inicial->ncores + 1) * sizeof(int));
  cor = mapa_inicial->mapa[0];
  fronteira_mapa(mapa_inicial, f);

  while(f->tamanho > 0) {
    for(i = 1; i <= mapa_inicial->ncores; i++)
      ncorfront[i] = 0;
    for(i = 0; i < f->tamanho; i++){
      int l = f->pos[i].l;
      int c = f->pos[i].c;
      ncorfront[mapa_inicial->mapa[l * mapa_inicial->nlinhas + c]]++;
    }
    ncor = 0;
    for(i = 1; i <= mapa_inicial->ncores; i++)
      if(ncorfront[i] > ncor) {
        ncor = ncorfront[i];
        cor = i;
      }
    pinta_mapa(mapa_inicial, cor);
    insere_plano(p, cor);
    fronteira_mapa(mapa_inicial, f);
  }
  mostra_plano(p);
  libera_mapa(mapa_inicial);
  
  return 0;
}
  

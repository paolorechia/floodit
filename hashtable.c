#include "hashtable.h"

// Inicializa a tabela hash
thashtable * h_init(int table_s){
  thashtable * hash = malloc(sizeof(thashtable));
  hash->table_size = table_s;
  hash->table_p = (thead **) malloc(sizeof(thead) * table_s);
  for (int i = 0; i < table_s; i++){
    hash->table_p[i] = NULL;
  }
  return hash;
}
// Funcao hash: traduz o estado para uma chave
int h_genkey(tmapa * state, int table_s){
  int key = 0;
  for (int i = 0; i < state->nlinhas; i++){
    for (int j = 0; j < state->ncolunas; j++){
      key += state->mapa[i][j];
    }
  }
  return key % table_s;
}
// Insere estado na tabela hash
int h_insert(thashtable *hash, tmapa * state){
  int key = h_genkey(state, hash->table_size);
  thead * list = h_getlist(hash, key);
  // se a chave ainda nao existe, estado eh novo, inserir
  if (list == NULL){
    list = l_init();
    hash->table_p[key] = list;
    l_insert(list, state); 
    return 1;
  }
  // se a chave ja existe, buscar na lista da chave
  else{
    // se encontrou na lista, estado ja existe, abortar
    if ((l_search(list, state)) == 1) return 0;
    // senao, estado novo, inserir
    l_insert(list, state);
    return 1;
  }
}
thead * h_getlist(thashtable *hash, int key){
  return hash->table_p[key];
}
// Verifica se estado esta na tabela hash
int h_findstate(thashtable * hash, tmapa * state){
  int key = h_genkey(state, hash->table_size);
  thead * list = h_getlist(hash, key);
  if (list != NULL){
    return l_search(list, state);
  }
  else return 0;
}

// Limpa da memoria a tabela hash
void h_free(thashtable * hash){
  for (int i = 0; i < hash->table_size; i++){
    if (hash->table_p[i] != NULL){
      l_free(hash->table_p[i]);
    }
  }
  free(hash->table_p);
  free(hash);
}

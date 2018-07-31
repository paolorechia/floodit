/*! \file */ 

#ifndef __LIST_H__
#define __LIST_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/

/**
* @brief Estrutura da celula da lista encadeada 
*/
typedef struct cel_struct{
    tpos * key; /**< Chave **/
    struct cel_struct * nxt; /**< Ponteiro para proxima celula **/
} tnode;

/**
* @brief Cabeca da lista
  Esta struct aponta para a primeira celula da lista encadeada
*/
typedef struct head{
    tnode * node;
    int size;
} thead;

thead * l_init();
/**
 * @brief Funçao usada para inserir os tposs (vizinhança) na lista daquele vertice.
 * Testando descricao
 */
void l_insert(thead *, tpos *);
/**
* Funçao auxiliar para ajudar a debugar o programa.
*/
void l_print(thead * head);
int l_size(thead * head);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
int rec_clear(tnode * node);
//Funçao para limpar a lista.
int l_clear(thead * head);
// Desaloca memoria
void l_free(thead *head);
// Busca sequencial de elemento na lista
int l_search(thead* head, tpos * buscado);
//Funcao que verifica a interseccao entre os dois vertives.
thead * l_intersection(thead *l1, thead * l2);
// cria uma copia da lista
thead * l_copy(thead *list);
// Filtra l1 com os elementos da lista2
// (Retorna elementos de l1 nao encontrados em l2)
// Utilizado para calcular a diferenca de conjunto
thead * l_filter(thead *l1, thead *l2);

tpos* l_pop_first(thead *l1);
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

#endif

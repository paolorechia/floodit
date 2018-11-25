#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
typedef struct cel_struct{
    tmapa * key;
    struct cel_struct * nxt;
} tnode;

typedef struct head{
    tnode * node;
    int size;
} thead;

thead * l_init();
void l_insert(thead * head, tmapa * new);
int l_remove(thead * head, tmapa * remover);
void l_print(thead * head);
int l_size(thead * head);
int rec_clear(tnode * node);
int l_clear(thead * head);
void l_free(thead *head);
int l_search(thead* head, tmapa * buscado);
thead * l_copy(thead *list);
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

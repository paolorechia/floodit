#include "list.h"
/*************************************************
* Estrutura de dados auxiliar - lista encadeada 
*************************************************/

//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 thead * l_init(){
    thead * head = malloc(sizeof(thead));
    head->node = malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    head->node->key = NULL;
    return head;
}


/**
* Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
*/
 void l_insert(thead * head, tpos * new){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=malloc(sizeof(tnode));
    node->nxt->key = malloc(sizeof(tpos));
    node->nxt->key->c = new->c;
    node->nxt->key->l = new->l;
    node->nxt->key->v = new->v;
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
}

// pop FIFO
// Implementar
tpos * l_pop_first(thead * head){
    tpos * aux;
    aux = malloc(sizeof(tpos));
    tnode * node = head->node->nxt;
    aux->l = node->key->l;
    aux->c = node->key->c;
    aux->v = node->key->v;
    head->node->nxt = node->nxt;
    head->size--;
    free(node->key);
    free(node);
    return aux;
}
//Funçao auxiliar para ajudar a debugar o programa.
 void l_print(thead * head){
    printf("--------->"); 
    if (head->node->nxt == NULL){
        printf("Empty l\n");
        return;
    }
    tnode * node = head->node->nxt;
    while (node){
        printf("(%d,%d):%d ", node->key->l,
                              node->key->c,
                              node->key->v);
        node = node->nxt;
    }
    putchar('\n');
}

 int l_size(thead * head){
    return head->size;
}

/* Funcao recursiva para limpar lista a partir do ultimo no*/
 int rec_clear(tnode * node){
    if (node->nxt != NULL){
        rec_clear(node->nxt);
    }
//    printf("Freeing node of name: %s\n", node->key);
    node->nxt = NULL;
    free(node->key);
    free(node);
    return 0;
}

//Funçao para limpar a lista.
 int l_clear(thead * head){
    if (head->node->nxt == NULL){
        return 0;
    }
    rec_clear(head->node->nxt);
    head->node->nxt = NULL;
    head->size = 0;
    return 1;
}

// Desaloca memoria
 void l_free(thead *head){
    l_clear(head);
    free(head->node);
    free(head);
}
// Filtra l1 com os elementos da lista2
// (Retorna elementos de l1 nao encontrados em l2)
// Utilizado para calcular a diferenca de conjunto
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

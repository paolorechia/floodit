#include "list.h"

/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
 thead * l_init(){
    thead * head = (thead *) malloc(sizeof(thead));
    head->node = (tnode *) malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    head->node->key = NULL;
    return head;
}

 void l_insert(thead * head, tmapa * new){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=(tnode *) malloc(sizeof(tnode));
    node->nxt->key = aloca_mapa(new);
    copia_mapa(new, node->nxt->key);
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
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
        mostra_mapa(node->key);
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
    libera_mapa(node->key);
    node->nxt = NULL;
    free(node);
    return 0;
}

//Funçao para limpar a lista.
 int l_clear(thead * head){
//    tnode * node = head->node;
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
// Busca sequencial de elemento na lista
 int l_search(thead* head, tmapa * buscado){
    // if empty list
    if (head->node->nxt == NULL){
        return 0;
    }
    tnode * node = head->node->nxt;
    while (node){
        if (compara_mapas(node->key, buscado)) return 1;
        node = node->nxt;
    }   
    return 0;
}

// cria uma copia da lista
 thead * l_copy(thead *list)
{
    // No auxiliar
    thead* new_list = l_init();
    tnode * lnode = list->node->nxt;
    while (lnode)
    {
        l_insert(new_list, lnode->key); // Insere chave na lista nova
        lnode = lnode->nxt;         // Proximo elemento da lista
    }
    return new_list; //Return de head of the copy.
}

/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

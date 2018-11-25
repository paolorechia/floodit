#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "mapa.h"


typedef struct hash_struct{
  int table_size;
  thead ** table_p;
} thashtable;

// Init hash table
thashtable * h_init(int table_s);
// Hash function, translates a state into a hash key
int h_genkey(tmapa * state, int table_s);
// Insert state into hash table
int h_insert(thashtable * hash, tmapa * state);
// Returns a linked list where the state may be found
thead * h_getlist(thashtable * hash, int key);
// Check if state is in hash table
int h_findstate(thashtable * hash, tmapa * state);
// Frees hash table from memory
void h_free(thashtable * hash);

#endif

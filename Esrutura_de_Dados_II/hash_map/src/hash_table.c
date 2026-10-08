#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

// uma função statica em c só pode ser chamada dentro do mesmo arquivo
static ht_item* ht_new_items(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

ht_hash_table* new_ht(const int size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = size;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(h_item*));

    return ht;
}

static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < hht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) ht_del_item(item);
    }
    free(ht->items);
    free(ht);
}
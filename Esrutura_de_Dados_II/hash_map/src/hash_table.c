#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

// variaveis estáticas globais só podem ser usadas dentro do mesmo arquivo
static ht_item HT_DELETED_ITEM = {NULL, NULL};

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

static int ht_hash(const char* s, const int a, const int m ) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i<len_s; i++) {
        hash += (long)pow(a, len_s - (i+1) * s[i]);
        hash = hash % m;
    }
    return (int)hash;
}

// Lidando com colisões
static int ht_get_hash(const har* s, cont int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + (attempt * (hash_b + 1))) % num_buckets
}

void ht_insert(ht_hash_table* ht, const char* k, const char* v) {
    ht_item* item = ht_new_item(k, v);
    int index = get_hash_hash(item->key, h->size, 0);
    // verifica se a posição está ocupada
    // se cur_item for null (bucket vazio)
    // pula o loop
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item - ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++
}

char* ht_search(ht_hash_table* ht, const char* k) {
    int index = ht_get_hash(k, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETE_ITEM && strcmp(item->key, k) == 0) return item->value;

        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void ht_delete(ht_hash_table* ht, const char* k) {
    int index = ht_get_hash(k, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            ht_del_item(item);
            ht->items[index] = &HT_DELETED_ITEM;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
    }
    ht->count--;
}
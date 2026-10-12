#include <stdlib.h>
#include <string.h>
#include "prime.h"
#include "hash_table.h"

#include <math.h>

// variaveis estáticas globais só podem ser usadas dentro do mesmo arquivo
static const int HT_INITIAL_BASE_SIZE = 50;
static ht_item HT_DELETED_ITEM = {NULL, NULL};
static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;

// uma função statica em c só pode ser chamada dentro do mesmo arquivo
static ht_item* ht_new_items(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}


// cria a tabela hash com o tamanho especificado
static ht_hash_table* ht_new_sized(const int base_size){
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	ht->base_size = base_size;

	ht->size = next_prime(ht->base_size);

	ht->count = 0;
	ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
	return ht;
}


// inicializa uma nova tabela hash
ht_hash_table* new_ht(const int size) {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

// apaga o item na tabela
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);

}

// apaga a tabela hash
void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) ht_del_item(item);
    }
    free(ht->items);
    free(ht);
}

// redimensiona a tabela hash
static void ht_resized(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) return;

    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // deletando a nova tabela e passando tudo para a antiga
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

// aumenta a tabela
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resized(ht, new_size);
}

// diminui a tabela
static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resized(ht, new_size);
}

// cria o hash de uma string
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
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

// insere na tabela hash
void ht_insert(ht_hash_table* ht, const char* k, const char* v) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) { ht_resize_up(ht);}
    ht_item* item = ht_new_items(k, v);
    int index = ht_get_hash(item->key, ht->size, 0);
    // verifica se a posição está ocupada
    // se cur_item for null (bucket vazio)
    // pula o loop
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

// busca na tabela hash
char* ht_search(ht_hash_table* ht, const char* k) {
    int index = ht_get_hash(k, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM && strcmp(item->key, k) == 0) return item->value;

        index = ht_get_hash(k, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

// deleta um item da tabela hash
void ht_delete(ht_hash_table* ht, const char* k) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {ht_resize_down(ht);}

    int index = ht_get_hash(k, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            ht_del_item(item);
            ht->items[index] = &HT_DELETED_ITEM;
        }
        index = ht_get_hash(k, ht->size, i);
        item = ht->items[index];
    }
    ht->count--;
}


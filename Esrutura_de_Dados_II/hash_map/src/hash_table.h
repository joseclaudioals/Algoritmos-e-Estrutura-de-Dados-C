#ifndef TREINAMENTO_C_HASH_TABLE_H
#define TREINAMENTO_C_HASH_TABLE_H

#endif //TREINAMENTO_C_HASH_TABLE_H

typedef struct {
    char* key;
    char* value;
}ht_item;

typedef struct{
    int base_size;
    int size;
    int count;
    ht_item** items;
}ht_hash_table;

// Cria a tabela
ht_hash_table* new_ht(const int size);

// Deleta a tabela
void ht_del_hash_table(ht_hash_table* ht);

// Insere ou atualiza um item
void ht_insert(ht_hash_table* ht, const char* k, const char* v);

// Busca um item
char* ht_search(ht_hash_table* ht, const char* k);

// Deleta um item
void ht_delete(ht_hash_table* ht, const char* k);
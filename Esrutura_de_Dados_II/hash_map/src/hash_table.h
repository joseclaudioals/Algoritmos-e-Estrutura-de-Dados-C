#ifndef TREINAMENTO_C_HASH_TABLE_H
#define TREINAMENTO_C_HASH_TABLE_H

#endif //TREINAMENTO_C_HASH_TABLE_H

typedef struct {
    char* key;
    char* value;
}ht_item;

typedef struct{
    int size;
    int count;
    ht_item** items;
}ht_hash_table;


#include <stdio.h>
#include "hash_table.h"

int main() {
    printf("=== INICIANDO TESTES DA TABELA HASH ===\n\n");

    // 1. Criando a tabela
    // O seu new_ht recebe um tamanho, mas usa o tamanho base internamente.
    ht_hash_table* ht = new_ht(50);
    printf("[+] Tabela hash criada com sucesso!\n\n");

    // 2. Testando Inserção
    printf("--- TESTANDO INSERCAO ---\n");
    ht_insert(ht, "nome", "Joao Silva");
    ht_insert(ht, "linguagem", "C");
    ht_insert(ht, "sistema", "Linux");
    printf("[+] 3 itens inseridos.\n\n");

    // 3. Testando Busca (Search)
    printf("--- TESTANDO BUSCA ---\n");
    char* res1 = ht_search(ht, "nome");
    char* res2 = ht_search(ht, "linguagem");
    char* res_null = ht_search(ht, "idade"); // Chave que não existe

    printf("Busca 'nome': %s\n", res1 ? res1 : "Nao encontrado");
    printf("Busca 'linguagem': %s\n", res2 ? res2 : "Nao encontrado");
    printf("Busca 'idade' (inexistente): %s\n\n", res_null ? res_null : "Nao encontrado (Correto!)");

    // 4. Testando Atualização (O fix que fizemos no ht_insert)
    printf("--- TESTANDO ATUALIZACAO ---\n");
    printf("Valor antigo de 'nome': %s\n", ht_search(ht, "nome"));
    ht_insert(ht, "nome", "Maria Souza"); // Inserindo na mesma chave
    printf("Novo valor de 'nome': %s\n\n", ht_search(ht, "nome"));

    // 5. Testando Deleção
    printf("--- TESTANDO DELECAO ---\n");
    ht_delete(ht, "sistema");
    char* res_del = ht_search(ht, "sistema");
    printf("Busca 'sistema' apos deletar: %s\n\n", res_del ? res_del : "Nao encontrado (Deletado com sucesso!)");

    // 6. Testando Redimensionamento (Resize Up) / Stress Test
    printf("--- TESTANDO CARGA ALTA (RESIZE UP) ---\n");
    char key[20];
    char value[20];
    for (int i = 0; i < 100; i++) {
        sprintf(key, "chave_%d", i);
        sprintf(value, "valor_%d", i);
        ht_insert(ht, key, value);
    }
    printf("[+] 100 itens inseridos para forcar o aumento da tabela.\n");

    char* res_stress = ht_search(ht, "chave_50");
    printf("Busca 'chave_50': %s\n\n", res_stress ? res_stress : "Erro");

    // 7. Limpeza de Memória
    ht_del_hash_table(ht);
    printf("=== TESTES FINALIZADOS E MEMORIA LIBERADA ===\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

typedef struct {
    int v;
    Node** adj;
}Graph;

typedef struct {
    int* colors;
    int* pre;
    int* start;
    int* end;
}dfsInfo;

Graph* startGraph(int v);
void addEdge(Graph* g, int s, int d);
void printGraph(const Graph* g);
void freeGraph(Graph* g);
dfsInfo* startDFS(int v);
void DFS_VISIT(Graph* g, dfsInfo* d, int u, int* time);
dfsInfo* dfs(Graph* g);
void freeDFS(dfsInfo* d);

int main(void) {
    Graph* g = startGraph(6);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 4, 5);

    printf("--- Estrutura do Grafo ---\n");
    printGraph(g);

    printf("\n--- Executando DFS ---\n");
    dfsInfo* d = dfs(g);

    for (int i = 0; i < g->v; i++) {
        printf("Vertice: %3d Descoberta: %3d Finalizacao: %3d Predecessor: %3d\n", i, d->start[i], d->end[i], d->pre[i]);
    }

    freeDFS(d);
    freeGraph(g);

    return 0;
}

Graph* startGraph(int v) {
    Graph* g = malloc(sizeof(Graph));
    if (!g) return NULL;
    g->v = v;
    g->adj = calloc(v, sizeof(Node*));
    if (!g->adj) return NULL;

    return g;
}

void addEdge(Graph* g, int s, int d) {
    if (!g) return;
    Node* n = malloc(sizeof(Node));
    if (!n) return;

    n->vertex = d;
    n->next = g->adj[s];
    g->adj[s] = n;
}

void printGraph(const Graph* g) {
    if (g) {
        for (int i = 0; i<g->v; i++) {
            printf("Vertice %d: ", i);
            Node* temp = g->adj[i];
            while (temp) {
                printf("%d -> ", temp->vertex);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void freeGraph(Graph* g) {
    if (g) {
        for (int i = 0; i<g->v; i++) {
            Node* temp = g->adj[i];
            while (temp) {
                g->adj[i] = temp->next;
                free(temp);
                temp = g->adj[i];
            }
        }
        free(g->adj);
        free(g);
    }
}

dfsInfo* startDFS(int v) {
    dfsInfo* d = malloc(sizeof(dfsInfo));
    if (!d) return NULL;
    d->colors = malloc(sizeof(int) * v);
    d->pre = malloc(sizeof(int) * v);
    d->start = malloc(sizeof(int) * v);
    d->end = malloc(sizeof(int) * v);
    if (!d->colors || !d->pre || !d->start || !d->end) return NULL;

    return d;
}

void DFS_VISIT(Graph* g, dfsInfo* d, int u, int* time) {
    if (!g || !d) return;
    (*time)++;
    d->start[u] = *time;
    d->colors[u] = 0;
    Node* temp = g->adj[u];
    while (temp) {
        int v = temp->vertex;
        if (d->colors[v]==-1) {
            d->pre[v] = u;
            DFS_VISIT(g, d, v, time);
        }
        temp = temp->next;
    }
    d->colors[u] = 1;
    (*time)++;
    d->end[u] = *time;
}

dfsInfo* dfs(Graph* g) {
    if (!g) return NULL;

    dfsInfo* d = startDFS(g->v);
    for (int u = 0 ; u < g->v ; u++) {
        d->colors[u] = -1; // -1 = white | 0 = white | 1 = preto
        d->pre[u] = -1; // null
    }

    int time = 0;
    for (int u = 0; u < g->v ; u++)
        if (d->colors[u] == -1) DFS_VISIT(g, d, u, &time);

    return d;
}

void freeDFS(dfsInfo* d) {
    if (!d) return;
    free(d->colors);
    free(d->start);
    free(d->end);
    free(d->pre);
    free(d);
}
//
// Created by josecls on 05/06/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

typedef struct {
    int v;
    Node** adj;
}Graph;

typedef struct {
    int* color;
    int* dist;
    int* pre;
    Node* queue;
    Node* tail;
}BFS;

Graph* startGraph(int v);
void addEdge(Graph* g, int u, int v) ;
void printGraph(const Graph* g);
void freeGraph(Graph* g);
void enqueue(BFS* b, int s);
Node* dequeue(BFS* b);
BFS* startBFS(int v);
BFS* bfs(Graph* g, int s);
void freeBFS(BFS* b);

int main(void) {
    int num_vertices = 6;
    Graph* g = startGraph(num_vertices);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 5);
    addEdge(g, 4, 5);

    printf("--- ESTRUTURA DO GRAFO ---\n");
    printGraph(g);
    printf("\n");

    int origem = 0;
    printf("--- EXECUTANDO BFS (Origem: %d) ---\n", origem);
    BFS* resultado = bfs(g, origem);

    if (resultado) {
        for (int i = 0; i < num_vertices; i++) {
            printf("Vertice %d | Distancia: %d | Predecessor: %d \n",
                    i, resultado->dist[i], resultado->pre[i]);
        }
        freeBFS(resultado);
    }

    freeGraph(g);
    return 0;
}

Graph* startGraph(int v) {
    Graph* g = malloc(sizeof(Graph));
    if (!g) return NULL;
    g->v = v;
    g->adj = malloc(sizeof(Node*) * v);
    if (!g->adj) return NULL;
    for (int i = 0; i < v ; i++) g->adj[i] = NULL;

    return g;
}

void addEdge(Graph* g, int u, int v) {
    if (!g) return;
    Node* n = malloc(sizeof(Node));
    if (!n) return;

    n->vertex = v;
    n->next = g->adj[u];
    g->adj[u] = n;
}

void printGraph(const Graph* g) {
    if (!g) return;
    for (int i = 0; i<g->v; i++) {
        printf("Vertice %d: \n", i);
        Node* temp = g->adj[i];
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeGraph(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->v; i++) {
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

void enqueue(BFS* b, int s) {
    Node* n = malloc(sizeof(Node));
    n->vertex = s;
    n->next = NULL;

    if (!b->queue) {
        b->queue = n;
        b->tail = n;
        return;
    }
    b->tail->next = n;
    b->tail = n;
}

Node* dequeue(BFS* b) {
    if (!b->queue) return NULL;

    Node* temp = b->queue;
    b->queue = b->queue->next;

    if (!b->queue) b->tail = NULL;

    return temp;
}

BFS* startBFS(int v) {
    BFS* b = malloc(sizeof(BFS));
    if (!b) return NULL;
    b->color = malloc(sizeof(int) * v);
    b->dist = malloc(sizeof(int) * v);
    b->pre = malloc(sizeof(int) * v);
    if (!b->color || !b->dist || !b->pre) return NULL;
    b->queue = NULL;
    b->tail = NULL;

    return b;
}

BFS* bfs(Graph* g, int s) {
    if (!g || s < 0 || s >= g->v ) return NULL;

    BFS* b = startBFS(g->v);
    for (int u = 0; u<g->v; u++) {
        if (u == s) continue;
        b->color[u] = -1; // -1 = branco | 0 = cinza | 1 = preto
        b->dist[u] = INT_MAX;
        b->pre[u] = -1; // nulo
    }

    b->color[s] = 0;
    b->dist[s] = 0;
    b->pre[s] = -1;

    enqueue(b, s);

    while (b->queue) {
        Node* u = dequeue(b);
        Node* v = g->adj[u->vertex];
        while (v) {
            if (b->color[v->vertex] == -1) {
                b->color[v->vertex] = 0;
                b->pre[v->vertex] = u->vertex;
                b->dist[v->vertex] = b->dist[u->vertex] + 1;
                enqueue(b, v->vertex);
            }
            v = v->next;
        }
        b->color[u->vertex] = 1;
        free(u);
    }
    return b;
}

void freeBFS(BFS* b) {
    free(b->color);
    free(b->dist);
    free(b->pre);
    free(b);
}
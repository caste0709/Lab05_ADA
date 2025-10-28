#include <stdio.h>
#include <stdlib.h>

static int cnt;
int pre[1000];

#define vertex int

typedef struct node *link;

struct node {
    vertex w;
    link next;
};

typedef struct graph *Graph;

struct graph {
    int V;
    int A;
    link *adj;
};

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof(struct node));
    if (a == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }

    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    if (G->adj == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }

    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;

    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;

    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}
static void dfsR_iterativo(Graph G, vertex s) {
    int stack[1000];
    int top = -1;

    stack[++top] = s;

    while (top >= 0) {
        vertex v = stack[top--];

        if (pre[v] != -1)
            continue;  

        pre[v] = cnt++;
        link a;
        for (a = G->adj[v]; a != NULL; a = a->next) {
            vertex w = a->w;
            if (pre[w] == -1)
                stack[++top] = w;
        }
    }
}

void GRAPHdfs(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfsR_iterativo(G, v);
}

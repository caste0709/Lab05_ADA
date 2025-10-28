#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cnt;
int pre[1000];
#define vertex int
static int sangria=0;

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

static void printsangria(int level) {
    for (int i = 0; i < level; i++) {
        printf("    "); 
    }
}

static void dfsR(Graph G, vertex v) {
    if (pre[v] == -1) {
        printsangria(sangria - 1);
        printf("%d \n", v); 
    }

    pre[v] = cnt++;
    sangria++; 
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        printsangria(sangria - 1);
        printf("%d-%d ", v, w); 
        
        if (pre[w] == -1) {
            printf("dfsR(G,%d)\n", w);
            dfsR(G, w);
        } 
        else {
            printf("\n"); 
        }
    }
    sangria--; 
    printsangria(sangria);
    printf("%d\n", v);
}

void GRAPHdfs(Graph G) {
    cnt = 0;
    sangria = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v) { 
        if (pre[v] == -1) { 
            printf("%d dfsR(G,%d)\n", v, v);
            dfsR(G, v);
        }
    }
}

Graph leer_txt(const char *archivo) {
    FILE *file = fopen(archivo, "r");
    if (file == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        exit(1);
    }
    int V;
    if (fscanf(file, "%d", &V) != 1 || V <= 0) {
        fprintf(stderr, "Error al leer el número de vértices\n");
        fclose(file);
        exit(1);
    }
    Graph G = GRAPHinit(V);
    int u, w;
    char line[1000];
    fgets(line, sizeof(line), file); 
    for (int i = 0; i < V; ++i) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break; 
        }
        char *token;
        char *rest = line; 
        token = strtok_r(rest, " \t\n\r", &rest); 
        if (token == NULL) {
            continue;
        }

        if (sscanf(token, "%d", &u) != 1) {
            continue;
        }

        if (u < 0 || u >= V) {
             fprintf(stderr, "Error: Vértice origen (%d) fuera de rango (0 a %d).\n", u, V - 1);
             continue;
        }
        while ((token = strtok_r(rest, " \t\n\r", &rest))) {
            if (sscanf(token, "%d", &w) == 1) {
                if (w >= 0 && w < V) {
                    GRAPHinsertArc(G, u, w);
                } else {
                    fprintf(stderr, "Error: Vértice adyacente (%d) fuera de rango (0 a %d).\n", w, V - 1);
                }
            }
        }
    }
    fclose(file);
    return G;
}

int main(){
    char archivo[100];
    printf("Ingrese el nombre del archivo txt: ");
    scanf("%s", archivo);
    Graph grafo = leer_txt(archivo);
    printf("--- Rastreo de la ejecución de GRAPHdfs(G) ---\n");
    GRAPHdfs(grafo);
    return 0;
}

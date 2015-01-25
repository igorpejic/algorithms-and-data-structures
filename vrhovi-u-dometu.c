#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define TRUE  1
#define FALSE 0
typedef int bool;

#define WHITE 0
#define GRAY  1
#define BLACK 2
typedef int color;

typedef struct {
    int adj[MAXV][MAXV];
    int nvertices;
    char labels[MAXV];
    int distances[MAXV];
    color colors[MAXV];
} graph;

int find_vertex_index(graph *g, char label) {
    int u;

    for (u=0; u<g->nvertices; u++) {
        if (g->labels[u]==label)
            return u;
    }
    return -1;
}

void initialize_attributes(graph *g) {
    int v;

    for (v=0; v<g->nvertices; v++) {
        g->distances[v] = 0;
        g->colors[v] = WHITE;
    }
}

graph *initialize_graph() {
    int u, v;
    graph *g;

    g = (graph *)malloc(sizeof(graph));
    if (!g) return NULL;
    g->nvertices = 0;
    for (u=0; u<MAXV; u++) {
        for (v=0; v<MAXV; v++) {
            g->adj[u][v] = 0;
        }
    }
    initialize_attributes(g);
    return g;
}

void print_graph(graph *g) {
    int u,v;

    for (u=0; u<g->nvertices; u++) {
        printf("%c: ",g->labels[u]);
        for (v=0; v<g->nvertices; v++) {
            if (g->adj[u][v])
                printf(" %c",g->labels[v]);
        }
        printf("\n");
    }
}

int add_vertex(graph *g, char label) {
    int u;

    u = g->nvertices++;
    g->labels[u] = label;
    return u;
}

void insert_edge_vertices(graph *g) {
    char label;
    int u, v;

    scanf(" %c",&label);
    u = find_vertex_index(g, label);
    if (u==-1) u = add_vertex(g, label);
    scanf(" %c", &label);
    if (label=='/') return;
    v = find_vertex_index(g, label);
    if (v==-1) v = add_vertex(g, label);
    g->adj[u][v] = g->adj[v][u] = 1;
}

void read_graph(graph *g) {
    int i, nedges;

    DEBUG("Unesite broj bridova: ");
    scanf("%d",&nedges);
    for (i=0; i<nedges; i++) {
        DEBUG("Unesite oznake vrhova brida %d ", i+1);
        insert_edge_vertices(g);
    }
}

int vrhovi_u_dometu(graph *g, int u, int dist) {
    int queue[MAXV], tail=-1, head=-1, v;

    queue[++tail] = u;  // enqueue
    g->colors[u] = GRAY;
    g->distances[u] = 0;
    while (tail!=head) {
        u = queue[++head];  // dequeue
        for (v=0; v<g->nvertices; v++) {
            if (g->adj[u][v]) {
                if (g->colors[v]==WHITE) {
                    g->colors[v] = GRAY;
                    queue[++tail] = v;  // enqueue
                    g->distances[v] = g->distances[u]+1;
                }
            }
        }
        g->colors[u] = BLACK;
    }
    int max=0;
    int len=0;
    int arr[MAXV];
    for (v = 0; v<g->nvertices; v++){
       if(g->distances[v] <= dist && g->distances[v] > 0)
            len++;
    }
    return len;
}

int main() {
    graph *g=NULL;
    int u,menu_choice, dist;
    char label,c;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1.Vrhovi u dometu (vrhovi_u_dometu)");
        DEBUG("\n2.Unos grafa\n3.Ispis grafa\n4.Izlaz\n");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                DEBUG("\nUnesite oznaku vrha: \n");
                scanf(" %c", &label);
                u = find_vertex_index(g,label);
                if (u==-1) break;
                initialize_attributes(g);
                DEBUG("\nUnesite udaljenost: \n");
                scanf("%d", &dist);
                printf("%d\n", vrhovi_u_dometu(g, u, dist));
                break;
            case 2:
                if (g) free (g);
                g = initialize_graph();
                if (!g) DEBUG("Neuspjesna inicijalizacija.");
                read_graph(g);
                break;
            case 3:
                DEBUG("\nIspis grafa:\n");
                print_graph(g);
                break;
            case 4:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=4);
    return 0;
}

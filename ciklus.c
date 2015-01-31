#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define TRUE  1
#define FALSE 0
typedef int bool;

#define WHITE 0
#define GRAY  1
#define BLACK 2
typedef int colors;

#define MAXV      100
#define MAXLABEL  10
#define INITDIST  INT_MAX

struct Edge;
typedef struct Vertex{
    char label[MAXLABEL];
    struct Edge *edges;
    // opcionalni atributi
    int distance;
    colors color;
} vertex;

typedef struct Edge {
    struct Vertex *u;
    struct Vertex *v;
    struct Edge *next;
    // opcionalni atributi
    int weight;
} edge;

typedef struct {
    vertex *vertices[MAXV];
    bool directed;
    bool weighted;
    int nvertices;
} graph;

vertex  *add_vertex(graph *g, char label[]);
void    delete_vertex(graph *g, vertex *u);
void    add_edge(graph *g, vertex *u, vertex *v, bool directed, int weight);
void    delete_edge(graph *g, vertex *u, vertex *v, bool directed);

int find_vertex_index(graph *g, vertex *v) {
    int i;

    for (i=0; i<g->nvertices; i++) {
        if (g->vertices[i]==v)
            return i;
    }
    return -1;
}

vertex *find_vertex(graph *g, char label[]) {
    int i;

    for (i=0; i<g->nvertices; i++) {
        if (!strcmp(g->vertices[i]->label,label))
            return g->vertices[i];
    }
    return NULL;
}

vertex *add_vertex(graph *g, char label[]) {
    int i;
    vertex *v;

    if (g->nvertices>=MAXV) {
        DEBUG("\nDosegnut je maksimalni broj vrhova.\n}");
        return NULL;
    }
    for (i=0; i<g->nvertices; i++) {
        v = g->vertices[i];
        if (!strcmp(v->label,label)) {
            DEBUG("\nVrh sa oznakom %s vec postoji.\n",label);
            return NULL;
        }
    }
    v = (vertex *) malloc(sizeof(vertex));
    strcpy(v->label,label);
    v->edges = NULL;
    v->distance = INITDIST;
    v->color = WHITE;

    g->vertices[g->nvertices++] = v;
    return v;
}

void clear_edges_list(edge *e) {
    if (!e) return;
    clear_edges_list(e->next);
    free(e);
}

void delete_vertex(graph *g, vertex *u) {
    int i;

    for (i=0; i<g->nvertices; i++)
        delete_edge(g,g->vertices[i],u,TRUE);
    i = find_vertex_index(g,u);
    if (i==-1) return;
    clear_edges_list(u->edges);
    free(u);
    for (; i<g->nvertices-1; i++)
        g->vertices[i] = g->vertices[i+1];
    g->nvertices--;
}

void add_edge(graph *g, vertex *u, vertex *v, bool directed, int weight) {
    edge *e, *ue;

    if (!u || !v) return;
    e = (edge *) malloc(sizeof(vertex));
    e->u = u;
    e->v = v;
    e->next = NULL;
    e->weight = weight;

    ue = u->edges;
    if (ue) {
        for (;ue->next;ue=ue->next) {
            if (ue->v==e->v) {
                DEBUG("Brid (%s %s) postoji", u->label, v->label);
            }
        }
        ue->next = e;
    } else {
        u->edges = e;
    }

    if (!directed)
        add_edge(g,v,u,TRUE,weight);
}

void delete_edge(graph *g, vertex *u, vertex *v, bool directed) {
    edge *e, *e_prev=NULL;

    if (!u || !v) return;
    for (e=u->edges;e;e=e->next) {
        if (e->v==v) {
            if (e_prev)
                e_prev->next = e->next;
            else
                u->edges = e->next;
            free(e);
        }
        e_prev = e;
    }

    if (!directed)
        delete_edge(g,v,u,TRUE);
}

graph *initialize_graph(bool directed, bool weighted) {
    graph *g;

    g = (graph *)malloc(sizeof(graph));
    g->directed = directed;
    g->weighted = weighted;
    g->nvertices = 0;
    return g;
}

void empty_graph(graph *g) {
    int i;

    for (i=g->nvertices-1; i>=0; i--) {
        delete_vertex(g, g->vertices[i]);
    }
}

void insert_edge_vertices(graph *g) {
    char label[MAXLABEL];
    vertex *u, *v;
    int weight;

    scanf(" %s",label);
    u = find_vertex(g,label);
    if (!u) u = add_vertex(g,label);
    scanf(" %s",label);
    if (!strcmp(label,"/")) return;
    v = find_vertex(g,label);
    if (!v) v = add_vertex(g,label);
    if (g->weighted) scanf("%d", &weight);
    else weight = 1;
    add_edge(g,u,v,g->directed,weight);
}

void read_graph(graph *g) {
    int i, nedges;

    empty_graph(g);

    DEBUG("Unesite broj bridova: ");
    scanf("%d",&nedges);

    for (i=0; i<nedges; i++) {
        DEBUG("Unesite oznake vrhova brida %d ",i+1);
        if (g->weighted) DEBUG("i njegovu tezinu ");
        insert_edge_vertices(g);
    }
}

void print_graph(graph *g) {
    vertex *v;
    edge *e;
    int i;

    for (i=0; i<g->nvertices; i++) {
        v = g->vertices[i];
        printf("%s: ",v->label);
        for (e=v->edges; e; e=e->next) {
            printf(" %s",e->v->label);
            if (g->weighted) printf("(%d)",e->weight);
        }
        printf("\n");
    }
}

void initialize_attributes(graph *g) {
    vertex *v;
    int i;

    for (i=0; i<g->nvertices; i++) {
        v = g->vertices[i];
        v->distance = INITDIST;
        v->color = WHITE;
    }
}

void dfs_visit(graph *g, vertex *v, bool *cycle){
    edge *e;
    v->color = GRAY;
    for(e = v->edges; e;e=e->next){
        if(e->v->color == BLACK){
            *cycle = TRUE;
        }
        if(e->v->color==WHITE){
            dfs_visit(g, e->v, cycle);
        }
    }
    v->color = BLACK;
}
void dfs(graph *g, bool *cycle){
    int i;
    
    for(i = 0; i < g->nvertices; i++){
        if(g->vertices[i]->color == WHITE)
            dfs_visit(g, g->vertices[i], cycle);
    }
}


bool postoji_ciklus(graph *g) {
    bool cycle = FALSE; 
    dfs(g,&cycle);
    return cycle;
}

int main() {
    graph *g;
    int menu_choice;
    char c;

    g = initialize_graph(FALSE, FALSE);

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1.Postoje ciklusi? (postoji_ciklus)");
        DEBUG("\n2.Unos grafa\n3.Ispis grafa\n4.Izlaz\n");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                if (g) {
                    initialize_attributes(g);
                }
                printf("%c\n", postoji_ciklus(g) ? 'Y' : 'N');
                break;
            case 2:
                read_graph(g);
                break;
            case 3:
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



#include "graph.h"
#include "queue.h"

int is_tag(size_t vertice, size_t* tagged, int tagged_amount)
{
    for (int i=0; i<tagged_amount; i++) {
        if (tagged[i]==vertice) {
            return 1;
        }
    }
    return 0;
}

int get(struct graph_t* graph, size_t* vertice, size_t i)
{
    return gsl_spmatrix_uint_get(graph->t, *vertice, i);
}

void* st_copy(void* i)
{
    size_t* copy = malloc(sizeof(size_t)*1);
    *copy = *(size_t*) i;
    return copy;
}

void st_del(void* i)
{
    free(i);
}

int st_cmp(void* a, void* b)
{
    return (*(size_t*) a - *(size_t*) b);
}

void breadthFirstSearch(struct graph_t* graph, enum color_t* color, size_t start, enum color_t* color_found)
{
    struct queue* q = queue__empty(st_copy,st_del,st_cmp);
    queue__add(q, &start);
    size_t tagged[graph->num_vertices];
    int tagged_amount = 0;
    tagged[tagged_amount]=start;
    tagged_amount++;
    int found = 0;
    while (!queue__is_empty(q)) {
        struct element* e = queue__pop(q);
        size_t* vertice = (size_t*) element__data(e);
        if (color[*vertice] != color[start]) {
            color_found[found]=color[*vertice];
            found++;
        }
        else {
            for (size_t i=0; i < graph->num_vertices; i++) {
                if (get(graph,vertice,i)!=0 && !(is_tag(i,tagged,tagged_amount))) {
                    queue__add(q,&i);
                    tagged[tagged_amount]=i;
                    tagged_amount++;
                }
            }
        }
        element__free(e);
    }
    queue__free(q);
}

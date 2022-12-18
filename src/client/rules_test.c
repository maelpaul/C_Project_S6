#include <assert.h>
#include "rules.h"

static void test_mod_pos(void) 
{
    printf("%-40s",__func__);

    assert(mod_pos(3,4)==3);
    assert(mod_pos(4,2)==0);
    assert(mod_pos(5,2)==1);

    printf("OK\n");
}

static void test_forbidden_color(void)
{
    printf("%-40s",__func__);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_alloc(4,4);
    gsl_spmatrix_uint_set(t,0,1,1);
    gsl_spmatrix_uint_set(t,0,2,1);
    gsl_spmatrix_uint_set(t,1,0,1);
    gsl_spmatrix_uint_set(t,1,3,1);
    gsl_spmatrix_uint_set(t,2,0,1);
    gsl_spmatrix_uint_set(t,2,3,1);
    gsl_spmatrix_uint_set(t,3,1,1);
    gsl_spmatrix_uint_set(t,3,2,1);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 4;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 3;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = RED;
    colors[2] = GREEN;
    colors[3] = YELLOW;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    forbidden[0].t[YELLOW]=1;
    forbidden[1].t[RED]=1;
    
    assert(forbidden_color(0,graph,colors,forbidden, YELLOW));
    assert(forbidden_color(0,graph,colors,forbidden, BLUE));
    assert(forbidden_color(1,graph,colors,forbidden, YELLOW));
    assert(forbidden_color(1,graph,colors,forbidden, RED));
    assert(!forbidden_color(1,graph,colors,forbidden, GREEN));
    assert(!forbidden_color(1,graph,colors,forbidden, NO_COLOR));

    free(graph);
    free(colors);
    gsl_spmatrix_uint_free(t);

    printf("OK\n");
}

void rules_alltests(void)
{
    printf("%s\n",__FILE__);

    test_mod_pos();
    test_forbidden_color();
}
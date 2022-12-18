#include <assert.h>
#include "display.h"

static void test_display_square_and_torus(void) {
//    printf("%-40s",__func__);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_set(t,0,1,1);
    gsl_spmatrix_uint_set(t,0,3,1);
    gsl_spmatrix_uint_set(t,1,0,1);
    gsl_spmatrix_uint_set(t,1,2,1);
    gsl_spmatrix_uint_set(t,1,4,1);
    gsl_spmatrix_uint_set(t,2,1,1);
    gsl_spmatrix_uint_set(t,2,5,1);
    gsl_spmatrix_uint_set(t,3,0,1);
    gsl_spmatrix_uint_set(t,3,4,1);
    gsl_spmatrix_uint_set(t,3,6,1);
    gsl_spmatrix_uint_set(t,4,1,1);
    gsl_spmatrix_uint_set(t,4,3,1);
    gsl_spmatrix_uint_set(t,4,5,1);
    gsl_spmatrix_uint_set(t,4,7,1);
    gsl_spmatrix_uint_set(t,5,2,1);
    gsl_spmatrix_uint_set(t,5,4,1);
    gsl_spmatrix_uint_set(t,5,8,1);
    gsl_spmatrix_uint_set(t,6,3,1);
    gsl_spmatrix_uint_set(t,6,7,1);
    gsl_spmatrix_uint_set(t,7,4,1);
    gsl_spmatrix_uint_set(t,7,6,1);
    gsl_spmatrix_uint_set(t,7,8,1);
    gsl_spmatrix_uint_set(t,8,5,1);
    gsl_spmatrix_uint_set(t,8,7,1);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 9;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 8;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = NO_COLOR;
    colors[1] = BLUE;
    colors[2] = GREEN;
    colors[3] = RED;
    colors[4] = ORANGE;
    colors[5] = CYAN;
    colors[6] = PINK;
    colors[7] = VIOLET;
    colors[8] = YELLOW;

    graph_disp(colors, graph);

    free(colors);
    free(graph);  
    gsl_spmatrix_uint_free(t);

//    printf("OK\n");  
}

static void test_display_donut(void) {
//    printf("%-40s",__func__);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_set(t,0,1,1);
    gsl_spmatrix_uint_set(t,0,3,1);
    gsl_spmatrix_uint_set(t,1,0,1);
    gsl_spmatrix_uint_set(t,1,2,1);
    gsl_spmatrix_uint_set(t,1,4,1);
    gsl_spmatrix_uint_set(t,2,1,1);
    gsl_spmatrix_uint_set(t,2,5,1);
    gsl_spmatrix_uint_set(t,3,0,1);
    gsl_spmatrix_uint_set(t,3,4,1);
    gsl_spmatrix_uint_set(t,3,6,1);
    gsl_spmatrix_uint_set(t,4,1,1);
    gsl_spmatrix_uint_set(t,4,3,1);
    gsl_spmatrix_uint_set(t,4,5,1);
    gsl_spmatrix_uint_set(t,4,7,1);
    gsl_spmatrix_uint_set(t,5,2,1);
    gsl_spmatrix_uint_set(t,5,4,1);
    gsl_spmatrix_uint_set(t,5,8,1);
    gsl_spmatrix_uint_set(t,6,3,1);
    gsl_spmatrix_uint_set(t,6,7,1);
    gsl_spmatrix_uint_set(t,7,4,1);
    gsl_spmatrix_uint_set(t,7,6,1);
    gsl_spmatrix_uint_set(t,7,8,1);
    gsl_spmatrix_uint_set(t,8,5,1);
    gsl_spmatrix_uint_set(t,8,7,1);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 8;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 7;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = GREEN;
    colors[2] = RED;
    colors[3] = ORANGE;
    colors[4] = CYAN;
    colors[5] = PINK;
    colors[6] = VIOLET;
    colors[7] = YELLOW;

    graph_disp(colors, graph);

    free(colors);
    free(graph);  
    gsl_spmatrix_uint_free(t);

//    printf("OK\n");  
}

static void test_display_hgraph(void) {
//    printf("%-40s",__func__);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_set(t,0,1,1);
    gsl_spmatrix_uint_set(t,0,3,1);
    gsl_spmatrix_uint_set(t,1,0,1);
    gsl_spmatrix_uint_set(t,1,2,1);
    gsl_spmatrix_uint_set(t,1,4,1);
    gsl_spmatrix_uint_set(t,2,1,1);
    gsl_spmatrix_uint_set(t,2,5,1);
    gsl_spmatrix_uint_set(t,3,0,1);
    gsl_spmatrix_uint_set(t,3,4,1);
    gsl_spmatrix_uint_set(t,3,6,1);
    gsl_spmatrix_uint_set(t,4,1,1);
    gsl_spmatrix_uint_set(t,4,3,1);
    gsl_spmatrix_uint_set(t,4,5,1);
    gsl_spmatrix_uint_set(t,4,7,1);
    gsl_spmatrix_uint_set(t,5,2,1);
    gsl_spmatrix_uint_set(t,5,4,1);
    gsl_spmatrix_uint_set(t,5,8,1);
    gsl_spmatrix_uint_set(t,6,3,1);
    gsl_spmatrix_uint_set(t,6,7,1);
    gsl_spmatrix_uint_set(t,7,4,1);
    gsl_spmatrix_uint_set(t,7,6,1);
    gsl_spmatrix_uint_set(t,7,8,1);
    gsl_spmatrix_uint_set(t,8,5,1);
    gsl_spmatrix_uint_set(t,8,7,1);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 7;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 6;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = GREEN;
    colors[2] = RED;
    colors[3] = ORANGE;
    colors[4] = CYAN;
    colors[5] = PINK;
    colors[6] = VIOLET;

    graph_disp(colors, graph);

    free(colors);
    free(graph);  
    gsl_spmatrix_uint_free(t);

//    printf("OK\n");  
}

void display_alltests()
{
    //printf("%s\n",__FILE__);
    
    printf("3 3\n");
    test_display_square_and_torus();
    test_display_donut();
    test_display_hgraph();    
}

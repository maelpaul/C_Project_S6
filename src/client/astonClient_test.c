#include <assert.h>
#include "player.h"
#include "client_debug.h"

void test_play_multiple_choice(void)
{
    printf("%-40s",__func__);

    gsl_spmatrix_uint* toco = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_set(toco,0,1,1);
    gsl_spmatrix_uint_set(toco,0,3,1);
    gsl_spmatrix_uint_set(toco,1,0,1);
    gsl_spmatrix_uint_set(toco,1,2,1);
    gsl_spmatrix_uint_set(toco,1,4,1);
    gsl_spmatrix_uint_set(toco,2,1,1);
    gsl_spmatrix_uint_set(toco,2,5,1);
    gsl_spmatrix_uint_set(toco,3,0,1);
    gsl_spmatrix_uint_set(toco,3,4,1);
    gsl_spmatrix_uint_set(toco,3,6,1);
    gsl_spmatrix_uint_set(toco,4,1,1);
    gsl_spmatrix_uint_set(toco,4,3,1);
    gsl_spmatrix_uint_set(toco,4,5,1);
    gsl_spmatrix_uint_set(toco,4,7,1);
    gsl_spmatrix_uint_set(toco,5,2,1);
    gsl_spmatrix_uint_set(toco,5,4,1);
    gsl_spmatrix_uint_set(toco,5,8,1);
    gsl_spmatrix_uint_set(toco,6,3,1);
    gsl_spmatrix_uint_set(toco,6,7,1);
    gsl_spmatrix_uint_set(toco,7,4,1);
    gsl_spmatrix_uint_set(toco,7,6,1);
    gsl_spmatrix_uint_set(toco,7,8,1);
    gsl_spmatrix_uint_set(toco,8,5,1);
    gsl_spmatrix_uint_set(toco,8,7,1);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_compress(toco,GSL_SPMATRIX_CSR);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 9;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 8;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = BLUE;
    colors[2] = GREEN;
    colors[3] = RED;
    colors[4] = ORANGE;
    colors[5] = CYAN;
    colors[6] = PINK;
    colors[7] = YELLOW;
    colors[8] = YELLOW;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id,graph,colors,forbidden);

    struct move_t* move = malloc(sizeof(struct move_t)*1);
    move->c = PINK;

    struct move_t new_move = play(*move);

    assert(new_move.c = ORANGE);

    finalize();
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_play_one_choice(void)
{
    printf("%-40s",__func__);

    gsl_spmatrix_uint* toco = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_set(toco,0,1,1);
    gsl_spmatrix_uint_set(toco,0,3,1);
    gsl_spmatrix_uint_set(toco,1,0,1);
    gsl_spmatrix_uint_set(toco,1,2,1);
    gsl_spmatrix_uint_set(toco,1,4,1);
    gsl_spmatrix_uint_set(toco,2,1,1);
    gsl_spmatrix_uint_set(toco,2,5,1);
    gsl_spmatrix_uint_set(toco,3,0,1);
    gsl_spmatrix_uint_set(toco,3,4,1);
    gsl_spmatrix_uint_set(toco,3,6,1);
    gsl_spmatrix_uint_set(toco,4,1,1);
    gsl_spmatrix_uint_set(toco,4,3,1);
    gsl_spmatrix_uint_set(toco,4,5,1);
    gsl_spmatrix_uint_set(toco,4,7,1);
    gsl_spmatrix_uint_set(toco,5,2,1);
    gsl_spmatrix_uint_set(toco,5,4,1);
    gsl_spmatrix_uint_set(toco,5,8,1);
    gsl_spmatrix_uint_set(toco,6,3,1);
    gsl_spmatrix_uint_set(toco,6,7,1);
    gsl_spmatrix_uint_set(toco,7,4,1);
    gsl_spmatrix_uint_set(toco,7,6,1);
    gsl_spmatrix_uint_set(toco,7,8,1);
    gsl_spmatrix_uint_set(toco,8,5,1);
    gsl_spmatrix_uint_set(toco,8,7,1);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_compress(toco,GSL_SPMATRIX_CSR);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 9;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 8;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = BLUE;
    colors[2] = GREEN;
    colors[3] = GREEN;
    colors[4] = ORANGE;
    colors[5] = CYAN;
    colors[6] = PINK;
    colors[7] = YELLOW;
    colors[8] = YELLOW;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    struct move_t* move = malloc(sizeof(struct move_t)*1);

    initialize(id, graph, colors, forbidden);
    move->c=NO_COLOR;
    struct move_t new_move = play(*move);
    assert(new_move.c == GREEN);

    finalize();  
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_play_no_choice(void)
{
    printf("%-40s",__func__);

    gsl_spmatrix_uint* toco = gsl_spmatrix_uint_alloc(4,4);
    gsl_spmatrix_uint_set(toco,0,1,1);
    gsl_spmatrix_uint_set(toco,0,2,1);
    gsl_spmatrix_uint_set(toco,1,0,1);
    gsl_spmatrix_uint_set(toco,1,3,1);
    gsl_spmatrix_uint_set(toco,2,0,1);
    gsl_spmatrix_uint_set(toco,2,3,1);
    gsl_spmatrix_uint_set(toco,3,1,1);
    gsl_spmatrix_uint_set(toco,3,2,1);

    gsl_spmatrix_uint* t = gsl_spmatrix_uint_compress(toco,GSL_SPMATRIX_CSR);

    struct graph_t* graph = malloc(sizeof(struct graph_t)*1);
    graph->num_vertices = 4;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 3;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = RED;
    colors[2] = RED;
    colors[3] = RED;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    struct move_t* move = malloc(sizeof(struct move_t)*1);

    initialize(id, graph, colors, forbidden);
    move->c = NO_COLOR;
    struct move_t new_move = play(*move);
    assert(new_move.c == NO_COLOR);

    finalize();   
    free(move); 
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void astonClient_alltests(void)
{
    printf("%s\n",__FILE__);

    test_play_one_choice();
    test_play_multiple_choice();
    test_play_no_choice();
}
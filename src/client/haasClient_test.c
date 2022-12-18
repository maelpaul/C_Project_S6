#include <assert.h>
#include <string.h>
#include "player.h"
#include "client_debug.h"

static void test_fake_game(void)
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
    colors[5] = ORANGE;
    colors[6] = PINK;
    colors[7] = YELLOW;
    colors[8] = YELLOW;
    enum color_t* color_copy = malloc(9*sizeof(enum color_t));
    for (int i=0; i<9;i++) {
        color_copy[i]=colors[i];
    }
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id,graph,colors,forbidden);

    // printf("%d ",fake_game(GREEN));
    assert(fake_game(GREEN,10)<50);
    for (int i=0; i<9; i++) {
        assert(colors_debug()[i]==color_copy[i]);
    }
    // printf("%d ",fake_game(ORANGE));
    assert(fake_game(ORANGE,10)==100);
    for (int i=0; i<9; i++) {
        assert(colors_debug()[i]==color_copy[i]);
    }
    // printf("%d ",fake_game(RED));
    assert(fake_game(RED,10)<50);
    for (int i=0; i<9; i++) {
        assert(colors_debug()[i]==color_copy[i]);
    }

    finalize();
    free(color_copy);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

static void test_fake_update_map(void)
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

    gsl_spmatrix_uint* ttestoco = gsl_spmatrix_uint_alloc(9,9);
    gsl_spmatrix_uint_memcpy(ttestoco,toco);
    gsl_spmatrix_uint* t = gsl_spmatrix_uint_compress(toco,GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint* ttest = gsl_spmatrix_uint_compress(ttestoco,GSL_SPMATRIX_CSR);
    struct graph_t* graphtest = malloc(sizeof(struct graph_t)*1);
    graphtest->num_vertices = 9;
    graphtest->t = ttest;
    graphtest->positions[0] = 0;
    graphtest->positions[1] = 8;

    
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
    colors[5] = ORANGE;
    colors[6] = PINK;
    colors[7] = YELLOW;
    colors[8] = YELLOW;
    enum color_t* color_copy = malloc(9*sizeof(enum color_t));
    for (int i=0; i<9;i++) {
        color_copy[i]=colors[i];
    }
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<MAX_COLOR ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id,graph,colors,forbidden);

    struct move_t* move = malloc(sizeof(struct move_t)*1);
    move->c=NO_COLOR;

    fake_update_map(move,id,graphtest,color_copy);
    for (int i=0; i<9; i++) {
        assert(colors_debug()[i]==color_copy[i]);
    }

    move->c=GREEN;
    fake_update_map(move,id,graphtest,color_copy);

    assert(color_copy[0]==GREEN);
    assert(color_copy[1]==GREEN);
    assert(color_copy[2]==GREEN);

    finalize();
    free(move);
    gsl_spmatrix_uint_free(graphtest->t);
    free(graphtest);
    free(color_copy);
    gsl_spmatrix_uint_free(toco);
    gsl_spmatrix_uint_free(ttestoco);

    printf("OK\n");
}

void haasClient_alltests(void)
{
    printf("%s\n",__FILE__);

    test_fake_game();
    test_fake_update_map();
}
#include <assert.h>
#include <unistd.h>
#include "player.h"
#include "client_debug.h"

void test_play(void)
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

    int red_acc = 0;
    int green_acc = 0;
    int orange_acc = 0;
    int other_acc = 0;

    for (int j=0; j<60; j++){
        gsl_spmatrix_uint* ttest = gsl_spmatrix_uint_alloc_nzmax(9,9,81,GSL_SPMATRIX_CSR);
        gsl_spmatrix_uint_memcpy(ttest,t);

        enum color_t* color_copy = malloc(9*sizeof(enum color_t));
        for (int i=0; i<9;i++) {
            color_copy[i]=colors[i];
        }
        struct graph_t* graphtest = malloc(sizeof(struct graph_t)*1);
        graphtest->num_vertices = 9;
        graphtest->t = ttest;
        graphtest->positions[0] = 0;
        graphtest->positions[1] = 8;
        initialize(id, graphtest, color_copy, forbidden);
        struct move_t* move = malloc(sizeof(struct move_t)*1);
        move->c = CYAN;
        struct move_t new_move = play(*move);
        switch(new_move.c){
            case(RED):
                red_acc++;
                break;
            case(GREEN):
                green_acc++;
                break;
            case(ORANGE):
                orange_acc++;
                break;
            default:
                other_acc++;
                break;
        }
        free(move);
        finalize();
        if ((red_acc>0) && (green_acc>0) && (orange_acc>0))
            {
                break;
            }
        sleep(1);
    }
    assert(red_acc>0);
    assert(green_acc>0);
    assert(orange_acc>0);
    assert(other_acc==0);

    gsl_spmatrix_uint_free(graph->t);
    gsl_spmatrix_uint_free(toco);
    free(graph);
    free(colors);

    printf("OK\n");
}

void test_play2(void)
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

    struct move_t* move = malloc(sizeof(struct move_t)*1);

    initialize(id, graph, colors, forbidden);
    int i = rand() % 9;
    i--;
    move->c = i;
    struct move_t new_move = play(*move);
    assert(new_move.c == 1 || new_move.c == 2 || new_move.c == 4);

    finalize();  
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_play3(void)
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
    int i = rand() % 9;
    i--;
    move->c = i;
    struct move_t new_move = play(*move);
    assert(new_move.c == -1);

    finalize();   
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void williamsClient_alltests(void)
{
    printf("%s\n",__FILE__);
    
    printf("Next test might take up to 60 seconds.\n");
    test_play();
    test_play2();
    test_play3();
}
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "player.h"
#include "client_debug.h"

static void test_get_player_name(void)
{
    printf("%-40s",__func__);

    for (int i = 0; i < 10; ++i) {

        char const* name = get_player_name();

        assert(strcmp(name, "Sebastian Vettel") == 0 
            || strcmp(name, "Lance Stroll") == 0
            || strcmp(name, "Mick Schumacher") == 0
            || strcmp(name, "Kevin Magnussen") == 0
            || strcmp(name, "Alexander Albon") == 0
            || strcmp(name, "Nicolas Latifi") == 0);    

    }

    printf("OK\n");
}

static void test_initialize(void)
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

    // gsl_spmatrix_uint* ttest = gsl_spmatrix_uint_alloc(4,4);
    // gsl_spmatrix_uint_set(t,0,1,1);
    // gsl_spmatrix_uint_set(t,0,2,1);
    // gsl_spmatrix_uint_set(t,1,0,1);
    // gsl_spmatrix_uint_set(t,1,3,1);
    // gsl_spmatrix_uint_set(t,2,0,1);
    // gsl_spmatrix_uint_set(t,2,3,1);
    // gsl_spmatrix_uint_set(t,3,1,1);
    // gsl_spmatrix_uint_set(t,3,2,1);

    // gsl_spmatrix_uint* ttest = gsl_spmatrix_uint_alloc(4,4);
    // gsl_spmatrix_uint_memcpy(ttest,t);
    
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
    for (int i = 0; i<NUM_PLAYERS ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id, graph, colors, forbidden);

    assert(id_debug()==0);
    assert(graph_debug()->num_vertices==4);
    assert(graph_debug()->positions[0]==0);
    assert(graph_debug()->positions[1]==3);
    // assert(graph_debug()->t==ttest);
    assert(gsl_spmatrix_uint_get(graph_debug()->t,0,1)==1);
    assert(colors_debug()[0]==BLUE);
    assert(colors_debug()[1]==RED);
    assert(colors_debug()[2]==GREEN);
    assert(colors_debug()[3]==YELLOW);

    finalize();
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_update_map(void)
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
    colors[2] = GREEN;
    colors[3] = YELLOW;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<NUM_PLAYERS ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id, graph, colors, forbidden);

    struct move_t* move = malloc(sizeof(struct move_t)*1);
    move->c = RED;

    update_map(move,id);

    assert(colors_debug()[0] = RED);
    assert(colors_debug()[1] = RED);
    assert(colors_debug()[2] = GREEN);
    assert(colors_debug()[3] = YELLOW);

    finalize();
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_update_map2(void)
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
    colors[1] = BLUE;
    colors[2] = GREEN;
    colors[3] = YELLOW;
    struct color_set_t forbidden[NUM_PLAYERS];
    for (int i = 0; i<NUM_PLAYERS ; i++) {
        forbidden[0].t[i]=0; 
        forbidden[1].t[i]=0;
    }
    size_t id = 0;

    initialize(id, graph, colors, forbidden);

    struct move_t* move = malloc(sizeof(struct move_t)*1);
    move->c = GREEN;

    update_map(move,id);

    assert(colors_debug()[0] = GREEN);
    assert(colors_debug()[1] = GREEN);
    assert(colors_debug()[2] = GREEN);
    assert(colors_debug()[3] = YELLOW);

    finalize();
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

static void test_update_map3(void)
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

    initialize(id, graph, colors, forbidden);

    struct move_t* move = malloc(sizeof(struct move_t)*1);
    move->c = CYAN;

    update_map(move,1);

    finalize();
    free(move);
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");
}

void test_forbidden(void) {
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

    initialize(id, graph, colors, forbidden);

    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        for (int j = 0; j < MAX_COLOR; ++j) {
            assert(forbidden_debug()[i].t[j] == forbidden[i].t[j]);                    
        }         
    }

    finalize();  
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");  
}

static void test_counter(void)
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

    initialize(id, graph, colors, forbidden);

    assert(bfs_counter(0,graph_debug(),colors_debug())==2);
    assert(bfs_counter(1,graph_debug(),colors_debug())==2);

    struct move_t move = {GREEN};
    play(move);

    assert(bfs_counter(0,graph_debug(),colors_debug())==3);

    finalize();
    gsl_spmatrix_uint_free(toco);

    printf("OK\n");  
}

void client_alltests(void) 
{
    printf("%s\n",__FILE__);

    test_get_player_name();
    test_initialize();
    test_update_map();
    test_update_map2();
    test_update_map3();
    test_forbidden();
    test_counter();
}

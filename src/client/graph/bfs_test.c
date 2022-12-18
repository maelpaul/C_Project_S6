#include "bfs.h"
#include <assert.h>

static void test_bfs_unicolor(void) 
{
    printf("%-40s",__func__);

    gsl_spmatrix_uint* t2 = gsl_spmatrix_uint_alloc(4,4);
    gsl_spmatrix_uint_set(t2,0,1,1);
    gsl_spmatrix_uint_set(t2,0,2,1);
    gsl_spmatrix_uint_set(t2,1,0,1);
    gsl_spmatrix_uint_set(t2,1,3,1);
    gsl_spmatrix_uint_set(t2,2,0,1);
    gsl_spmatrix_uint_set(t2,2,3,1);
    gsl_spmatrix_uint_set(t2,3,1,1);
    gsl_spmatrix_uint_set(t2,3,2,1);

    struct graph_t graph2 = {4,t2,{0,3}};
    enum color_t color2[4] = {RED,RED,RED,RED};
    enum color_t found2[]= {NO_COLOR,NO_COLOR,NO_COLOR,NO_COLOR};
    breadthFirstSearch(&graph2,color2,0,found2);
    
    assert(found2[0]==NO_COLOR);
    assert(found2[1]==NO_COLOR);
    assert(found2[2]==NO_COLOR);
    assert(found2[3]==NO_COLOR);

    gsl_spmatrix_uint_free(t2);

    printf("OK\n");
}

static void test_bfs_colormix(void) 
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

    struct graph_t graph = {4,t,{0,3}};
    enum color_t color[4] = {BLUE,BLUE,GREEN,RED};
    enum color_t found[2]= {};
    breadthFirstSearch(&graph,color,0,found);
    
    assert(found[0]==GREEN);
    assert(found[1]==RED);

    gsl_spmatrix_uint_free(t);

    printf("OK\n");
}

static void test_bfs_fully_multicolor(void) 
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

    struct graph_t graph = {4,t,{0,3}};
    enum color_t color[4] = {BLUE,RED,GREEN,YELLOW};
    enum color_t found[2]= {};
    breadthFirstSearch(&graph,color,0,found);
    
    assert(found[0]==RED);
    assert(found[1]==GREEN);

    gsl_spmatrix_uint_free(t);

    printf("OK\n");
}

static void test_bfs_colormix_2(void)
{
    printf("%-40s",__func__);

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
    colors[0] = BLUE;
    colors[1] = BLUE;
    colors[2] = GREEN;
    colors[3] = RED;
    colors[4] = ORANGE;
    colors[5] = CYAN;
    colors[6] = PINK;
    colors[7] = YELLOW;
    colors[8] = YELLOW;
    size_t id = 0;
    enum color_t* found = malloc(sizeof(enum color_t)*graph->num_vertices);
    for(size_t i = 0; i<graph->num_vertices;i++) {
        found[i]=NO_COLOR;
    }
    breadthFirstSearch(graph,colors,graph->positions[id],found);

    assert(found[0]==RED);
    assert(found[1]==GREEN);
    assert(found[2]==ORANGE);

    free(found);
    free(colors);
    free(graph);
    gsl_spmatrix_uint_free(t);
    
    printf("OK\n");
}

static void test_del_and_cmp(void)
{
    size_t* a = malloc(sizeof(size_t));
    st_del(a);

    size_t* b = malloc(sizeof(size_t));
    *b = 10;
    size_t* c = malloc(sizeof(size_t));
    *c = 5;

    assert(st_cmp(b, c) == 5);

    free(b);
    free(c);
}

void bfs_alltests()
{
    printf("%s\n",__FILE__);

    test_bfs_unicolor();
    test_bfs_colormix();
    test_bfs_fully_multicolor();
    test_bfs_colormix_2();
    test_del_and_cmp();
}

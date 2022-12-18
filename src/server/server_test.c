#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "server.h"
#include "../display/display.h"

static void test_file(void)
{
  printf("%-40s", __func__);
  printf("\tOK\n");
}

static void test_filter_square(void)
{
  printf("%-40s", __func__);

  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      assert(filter_square(i, j, 10));
    }
  }
  printf("\tOK\n");
}

static void test_filter_donut_on_wrong_sized_board(void)
{
  printf("%-40s", __func__);
  int m = 8;
  assert(filter_donut(0, 0, m) == -1);
  printf("\tOK\n");
}

static void test_filter_donut_on_right_sized_board(void)
{
  printf("%-40s", __func__);
  int m = 9;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (i > 2 && i < 6 && j > 2 && j < 6){
        assert(!filter_donut(i, j, m));
      }
      else {
        assert(filter_donut(i, j, m));
      }
    }
  }
  printf("\tOK\n");
}

static void test_filter_hgraph_on_wrong_sized_board(void)
{
  printf("%-40s", __func__);
  int m = 8;
  assert(filter_hgraph(0, 0, m) == -1);
  printf("\tOK\n");
}

static void test_filter_hgraph_on_right_sized_board(void)
{
  printf("%-40s", __func__);
  int m = 9;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (j > 2 && j < 6 && i < 3){
        assert(!filter_hgraph(i, j, m));
      }
      else if (j > 2 && j < 6 && i > 5) {
        assert(!filter_hgraph(i, j, m));
      }
      else {
        assert(filter_hgraph(i, j, m));
      }
    }
  }
  printf("\tOK\n");
}

static void test_filter_torus(void)
{
  printf("%-40s", __func__);

  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      assert(filter_square(i, j, 10));
    }
  }
  printf("\tOK\n");
}


/*static void test_generate_square(void)
{
  printf("%-40s", __func__);
  size_t position[2] = {1, 5};
  struct graph_t* g = generate_square(10, position);
  gsl_spmatrix_uint_free(g->t);
  free(g);
  printf("\tOK\n");
}
*/

static void test_is_corner_on_square_graph(void)
{
  printf("%-40s", __func__);
  int m = 8;
  int i = 0;
  int j = 0;
  assert(is_corner(i, j, m, SQUARE) == UP_LEFT1);
  i = m-1;
  assert(is_corner(i, j, m, SQUARE) == DOWN_LEFT1);
  j = m-1;
  assert(is_corner(i, j, m, SQUARE) == DOWN_RIGHT1);
  i = 0;
  assert(is_corner(i, j, m, SQUARE) == UP_RIGHT1);
  i = 1;
  j = 4; 
  assert(is_corner(i, j, m, SQUARE) == NONE_CORNER);
  printf("\tOK\n");
}

static void test_is_corner_on_torus_graph(void)
{
  printf("%-40s", __func__);
  int m = 8;
  int i = 0;
  int j = 0;
  assert(is_corner(i, j, m, TORUS) == NONE_CORNER);
  i = m-1;
  assert(is_corner(i, j, m, TORUS) == NONE_CORNER);
  j = m-1;
  assert(is_corner(i, j, m, TORUS) == NONE_CORNER);
  i = 0;
  assert(is_corner(i, j, m, TORUS) == NONE_CORNER);
  i = 1;
  j = 4; 
  assert(is_corner(i, j, m, TORUS) == NONE_CORNER);
  printf("\tOK\n");
}

static void test_is_corner_on_hgraph_graph(void)
{
  printf("%-40s", __func__);
  int m = 9;
  int i = 0;
  int j = 0;
  assert(is_corner(i, j, m, HGRAPH) == UP_LEFT1);
  i = m-1;
  assert(is_corner(i, j, m, HGRAPH) == DOWN_LEFT1);
  j = m-1;
  assert(is_corner(i, j, m, HGRAPH) == DOWN_RIGHT1);
  i = 0;
  assert(is_corner(i, j, m, HGRAPH) == UP_RIGHT1);
  i = 1;
  j = 4; 
  assert(is_corner(i, j, m, HGRAPH) == NONE_CORNER);
  int third = 3;
  i = third-1;
  j = third-1;
  assert(is_corner(i, j, m, HGRAPH) == UP_LEFT2);
  i = 2*third-1;
  assert(is_corner(i, j, m, HGRAPH) == DOWN_LEFT2);
  j = 2*third-1;
  assert(is_corner(i, j, m, HGRAPH) == DOWN_RIGHT2);
  i = third-1;
  assert(is_corner(i, j, m, HGRAPH) == UP_RIGHT2);
  printf("\tOK\n");
}

static void test_is_border_on_square_graph(void)
{
  printf("%-40s", __func__);
  int m = 8;
  int i = 0;
  int j = 0;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, SQUARE) == LEFT_IN);
  }
  i = m-1;
  for (int j = 1; j < m-1; ++j) {
    assert(is_border(i, j, m, SQUARE) == DOWN_IN);
  }
  j = m-1;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, SQUARE) == RIGHT_IN);
  }
  i = 0;
  for (int j = 1; j < m-1; ++j) {
    assert(is_border(i, j, m, SQUARE) == UP_IN);
  }
  i = 1;
  j = 4; 
  assert(is_border(i, j, m, SQUARE) == NONE_LINE);
  printf("\tOK\n");
}

static void test_is_border_on_donut_graph(void)
{
  printf("%-40s", __func__);
  int m = 9;
  int i = 0;
  int j = 0;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, DONUT) == LEFT_IN);
  }
  i = m-1;
  for (int j = 1; j < m-1; ++j) {
    assert(is_border(i, j, m, DONUT) == DOWN_IN);
  }
  j = m-1;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, DONUT) == RIGHT_IN);
  }
  i = 0;
  for (int j = 1; j < m-1; ++j) {
    assert(is_border(i, j, m, DONUT) == UP_IN);
  }
  i = 1;
  j = 4; 
  assert(is_border(i, j, m, DONUT) == NONE_LINE);
  int third = m/3;
  i = third;
  j = third;
  for (int i = third; i < 2*third-1; ++i) {
    assert(is_border(i, j, m, DONUT) == LEFT_OUT);
  }
  i = 2*third;
  for (int j = third; j < 2*third-1; ++j) {
    assert(is_border(i, j, m, DONUT) == DOWN_OUT);
  }
  j = 2*third;
  for (int i = third; i < 2*third-1; ++i) {
    assert(is_border(i, j, m, DONUT) == RIGHT_OUT);
  }
  i = third-1;
  for (int j = third; j < 2*third-1; ++j) {
    assert(is_border(i, j, m, DONUT) == UP_OUT);
  }
  printf("\tOK\n");
}

static void test_is_border_on_hgraph_graph(void)
{
  int m = 9;
  int i = 0;
  int j = 0;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, HGRAPH) == LEFT_IN);
  }
  j = m-1;
  for (int i = 1; i < m-1; ++i) {
    assert(is_border(i, j, m, HGRAPH) == RIGHT_IN);
  }
  int third = m/3;
  j = third-1;
  for (int i = 1; i < third; ++i) {
    assert(is_border(i, j, m, HGRAPH) == LEFT_OUT);
  }
  for (int i = 2*third; i < m-1; ++i) {
    assert(is_border(i, j, m, HGRAPH) == LEFT_OUT);
  }
  j = 2*third;
  for (int i = 1; i < third; ++i) {
    assert(is_border(i, j, m, HGRAPH) == RIGHT_OUT);
  }
  for (int i = 2*third; i < m-1; ++i) {
    assert(is_border(i, j, m, HGRAPH) == RIGHT_OUT);
  }
  i = 0;
  for (int j = 1; j < third-1; ++j) {
    assert(is_border(i, j, m, HGRAPH) == UP_IN);
  }
  for (int j = 2*third+1; j < m-1; ++j) {
    assert(is_border(i, j, m, HGRAPH) == UP_IN);
  }
  i = third;
  for (int j = third; j < 2*third; ++j) {
    assert(is_border(i, j, m, HGRAPH) == UP_IN);
  }
  i = m-1;
  for (int j = 1; j < third-1; ++j) {
    assert(is_border(i, j, m, HGRAPH) == DOWN_IN);
  }
  for (int j = 2*third+1; j < m-1; ++j) {
    assert(is_border(i, j, m, HGRAPH) == DOWN_IN);
  }
  i = third*2-1;
  for (int j = third; j < 2*third; ++j) {
    assert(is_border(i, j, m, HGRAPH) == DOWN_IN);
  }
}

static void test__neighbours_on_up_in()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 0;
  int j = 2;
  neighbour_border(i, j, m, UP_IN, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_left_in() 
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 2;
  int j = 0;
  neighbour_border(i, j, m, LEFT_IN, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_right_in()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 1;
  int j = 8;
  neighbour_border(i, j, m, RIGHT_IN, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_down_in()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 8;
  int j = 1;
  neighbour_border(i, j, m, DOWN_IN, &n);
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_up_out()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 2;
  int j = 3;
  neighbour_border(i, j, m, UP_OUT, &n);
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_left_out()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 3;
  int j = 2;
  neighbour_border(i, j, m, LEFT_OUT, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_right_out()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 5;
  int j = 6;
  neighbour_border(i, j, m, RIGHT_OUT, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_down_out()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 6;
  int j = 3;
  neighbour_border(i, j, m, DOWN_OUT, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  printf("\tOK\n");
}

static void test__neighbours_on_intern()
{
  printf("%-40s", __func__);
  struct neighbours n = {-1, -1, -1, -1};
  int m = 9;
  int i = 2;
  int j = 2;
  neighbour_intern(i, j, m, &n);
  assert(n.down = convert_square_to_vertice(i + 1, j, m));
  assert(n.up = convert_square_to_vertice(i - 1, j, m));
  assert(n.right = convert_square_to_vertice(i, j + 1, m));
  assert(n.left = convert_square_to_vertice(i, j - 1, m));
  printf("\tOK\n");
}

static void test_random_dyeing() {
  printf("%-40s", __func__);
  int res = random_dyeing(1, 2, 9);
  assert((res >=0) && (res <= MAX_COLOR));
  printf("\tOK\n");  
}

static void test_cyclic_dyeing(void) 
{
  printf("%-40s", __func__);
  int m = 9;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      assert(cyclic_dyeing(i, j, m) == convert_square_to_vertice(i, j, m)%MAX_COLOR);
    }
  }
  printf("\tOK\n");
}

static void test_corners() {
  printf("%-40s", __func__);
  
  int m = 9;

  struct neighbours ul1 = {-1, -1, -1, -1};
  neighbour_corner(0, 0, m, UP_LEFT1, &ul1);
  assert(ul1.up == -1);
  assert(ul1.down == m);
  assert(ul1.left == -1);
  assert(ul1.right == 1);

  struct neighbours ur1 = {-1, -1, -1, -1};
  neighbour_corner(0, m-1, m, UP_RIGHT1, &ur1);
  assert(ur1.up == -1);
  assert(ur1.down == 2*m-1);
  assert(ur1.left == m-2);
  assert(ur1.right == -1);
  
  struct neighbours dl1 = {-1, -1, -1, -1};
  neighbour_corner(m-1, 0, m, DOWN_LEFT1, &dl1);
  assert(dl1.up == (m-2)*m);
  assert(dl1.down == -1);
  assert(dl1.left == -1);
  assert(dl1.right == (m-1)*m+1);
  
  struct neighbours dr1 = {-1, -1, -1, -1};
  neighbour_corner(m-1, m-1, m, DOWN_RIGHT1, &dr1);
  assert(dr1.up == (m-1)*m-1);
  assert(dr1.down == -1);
  assert(dr1.left == m*m-2);
  assert(dr1.right == -1);

  struct neighbours ul2 = {-1, -1, -1, -1};
  neighbour_corner(0, m/3-1, m, UP_LEFT2, &ul2);
  assert(ul2.up == -1);
  assert(ul2.down == m+m/3-1);
  assert(ul2.left == m/3-2);
  assert(ul2.right == -1);

  struct neighbours ur2 = {-1, -1, -1, -1};
  neighbour_corner(0, m-m/3, m, UP_RIGHT2, &ur2);
  assert(ur2.up == -1);
  assert(ur2.down == 2*m-m/3);
  assert(ur2.left == -1);
  assert(ur2.right == m-m/3+1);
  
  struct neighbours dl2 = {-1, -1, -1, -1};
  neighbour_corner(m-1, m/3-1, m, DOWN_LEFT2, &dl2);
  assert(dl2.up == (m-2)*m+m/3-1);
  assert(dl2.down == -1);
  assert(dl2.left == (m-1)*m+m/3-2);
  assert(dl2.right == -1);
  
  struct neighbours dr2 = {-1, -1, -1, -1};
  neighbour_corner(m-1, m-m/3, m, DOWN_RIGHT2, &dr2);
  assert(dr2.up == (m-1)*m-m/3);
  assert(dr2.down == -1);
  assert(dr2.left == -1);
  assert(dr2.right == m*m-m/3+1);

  struct neighbours n = {-1, -1, -1, -1};
  neighbour_corner(1, 1, m, NONE_CORNER, &n);
  assert(n.up == -1);
  assert(n.down == -1);
  assert(n.left == -1);
  assert(n.right == -1);

  printf("\tOK\n");  
}

static void test_generate_board_square_graph_random_dyeing() {
  printf("%-40s", __func__);
  size_t p[NUM_PLAYERS] = {0, 80};
  struct board* b = malloc(sizeof(struct board));
  b = generate_board(b, SQUARE, 9, p, random_dyeing, filter_square, nzmax_square);
  graph_disp(b->c, b->g);
  free_board(b);
  printf("\tOK\n");  
}

static void test_generate_board_hgraph_graph_random_dyeing() {
  //printf("%-40s", __func__);
  size_t p[NUM_PLAYERS] = {0, 80};
  struct board* b = malloc(sizeof(struct board));
  b = generate_board(b, HGRAPH, 9, p, cyclic_dyeing, filter_hgraph, nzmax_hgraph);
  printf("9 9\n");
  graph_disp(b->c, b->g);
  free_board(b);
  //printf("\tOK\n");  
}

static void test_generate_board_donut_graph_random_dyeing() {
  printf("%-40s", __func__);
  size_t p[NUM_PLAYERS] = {0, 80};
  struct board* b = malloc(sizeof(struct board));
  b = generate_board(b, DONUT, 9, p, random_dyeing, filter_donut, nzmax_donut);
  graph_disp(b->c, b->g);
  free_board(b);
  printf("\tOK\n");  
}

static void test_generate_board_torus_graph_random_dyeing() {
  printf("%-40s", __func__);
  size_t p[NUM_PLAYERS] = {0, 80};
  struct board* b = malloc(sizeof(struct board));
  b = generate_board(b, TORUS, 9, p, random_dyeing, filter_torus, nzmax_torus);
  graph_disp(b->c, b->g);
  free_board(b);
  printf("\tOK\n");  
}

static void test_del_and_cmp_size_t(void)
{
  printf("%-40s", __func__);
  size_t* a = malloc(sizeof(size_t));
  st_del_server(a);

  size_t* b = malloc(sizeof(size_t));
  *b = 10;
  size_t* c = malloc(sizeof(size_t));
  *c = 5;

  assert(st_cmp_server(b, c) == 5);
  size_t* d = st_copy_server(b);
  st_del_server(b);
  assert(st_cmp_server(d, c) == 5);
  free(c);
  free(d);
  printf("\tOK\n"); 
}

static void test_update_graph(void)
{
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

    struct graph_t* graph = malloc(sizeof(struct graph_t));
    graph->num_vertices = 9;
    graph->t = t;
    graph->positions[0] = 0;
    graph->positions[1] = 8;
    enum color_t* colors = malloc(sizeof(enum color_t)*graph->num_vertices);
    colors[0] = BLUE;
    colors[1] = NO_COLOR;
    colors[2] = GREEN;
    colors[3] = RED;
    colors[4] = ORANGE;
    colors[5] = CYAN;
    colors[6] = PINK;
    colors[7] = NO_COLOR;
    colors[8] = VIOLET;
  
    printf("3 3\n");
    graph_disp(colors, graph);
    gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(graph->t, GSL_SPMATRIX_CSR);  
    gsl_spmatrix_uint_free(graph->t);
    graph->t = csr;
    struct board* b = malloc(sizeof(struct board));
    b->g = graph;
    b->c = colors;
    struct move_t test = {RED};
    update_graph_server(&test, 0, b);
    graph_disp(b->c, b->g);
    test.c = PINK;
    update_graph_server(&test, 1, b);
    graph_disp(b->c, b->g);
    test.c = ORANGE;
    update_graph_server(&test, 0, b);
    graph_disp(b->c, b->g);
    free(colors);
    gsl_spmatrix_uint_free(graph->t);
    free(graph);  
    free(b);

//    printf("OK\n");  
}

static void test_update_h_graph_with_random_dyeing(void)
{
//    printf("%-40s",__func__);

  size_t p[NUM_PLAYERS] = {0, 80};
  struct board* b = malloc(sizeof(struct board));
  b = generate_board(b, HGRAPH, 9, p, cyclic_dyeing, filter_hgraph, nzmax_hgraph);
  printf("9 9\n");
  graph_disp(b->c, b->g);
  struct move_t test = {RED};
  update_graph_server(&test, 0, b);
  graph_disp(b->c, b->g);
  test.c = PINK;
  update_graph_server(&test, 1, b);
  graph_disp(b->c, b->g);
  test.c = GREEN;
  update_graph_server(&test, 0, b);
  graph_disp(b->c, b->g);
  free_board(b);
//    printf("OK\n");  
}

void server_alltests(void) 
{
    printf("%s\n",__FILE__);

    test_file();
    test_is_corner_on_square_graph();
    test_is_corner_on_torus_graph();
    test_is_corner_on_hgraph_graph();
    test_is_border_on_square_graph();
    test_is_border_on_donut_graph();
    test_is_border_on_hgraph_graph();
    test_filter_square();
    test_filter_donut_on_wrong_sized_board();
    test_filter_donut_on_right_sized_board();
    test_filter_hgraph_on_wrong_sized_board();
    test_filter_hgraph_on_right_sized_board();
    test_filter_torus();
    test__neighbours_on_up_in();
    test__neighbours_on_left_in();
    test__neighbours_on_right_in();
    test__neighbours_on_down_in();
    test__neighbours_on_up_out();
    test__neighbours_on_left_out();
    test__neighbours_on_right_out();
    test__neighbours_on_down_out();
    test__neighbours_on_intern();
    test_random_dyeing();
    test_cyclic_dyeing();
    test_corners();
    test_generate_board_square_graph_random_dyeing();
    test_generate_board_torus_graph_random_dyeing();
    test_generate_board_donut_graph_random_dyeing();
    test_generate_board_hgraph_graph_random_dyeing();
    test_del_and_cmp_size_t();
    test_update_graph();
    test_update_h_graph_with_random_dyeing();
}

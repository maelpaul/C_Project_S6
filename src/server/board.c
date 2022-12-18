#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

#include "board.h"

int filter_square(int x, int y, int m) 
{
    x++;
    y++;
    m++;
    return 1;
}

int filter_donut(int x, int y, int m) 
{
    if (m%3 != 0 || (x > m) || (y > m)) {
        return -1;
    }
    int third = m/3;
    int boundary_x = (x >= third) && (x < third*2);
    int boundary_y = (y >= third) && (y < third*2);
    return !(boundary_x && boundary_y);
}  

int filter_hgraph(int x, int y, int m)
{
    if (m%3 != 0 || (x > m) || (y > m)) {
        return -1;
    }
    int third = m/3;
    int boundary_y = (y >= third) && (y < third*2);
    int boundary_x = (x >= 0) && (x < third);
    int first_square = boundary_x && boundary_y;
    int boundary_y2 = (y >= third) && (y < third*2);
    int boundary_x2 = (x >= 2*third) && (x < m);
    int second_square = boundary_x2 && boundary_y2;
    return !(first_square || second_square);
}

int filter_torus(int x, int y, int m) 
{
    x++;
    y++;
    m++;
    return 1;
}

size_t nzmax_square(size_t m)
{
    return ( 4 * ( m - 2 ) * ( m - 2 ) + 3 * ( m - 2 ) * 4 + 2 * 4 );
}

size_t nzmax_donut(size_t m)
{
    return 4 * ( 2 + ( ( m / 3 ) - 1 ) * 2 * 3 + ( 4 * ( m / 3 ) - 1 ) * ( ( m / 3 ) - 1 ) + ( m / 3 ) * 2 * 3 + 4 * ( ( m / 3 ) - 1 ) * ( ( m / 3 ) - 1 ) ); 
}

size_t nzmax_hgraph(size_t m)
{
    if (m >= 3 ) {
        return ( 4 * 2 + ( m - 2 ) * 3 ) + 2 * ( (m / 3 ) - 2) + 2 * ((m / 3 ) - 1 + 4 * ( m - 2 * m / 2 - 2 )) * 2 + 2 * (m / 3) * 3 + 4 * (m / 3 * ( m / 3 - 2));
    } else {
        return 4 * m * m;
    }
}

size_t nzmax_torus(size_t m)
{
    return (4*m*m);
}

int convert_square_to_vertice(int i, int j, int m) {
	return i*m + j;
}

void add_corner_if_exist(int i, int j, enum corner *c, int value_expected_i, int value_expected_j, enum corner c_expected)
{
    enum corner new_c = ((i == value_expected_i) && (j == value_expected_j) ) ? c_expected : *c;
    *c = new_c;
}


//Does this function need to check if m is a multiple of three ?
enum corner is_corner(int i, int j, int m, enum graph_type_t t)
{
    enum corner c = NONE_CORNER;
    int third = m/3;
    switch (t) {
    case SQUARE:
    case DONUT:
        add_corner_if_exist(i, j, &c, 0, m-1, UP_RIGHT1);
        add_corner_if_exist(i, j, &c, 0, 0, UP_LEFT1);
        add_corner_if_exist(i, j, &c, m-1, 0, DOWN_LEFT1);
        add_corner_if_exist(i, j, &c, m-1, m-1, DOWN_RIGHT1);
        return c;
        break;
    case HGRAPH:
        add_corner_if_exist(i, j, &c, 0, m-1, UP_RIGHT1);
        add_corner_if_exist(i, j, &c, 0, 0, UP_LEFT1);
        add_corner_if_exist(i, j, &c, m-1, 0, DOWN_LEFT1);
        add_corner_if_exist(i, j, &c, m-1, m-1, DOWN_RIGHT1);
        add_corner_if_exist(i, j, &c, third-1, 2*third-1, UP_RIGHT2);
        add_corner_if_exist(i, j, &c, third-1, third-1, UP_LEFT2);
        add_corner_if_exist(i, j, &c, 2*third-1, third-1, DOWN_LEFT2);
        add_corner_if_exist(i, j, &c, 2*third-1, 2*third-1, DOWN_RIGHT2);
        return c;
        break;
    default:
        return c;
        break;
    }
}

enum line is_border(int i, int j, int m, enum graph_type_t t)
{
    int i_min = 0;
    int j_min = 0;
    int i_max = m-1;
    int j_max = m-1;
    int third = m/3;
    int test_first_line_right_out = 0;
    int test_second_line_right_out = 0;
    int test_first_line_left_out = 0;
    int test_second_line_left_out = 0;
    int test_first_line_up_in = 0;
    int test_second_line_up_in = 0;
    int test_third_line_up_in = 0;
    int test_first_line_down_in = 0;
    int test_second_line_down_in = 0;
    int test_third_line_down_in = 0;
    enum line l = NONE_LINE;
    switch (t)
    {
    case SQUARE:
        l = ((i_min == i) && (j_min < j) && (j < j_max)) ? UP_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_max)) ? RIGHT_IN : l;
        l = ((i_max == i) && (j_min < j) && (j < j_max)) ? DOWN_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_min)) ? LEFT_IN : l;
        return l;
        break;
    case DONUT:
        l = ((i_min == i) && (j_min < j) && (j < j_max)) ? UP_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_max)) ? RIGHT_IN : l;
        l = ((i_max == i) && (j_min < j) && (j < j_max)) ? DOWN_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_min)) ? LEFT_IN : l;
        i_min = third;
        j_min = third;
        i_max = 2*third;
        j_max = 2*third;
        l = ((i_min-1 == i) && (j_min <= j) && (j < j_max)) ? UP_OUT: l;
        l = ((i_min <= i) && (i < i_max) && (j == j_max)) ? RIGHT_OUT : l;
        l = ((i_max == i) && (j_min <= j) && (j < j_max)) ? DOWN_OUT : l;
        l = ((i_min <= i) && (i < i_max) && (j == j_min)) ? LEFT_OUT : l;
        return l;
        break;  
    case HGRAPH:
        test_first_line_right_out = ((0 < i) && (i < third) && (j == 2*third));
        test_second_line_right_out = ((2*third <= i) && (i < m-1) && (j == 2*third));
        test_first_line_left_out = ((0 < i) && (i < third) && (j == third-1));
        test_first_line_up_in = ((0 < j) && (j < third-1) && (i == 0));
        test_second_line_up_in = ((2*third < j) && (j < m-1) && (i == 0));
        test_third_line_up_in = ((third <= j) && (j < 2*third) && (i == third));
        test_first_line_down_in = ((0 < j) && (j < third-1) && (i == m-1));
        test_second_line_down_in = ((2*third < j) && (j < m-1) && (i == m-1));
        test_third_line_down_in = ((third <= j) && (j < 2*third) && (i == 2*third-1));
        test_second_line_left_out = ((2*third <= i) && (i < m-1) && (j == third-1));
        l = (test_first_line_right_out || test_second_line_right_out) ? RIGHT_OUT : l;
        l = (test_first_line_left_out || test_second_line_left_out) ? LEFT_OUT : l;
        l = (test_first_line_up_in || test_second_line_up_in || test_third_line_up_in) ? UP_IN : l;
        l = (test_first_line_down_in || test_second_line_down_in || test_third_line_down_in) ? DOWN_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_max)) ? RIGHT_IN : l;
        l = ((i_min < i) && (i < i_max) && (j == j_min)) ? LEFT_IN : l;
        return l;
        break;
    default:
        return l;
        break;
    }
}

void neighbour_border(int i, int j, int m, enum line l, struct neighbours* n)
{
    switch(l)
    {
    case UP_IN:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case LEFT_IN:
        n->up = convert_square_to_vertice(i - 1, j, m);
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case RIGHT_IN:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        break;
    case DOWN_IN:
        n->up = convert_square_to_vertice(i - 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case UP_OUT:
        n->up = convert_square_to_vertice(i - 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case LEFT_OUT:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        break;
    case RIGHT_OUT:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case DOWN_OUT:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    default:
        break;
    }
}

void neighbour_corner(int i, int j, int m, enum corner c, struct neighbours* n)
{
    switch(c)
    {
    case UP_RIGHT1:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        break;
    case UP_RIGHT2:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case UP_LEFT1:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->right = convert_square_to_vertice(i, j + 1, m);
        break;
    case UP_LEFT2:
        n->down = convert_square_to_vertice(i + 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        break;
    case DOWN_RIGHT1:
        n->up = convert_square_to_vertice(i - 1, j, m);
        n->left = convert_square_to_vertice(i, j - 1, m);
        break;
    case DOWN_RIGHT2:
        n->right = convert_square_to_vertice(i, j + 1, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        break;
    case DOWN_LEFT1:
        n->right = convert_square_to_vertice(i, j + 1, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        break;
    case DOWN_LEFT2:
        n->left = convert_square_to_vertice(i, j - 1, m);
        n->up = convert_square_to_vertice(i - 1, j, m);
        break;
    default:
        break;
    }
}

void neighbour_intern(int i, int j, int m, struct neighbours* n)
{
    n->down = convert_square_to_vertice((i + 1 + m)%m, j, m);
    n->up = convert_square_to_vertice((i - 1 + m)%m, j, m);
    n->left = convert_square_to_vertice(i, (j - 1 + m)%m, m);
    n->right = convert_square_to_vertice(i, (j + 1 + m)%m, m);
}

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

int random_dyeing(int i, int j, int m) 
{
    int n = 0;
    i++;
    j++;
    m++;
    n = rand() % (MAX_COLOR);
    return n;
}

int cyclic_dyeing(int i, int j, int m) 
{
    int s = convert_square_to_vertice(i, j, m);
    return s%MAX_COLOR;
}

int modulo(int i, int m) {
    if (i < 0) {
        return i%m +m;
    } else {
        return i%m;
    }
}

struct board *generate_board(struct board* b, enum graph_type_t kind, int m, size_t position[], dyeing_t d, filter_t f, nzmax_t nzmax)
{
    struct graph_t* g = malloc(sizeof(struct graph_t));
    gsl_spmatrix_uint* t_coo =  gsl_spmatrix_uint_alloc_nzmax(m*m, m*m, nzmax(m), GSL_SPMATRIX_COO);
    g->num_vertices = m*m;
    g->t = t_coo;
    g->positions[0] = position[0];
    g->positions[1] = m*m-1;
    int idx_color = 0;
    enum color_t* colors = malloc(m*m*sizeof(enum color_t));
    b->g = g;
    b->c = colors;
    srand(current_timestamp());
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f(i, j, m)) {
                int s_current = convert_square_to_vertice(i, j, m);
                struct neighbours n = {-1, -1, -1, -1};
                enum line l = is_border(i, j, m, kind);
                enum corner c = is_corner(i, j, m, kind);
                if (l) {
                    neighbour_border(i, j, m, l, &n);
                } else if (c) {
                    neighbour_corner(i, j, m, c, &n);
                } else {
                    neighbour_intern(i, j, m, &n);
                }
                b->c[convert_square_to_vertice(i, j, m)] = d(i, j, m);
                if (n.down != -1) {
                    int neighbour= convert_square_to_vertice(modulo(i+1, m), modulo(j, m), m);
                    gsl_spmatrix_uint_set(b->g->t, s_current, neighbour, 1);
                    gsl_spmatrix_uint_set(b->g->t, neighbour, s_current, 1);
                }
                if (n.up != -1) {
                    int neighbour= convert_square_to_vertice(modulo(i-1, m), modulo(j, m), m);
                    gsl_spmatrix_uint_set(b->g->t, s_current, neighbour, 1);
                    gsl_spmatrix_uint_set(b->g->t, neighbour, s_current, 1);
                }
                if (n.left != -1) {
                    int neighbour= convert_square_to_vertice(modulo(i, m), modulo(j-1, m), m);
                    gsl_spmatrix_uint_set(b->g->t, s_current, neighbour, 1);
                    gsl_spmatrix_uint_set(b->g->t, neighbour, s_current, 1);
                }
                if (n.right != -1) {
                    int neighbour= convert_square_to_vertice(modulo(i, m), modulo(j+1, m), m);
                    gsl_spmatrix_uint_set(b->g->t, s_current, neighbour, 1);
                    gsl_spmatrix_uint_set(b->g->t, neighbour, s_current, 1);
                }
                ++idx_color;
            } else {
                b->c[convert_square_to_vertice(i, j, m)] = NO_COLOR;
            }
        }
    }
    gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(b->g->t, GSL_SPMATRIX_CSR);  
    gsl_spmatrix_uint_free(t_coo);
    b->g->t = csr;
    return b;
}

void free_board(struct board* b)
{
    gsl_spmatrix_uint_free(b->g->t);
    free(b->g);
    free(b->c);
    free(b);
}
#include "server.h"
#include "board.h"
#include "../client/queue/queue.h"

void* st_copy_server(void * i)
{
    size_t* copy = malloc(sizeof(size_t)*1);
    *copy = *(size_t*) i;
    return copy;
}

void st_del_server(void * i)
{
    free(i);
}

int st_cmp_server(void* a, void* b)
{
    return (*(size_t*) a - *(size_t*) b);
}


int is_tag_server(size_t i, size_t* tagged, int tagged_amount)
{
    for (int j = 0; j < tagged_amount; j++) {
        if (tagged[j]==i) {
            return 1;
        }
    }
    return 0;
}


void update_graph_server(struct move_t* move, size_t id, struct board* b)
{
    // printf("id_parameter : %zu\n", id);
    // printf("id_position : %zu\n", b->g->positions[id]);
    enum color_t previous_color = b->c[b->g->positions[id]];
    struct queue* q = queue__empty(st_copy_server,st_del_server,st_cmp_server);
    queue__add(q, &(b->g->positions[id]));
    size_t tagged[b->g->num_vertices];
    int tagged_amount = 0;
    tagged[tagged_amount]=b->g->positions[id];
    tagged_amount++;
    while (!queue__is_empty(q)) {
        struct element* e = queue__pop(q);
        size_t* vertice = (size_t*) element__data(e);
        if (b->c[*vertice] == previous_color) {
            for (size_t i=0; i < b->g->num_vertices; i++) {
                if (gsl_spmatrix_uint_get(b->g->t,*vertice,i)!=0 && !(is_tag_server(i,tagged,tagged_amount))) {
                    queue__add(q,&i);
                    tagged[tagged_amount]=i;
                    tagged_amount++; 
                }
            }
            b->c[*vertice]=move->c;
        }
        element__free(e);
    }
    queue__free(q);
}


int bfs_counter_server(size_t id, struct board* b)
{
    int counter = 0;
    struct queue* q = queue__empty(st_copy_server,st_del_server,st_cmp_server);
    // potentiel bug
    queue__add(q, &(b->g->positions[id]));
    size_t tagged[b->g->num_vertices];
    int tagged_amount = 0;
    tagged[tagged_amount]=b->g->positions[id];
    tagged_amount++;
    while (!queue__is_empty(q)) {
        struct element* e = queue__pop(q);
        size_t* vertice = (size_t*) element__data(e);
        if (b->c[*vertice] == b->c[b->g->positions[id]]) {
            for (size_t i=0; i < b->g->num_vertices; i++) {
                if (gsl_spmatrix_uint_get(b->g->t,*vertice,i)!=0 && !(is_tag_server(i,tagged,tagged_amount))) {
                    queue__add(q,&i);
                    tagged[tagged_amount]=i;
                    tagged_amount++; 
                }
            }
            counter++;
        }
        element__free(e);
    }
    queue__free(q);
    return counter;
}


int get_winner(struct board* b)
{
    int player1 = bfs_counter_server(0, b);
    int player2 = bfs_counter_server(1, b);
    if (player2 > player1) {
        return 1;
    }
    else if (player2 < player1) {
        return 0;
    }
    else {
        return -1;
    }
}

int nzmax(int graph_type, int m)
{
    switch (graph_type) {
        case SQUARE:
            return nzmax_square(m);
            break;
        case DONUT:
            return nzmax_donut(m);
            break;
        case HGRAPH:
            return  nzmax_hgraph(m);
            break;
        case TORUS:
            return nzmax_torus(m);
            break;
        default:
            return nzmax_square(m);
            break;
        }
}

struct board* generate(int graph_type, int board_size, size_t positions[], dyeing_t d, struct board* b)
{
    switch (graph_type) {
        case SQUARE:
            return generate_board(b, graph_type, board_size, positions, d, filter_square, nzmax_square);
            break;
        case DONUT:
            return generate_board(b, graph_type, board_size, positions, d, filter_donut, nzmax_donut);
            break;
        case HGRAPH:
            return  generate_board(b, graph_type, board_size, positions, d, filter_hgraph, nzmax_hgraph);
            break;
        case TORUS:
            return generate_board(b, graph_type, board_size, positions, d, filter_torus, nzmax_torus);
            break;
        default:
            return generate_board(b, graph_type, board_size, positions, d, filter_square, nzmax_square);
            break;
        }
}

int random_player()
{
    srand(time(NULL));
    return (rand()%2);
}

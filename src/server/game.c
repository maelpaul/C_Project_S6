#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "../display/display.h"
#include "input.h"

#define DEFAULT_GRAPH_TYPE SQUARE
#define DEFAULT_BOARD_SIZE 9
#define DEFAULT_NUM_COLORS MAX_COLOR
#define DEFAULT_COLOR_ALGO 0
#define DEFAULT_BANNED_COLORS 0

typedef char const *(*p_name)();
typedef void (*init)(size_t, struct graph_t *, enum color_t *, struct color_set_t *);
typedef struct move_t (*play)(struct move_t);
typedef void (*finalize)();

struct player
{
    size_t id;
    p_name get_player_name;
    init initialize;
    play play;
    finalize finalize;
};

int main(int argc, char *argv[])
{
    int graph_type = DEFAULT_GRAPH_TYPE;
    int board_size = DEFAULT_BOARD_SIZE;
    int num_colors = DEFAULT_NUM_COLORS;
    int dyeing_algo = DEFAULT_COLOR_ALGO;
    int forbidden_colors = DEFAULT_BANNED_COLORS;
    scan_option(argc, argv, &board_size, &num_colors, &dyeing_algo, &forbidden_colors, &graph_type);

    void *access[NUM_PLAYERS];
    struct player players[NUM_PLAYERS];
    int nb = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '.' || check_install(argv[i]))
        {
            if (!(access[nb] = dlopen(argv[i], RTLD_LAZY)))
            {
                printf("Erreur dlopen: %s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            else if (!(players[nb].initialize = (init)dlsym(access[nb], "initialize")))
            {
                printf("Erreur dlsym: %s\n", dlerror());
                dlclose(access[nb]);
                exit(EXIT_FAILURE);
            }
            else if (!(players[nb].get_player_name = (p_name)dlsym(access[nb], "get_player_name")))
            {
                printf("Erreur dlsym: %s\n", dlerror());
                dlclose(access[nb]);
                exit(EXIT_FAILURE);
            }
            else if (!(players[nb].play = (play)dlsym(access[nb], "play")))
            {
                printf("Erreur dlsym: %s\n", dlerror());
                dlclose(access[nb]);
                exit(EXIT_FAILURE);
            }
            else if (!(players[nb].finalize = (finalize)dlsym(access[nb], "finalize")))
            {
                printf("Erreur dlsym: %s\n", dlerror());
                dlclose(access[nb]);
                exit(EXIT_FAILURE);
            }
            else
            {
                players[nb].id = nb + 1;
            }
            nb++;
        }
    }

    size_t start_player_id = random_player();
    size_t other_player_id = 1 - start_player_id;
    size_t positions[NUM_PLAYERS] = {0, board_size * board_size - 1};
    struct board *b = malloc(sizeof(struct board));
    if (dyeing_algo == 0)
    {
        b = generate(graph_type, board_size, positions, random_dyeing, b);
    }
    else
    {
        b = generate(graph_type, board_size, positions, cyclic_dyeing, b);
    }

    struct color_set_t colors;
    for (int i = 0; i < MAX_COLOR; i++)
    {
        colors.t[i] = 0;
    }

    struct color_set_t forbidden[NUM_PLAYERS] = {colors, colors};

    struct graph_t *copy_g_p_1 = malloc(sizeof(struct graph_t));
    struct graph_t *copy_g_p_2 = malloc(sizeof(struct graph_t));
    gsl_spmatrix_uint *copy_t_p1 = gsl_spmatrix_uint_alloc_nzmax(board_size * board_size, board_size * board_size, nzmax(graph_type, board_size), GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint *copy_t_p2 = gsl_spmatrix_uint_alloc_nzmax(board_size * board_size, board_size * board_size, nzmax(graph_type, board_size), GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(copy_t_p1, b->g->t);
    gsl_spmatrix_uint_memcpy(copy_t_p2, b->g->t);
    copy_g_p_1->t = copy_t_p1;
    copy_g_p_1->num_vertices = board_size * board_size;
    copy_g_p_1->positions[0] = 0;
    copy_g_p_1->positions[1] = board_size * board_size - 1;
    copy_g_p_2->t = copy_t_p2;
    copy_g_p_2->num_vertices = board_size * board_size;
    copy_g_p_2->positions[0] = 0;
    copy_g_p_2->positions[1] = board_size * board_size - 1;

    struct graph_t *copy_g_p[NUM_PLAYERS] = {copy_g_p_1, copy_g_p_2};

    enum color_t *copy_c_p_1 = malloc(board_size * board_size * sizeof(enum color_t));
    enum color_t *copy_c_p_2 = malloc(board_size * board_size * sizeof(enum color_t));
    memcpy(copy_c_p_1, b->c, board_size * board_size * (sizeof(enum color_t)));
    memcpy(copy_c_p_2, b->c, board_size * board_size * (sizeof(enum color_t)));

    enum color_t *copy_c_p[NUM_PLAYERS] = {copy_c_p_1, copy_c_p_2};

    // initialization
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        players[i].initialize(i, copy_g_p[i], copy_c_p[i], forbidden);
    }

    // play
    size_t current_player = other_player_id;
    struct move_t current_move = {NO_COLOR};
    struct move_t previous_move = {RED};

    int count = 0;
    printf("%d %d\n", board_size, board_size);
    while (1)
    {
        current_player = 1 - current_player;
        previous_move = current_move;
        current_move = players[current_player].play(current_move);
        int counter = bfs_counter_server(players[current_player].id - 1, b);
        if (current_move.c != NO_COLOR) {
            update_graph_server(&current_move, current_player, b);
            int new_counter = bfs_counter_server(players[current_player].id - 1, b);
            if (new_counter == counter) {
                break;
            }
        }
        graph_disp(b->c, b->g);
        if (current_move.c == NO_COLOR && previous_move.c == NO_COLOR) {
            break;
        }
        count++;
    }

    int gagnant = get_winner(b);
    if (gagnant != -1)
    {
        printf("%s has won the game \n", players[gagnant].get_player_name());
    }
    else
    {
        printf("Draw\n");
    }

    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        players[i].finalize();
    }

    free_board(b);
    for (int i = 0; i < nb; i++)
    {
        dlclose(access[i]);
    }
    exit(EXIT_SUCCESS);
}
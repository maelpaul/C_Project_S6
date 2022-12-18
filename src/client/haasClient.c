#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "queue.h"
#include "client_debug.h"
#include "rules.h"
#include "graph/bfs.h"

#define MAX_GAMES_HAAS 100

static size_t current_id;
static struct graph_t* current_graph;
static enum color_t* current_colors;
static struct color_set_t current_forbidden[NUM_PLAYERS];

size_t id_debug(void)
{
    return current_id;
}

struct graph_t* graph_debug(void)
{
    return current_graph;
}

enum color_t* colors_debug(void)
{
    return current_colors;
}

struct color_set_t* forbidden_debug(void)
{
    return current_forbidden;
}

char const* get_player_name()
{
    srand(time(NULL));
    int number = mod_pos(rand(),2);
    char* name;
    if (number == 0) {
        name = "Mick Schumacher";
    }
    else {
        name = "Kevin Magnussen";
    }
    return name;
}

void initialize(size_t id, struct graph_t* graph, enum color_t* colors, struct color_set_t forbidden[NUM_PLAYERS])
{
    current_id = id;
    current_graph = malloc(sizeof(struct graph_t));
    current_graph->num_vertices = graph->num_vertices;
    current_graph->t = gsl_spmatrix_uint_alloc_nzmax(graph->num_vertices,graph->num_vertices,graph->num_vertices*graph->num_vertices,GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(current_graph->t,graph->t);
    current_colors = malloc(graph->num_vertices * sizeof(enum color_t));
    for (size_t i = 0; i < graph->num_vertices; ++i)
    {
        current_colors[i] = colors[i];
    }    
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        current_graph->positions[i] = graph->positions[i];
        for (int j = 0; j < MAX_COLOR; ++j) {
            current_forbidden[i].t[j] = forbidden[i].t[j];                    
        }    
    }     
    gsl_spmatrix_uint_free(graph->t);
    free(graph);
    free(colors);
}

int bfs_counter(size_t id, struct graph_t* graph, enum color_t* colors)
{
    int counter = 0;
    struct queue* q = queue__empty(st_copy,st_del,st_cmp);
    queue__add(q, &graph->positions[id]);
    size_t tagged[graph->num_vertices];
    int tagged_amount = 0;
    tagged[tagged_amount]=graph->positions[id];
    tagged_amount++;
    while (!queue__is_empty(q)) {
        struct element* e = queue__pop(q);
        size_t* vertice = (size_t*) element__data(e);
        if (colors[*vertice] == colors[graph->positions[id]]) {
            for (size_t i=0; i < graph->num_vertices; i++) {
                if (get(graph,vertice,i)!=0 && !(is_tag(i,tagged,tagged_amount))) {
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

void fake_update_map(struct move_t* move, size_t id, struct graph_t* graph, enum color_t* colors)
{
    if (move->c != NO_COLOR) {
        enum color_t previous_color = colors[graph->positions[id]];
        struct queue* q = queue__empty(st_copy,st_del,st_cmp);
        queue__add(q, &graph->positions[id]);
        size_t tagged[graph->num_vertices];
        int tagged_amount = 0;
        tagged[tagged_amount]=graph->positions[id];
        tagged_amount++;
        while (!queue__is_empty(q)) {
            struct element* e = queue__pop(q);
            size_t* vertice = (size_t*) element__data(e);
            if (colors[*vertice] == previous_color) {
                for (size_t i=0; i < graph->num_vertices; i++) {
                    if (get(graph,vertice,i)!=0 && !(is_tag(i,tagged,tagged_amount))) {
                        queue__add(q,&i);
                        tagged[tagged_amount]=i;
                        tagged_amount++; 
                    }
                }
                colors[*vertice]=move->c;
            }
            element__free(e);
        }
        queue__free(q);
    }
}

int fake_game(enum color_t color,int plays)
{
    srand(time(NULL));
    int victory_rate = 0;
    for (int j=0; j<MAX_GAMES_HAAS; j++) {
        enum color_t* colors = malloc(current_graph->num_vertices * sizeof(enum color_t));
        for (size_t n=0; n<current_graph->num_vertices; n++) {
            colors[n]=current_colors[n];
        }
        struct move_t* move = malloc(sizeof(struct move_t)*1);
        move->c=color;
        fake_update_map(move,current_id,current_graph,colors);
        free(move);
        size_t id = 1-current_id;
        for (int n = 0; n<plays;n++) {
            struct move_t new_move = {NO_COLOR};
            enum color_t colors_tab[current_graph->num_vertices];
            for (size_t i = 0; i < current_graph->num_vertices; ++i) {
                colors_tab[i] = NO_COLOR;
            }
            breadthFirstSearch(current_graph, colors, current_graph->positions[id], colors_tab);
            enum color_t avaliable[current_graph->num_vertices];
            int avaliable_amount = 0;
            for (size_t i = 0; i < current_graph->num_vertices; i++) {
                if (colors_tab[i]==NO_COLOR) {
                    break;
                }
                else if (!forbidden_color(id, current_graph, colors,current_forbidden, colors_tab[i]) && (colors_tab[i]!=colors[current_graph->positions[1-id]])) {
                    avaliable[avaliable_amount]=colors_tab[i];
                    avaliable_amount++;
                }
            }
            if (avaliable_amount!=0) {
                int random = mod_pos(rand(),avaliable_amount);
                new_move.c = avaliable[random];
            }
            fake_update_map(&new_move,id,current_graph,colors);
            id = 1-id;
        }
        if (bfs_counter(current_id,current_graph,colors) > bfs_counter(1-current_id,current_graph,colors)) {
            victory_rate++;
        }
        free(colors);
    }
    return victory_rate;
}

struct move_t play(struct move_t previous_move)
{
    struct move_t new_move = {NO_COLOR};
    srand(time(NULL));
    update_map(&previous_move, 1-current_id);
    enum color_t colors_tab[current_graph->num_vertices];
    for (size_t i = 0; i < current_graph->num_vertices; ++i) {
        colors_tab[i] = NO_COLOR;
    }
    breadthFirstSearch(current_graph, current_colors, current_graph->positions[current_id], colors_tab); 
    int avaliable[MAX_COLOR];
    for (int n = 0; n < MAX_COLOR; n++) {
        avaliable[n]=0;
    }
        int avaliable_amount = 0;
    for (size_t i = 0; i < current_graph->num_vertices; i++) {
        if (colors_tab[i]==NO_COLOR) {
            break;
        }
        else if (!forbidden_color(current_id, current_graph, current_colors,current_forbidden, colors_tab[i]) && (colors_tab[i]!=current_colors[current_graph->positions[1-current_id]])) {
            avaliable[colors_tab[i]]++;
            avaliable_amount++;
        }
    }
    if (avaliable_amount==0) {
        return (new_move);
    }
    else {
        int max_rate = 0;
        for (int j=0; j<MAX_COLOR; j++) {
            if (avaliable[j]!=0) {
                int rate = fake_game(j,5);
                if (rate>=max_rate) {
                    max_rate = rate;
                    new_move.c = j;
                }
            }
        }
    }
    update_map(&new_move, current_id);
    return (new_move);
}

void update_map(struct move_t* move, size_t id)
{
    if (move->c != NO_COLOR) {
        enum color_t previous_color = current_colors[current_graph->positions[id]];
        struct queue* q = queue__empty(st_copy,st_del,st_cmp);
        queue__add(q, &current_graph->positions[id]);
        size_t tagged[current_graph->num_vertices];
        int tagged_amount = 0;
        tagged[tagged_amount]=current_graph->positions[id];
        tagged_amount++;
        while (!queue__is_empty(q)) {
            struct element* e = queue__pop(q);
            size_t* vertice = (size_t*) element__data(e);
            if (current_colors[*vertice] == previous_color) {
                for (size_t i=0; i < current_graph->num_vertices; i++) {
                    if (get(current_graph,vertice,i)!=0 && !(is_tag(i,tagged,tagged_amount))) {
                        queue__add(q,&i);
                        tagged[tagged_amount]=i;
                        tagged_amount++; 
                    }
                }
                current_colors[*vertice]=move->c;
            }
            element__free(e);
        }
        queue__free(q);
    }
}

void finalize(void)
{
    // char const* name = get_player_name();
    // size_t other_id = 1-current_id;
    // int own_counter = bfs_counter(current_id, current_graph, current_colors);
    // int other_counter = bfs_counter(other_id, current_graph, current_colors);
    // if (own_counter>other_counter) {
    //     printf("%s wins !\n", name);
    // }
    // else if (own_counter<other_counter) {
    //     printf("%s loses !\n", name);
    // }
    // else {
    //     printf("Tie !\n");
    // }
    gsl_spmatrix_uint_free(current_graph->t);
    free(current_graph);
    free(current_colors);
}
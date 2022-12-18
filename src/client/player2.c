#include <stdio.h>
#include <stdlib.h>

#include "../player.h"

char const* get_player_name()
{
    printf("Je m'appelle le player 2 \n");
    return NULL;
}

void initialize(size_t id, struct graph_t* graph, enum color_t* colors, struct color_set_t forbidden[NUM_PLAYERS])
{
    printf("Le joueur 2 a inititialisé sa partie. \n");
}

struct move_t play(struct move_t previous_move) 
{
    printf("Le joueur 2 a joué. \n");
    struct move_t m = {RED};
    return m;
}

void finalize()
{
    printf("Le joueur 2 a fini sa partie. \n");
}
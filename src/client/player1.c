#include <stdio.h>
#include <stdlib.h>

#include "../player.h"

char const* get_player_name()
{
    printf("Je m'appelle le joueur 1 \n");
    return NULL;
}

void initialize(size_t id, struct graph_t* graph, enum color_t* colors, struct color_set_t forbidden[NUM_PLAYERS])
{
    printf("Le joueur 1 a initialisé sa partie ! \n");
}

struct move_t play(struct move_t previous_move)
{
    printf("Le joueur 1 vient de jouer \n");
    struct move_t color = {BLUE};
    return color;
}

void finalize()
{
    printf("Le joueur 1 a terminé sa partie ! \n");
}
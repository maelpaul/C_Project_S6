#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "rules.h"

int mod_pos(int i, int mod)
{
    return ((i%mod>=0)? i%mod : i%mod+mod);
}

int forbidden_color(size_t id, struct graph_t* graph, enum color_t* colors, struct color_set_t forbidden[NUM_PLAYERS], enum color_t color)
{   
    enum color_t current_color = colors[graph->positions[id]];
    if (current_color == color)
    {
        return 1;
    }
    if (forbidden[id].t[color]==1) {
        return 1;
    }
    return 0;
}

/**
 * @file rules.h
 * @brief Rules of the project
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _RULES_H_
#define _RULES_H_

#include "../color.h"
#include "../graph.h"

/**
 * @brief Returns i % mod as a positive integer
 * 
 * @param i An integer
 * @param mod An integer
 * @return int 
 */
int mod_pos(int i, int mod);

/**
 * @brief Returns 1 if color is a forbidden color, 0 otherwise  
 * 
 * @param id An id of a player (0 or 1)
 * @param graph A pointer on a graph 
 * @param colors An array of colors
 * @param forbidden An array of arrays (one array for each player) of char (forbidden[player].t[color] == 1 for a forbidden color for player, 0 otherwise)
 * @param color The color to test if it is forbidden
 * @return int 
 */
int forbidden_color(size_t id, struct graph_t* graph, enum color_t* colors, struct color_set_t forbidden[NUM_PLAYERS], enum color_t color);

#endif // _RULES_H_

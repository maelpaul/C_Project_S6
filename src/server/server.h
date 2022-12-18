/**
 * @file server.h
 * @brief Server of the project
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../graph.h"
#include "../color.h"
#include "board.h"

/**
 * @brief Return a random number between 0 and 1
 * 
 * @return int 
 */
int random_player();

/**
 * @brief returns a copy of i
 * 
 * @param i void*
 * @return void* 
 */
void* st_copy_server(void * i);

/**
 * @brief frees i
 * 
 * @param i 
 */
void st_del_server(void * i);

/**
 * @brief compares a and b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int st_cmp_server(void* a, void* b);

/**
 * @brief Returns a boolean to see if cell is tagged
 * 
 * @param i size_t
 * @param tagged size_t *
 * @param tagged_amount int
 * @return int 
 */
int is_tag_server(size_t i, size_t* tagged, int tagged_amount);

/**
 * @brief Updates the board with the move that has juste been made by the player
 * 
 * @param move struct move_t*
 * @param id size_t
 * @param b struct board*
 */
void update_graph_server(struct move_t* move, size_t id, struct board* b);

/**
 * @brief Counts the number of tiles on the board possessed by the player
 * 
 * @param id size_t
 * @param b struct board*
 * @return int 
 */
int bfs_counter_server(size_t id, struct board* b);

/**
 * @brief Returns the winner of the game
 * 
 * @param b struct board*
 * @return int 
 */
int get_winner(struct board* b);

/**
 * @brief Returns the nzmax corresponding to the graph_type and the size of the board
 * 
 * @param graph_type int
 * @param m int
 * @return int 
 */
int nzmax(int graph_type, int m);

/**
 * @brief Generates a board corresponding to the graph type and the graph size
 * 
 * @param graph_type int
 * @param board_size int
 * @param positions size_t array
 * @param d dyeing_t function pointer
 * @param b struct board*
 * @return struct board* 
 */
struct board* generate(int graph_type, int board_size, size_t positions[], dyeing_t d, struct board* b);

#endif // _SERVER_H_
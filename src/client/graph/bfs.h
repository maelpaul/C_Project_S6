/**
 * @file bfs.h
 * @brief Breadth-first search(BFS) of the project
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _BFS_H_
#define _BFS_H_

#include "graph.h"

/**
 * @brief Useful function for BFS to see if cell is tagged
 * 
 * @param vertice A vertice
 * @param tagged An array of vertices
 * @param tagged_amount An integer
 * @return int 
 */
int is_tag(size_t vertice, size_t* tagged, int tagged_amount);

/**
 * @brief Returns the element of the graph->t matrix at position *vertice, i
 * 
 * @param graph A pointer on a graph
 * @param vertice A pointer on a vertice
 * @param i An other vertice
 * @return int 
 */
int get(struct graph_t* graph, size_t* vertice, size_t i);

/**
 * @brief Copy function for size_t
 * 
 * @param i A void pointer
 * @return void* 
 */
void* st_copy(void* i);

/**
 * @brief Free function for size_t
 * 
 * @param i A void pointer
 */
void st_del(void* i);

/**
 * @brief Compare function for size_t
 * 
 * @param a A void pointer
 * @param b A void pointer
 * @return int 
 */
int st_cmp(void* a, void* b);

/**
 * @brief Updates color_found with colors found at the border of the area with start point being start
 * 
 * @param graph A pointer on a graph
 * @param color An array of colors
 * @param start A start point
 * @param color_found An array of colors
 */
void breadthFirstSearch(struct graph_t* graph, enum color_t* color, size_t start, enum color_t* color_found);

#endif // _BFS_H_

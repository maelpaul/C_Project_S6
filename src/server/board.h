/**
 * @file board.h
 * @brief Functions to generate and free the board
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../graph.h"
#include "../color.h"

typedef int (*filter_t)(int, int, int);
typedef int (*dyeing_t)(int, int, int);
typedef size_t (*nzmax_t)(size_t);

enum line {
    NONE_LINE, UP_IN, LEFT_IN, RIGHT_IN, DOWN_IN, UP_OUT, LEFT_OUT, RIGHT_OUT, DOWN_OUT
};

enum corner {
    NONE_CORNER, UP_RIGHT1, UP_RIGHT2, UP_LEFT1, UP_LEFT2, DOWN_LEFT1, DOWN_LEFT2, DOWN_RIGHT1, DOWN_RIGHT2
};

/**
 * @brief Structure of a board
 * 
 */
struct board {
	struct graph_t* g; /*!< A pointer on a graph */
	enum color_t* c; /*!< An array of colors */
};

/**
 * @brief Return a graphe with the type in parameter
 * 
 * @param b struct board*
 * @param kind graph_t Graph type
 * @param m integer board width
 * @param position size_t Start positions of each player, indexed by id
 * @param d dyeing_t pointer to a function which applies the dyeing
 * @param f filter_t pointer to a function which applies a filter to know if the square is in this kind of graph
 * @param nzmax nzmax_t pointer to a function which returns the maximal number of null coefficient 
 * @return struct board*
 */
struct board *generate_board(struct board* b, enum graph_type_t kind, int m, size_t position[], dyeing_t d, filter_t f, nzmax_t nzmax);

/**
 * @brief Structures of neighbours
 * 
 */
struct neighbours {
    int up; /*!< Upwards neighbour, -1 if it doesn't exist */  
    int down; /*!< Downwards neighbour, -1 if it doesn't exist  */
    int left; /*!< Left neighbour, -1 if it doesn't exist */
    int right; /*!< Right neighbour, -1 if it doesn't exist */
};

/**
 * @brief Return Boolean indicating if square with coordinates x and y can be colored in order to obtain a square graph
 * 
 * @param x integer coordinate x < m
 * @param y integer coordinate y < m
 * @param m integer board width
 * @return int, 1 if square can be colored, otherwise 0
 */
int filter_square(int x, int y, int m);

/**
 * @brief Return Boolean indicating if square with coordinates x and y can be colored in order to obtain a donut graph
 * 
 * @param x integer coordinate x
 * @param y integer coordinate y
 * @param m integer board width
 * @return int, positive if square can be colored -1 if m isn't a multiple of 3 otherwise 0
 */
int filter_donut(int x, int y, int m);

/**
 * @brief Return Boolean indicating if square with coordinates x and y can be colored in order to obtain a hgraph graph
 * 
 * @param x integer coordinate x
 * @param y integer coordinate y
 * @param m integer board width
 * @return int, positive if square can be colored -1 if m isn't a multiple of 3 otherwise 0
 */
int filter_hgraph(int x, int y, int m);

/**
 * @brief Return Boolean indicating if square with coordinates x and y can be colored in order to obtain a torus graph
 * 
 * @param x integer coordinate x
 * @param y integer coordinate y
 * @param m integer board width
 * @return int, positive if square can be colored -1 if m isn't a multiple of 3 otherwise 0
 */
int filter_torus(int x, int y, int m);

/**
 * @brief Return the length of the three arrays is equal to the number of non-zero elements in the matrix, nnz for a square graph
 * 
 * @param m size_t Size of m
 * @return size_t the length of the three arrays is equal to the number of non-zero elements in the matrix
 */
size_t nzmax_square(size_t m);

/**
 * @brief Return the length of the three arrays is equal to the number of non-zero elements in the matrix, nnz for a donut graph
 * 
 * @param m size_t Size of m
 * @return size_t the length of the three arrays is equal to the number of non-zero elements in the matrix
 */
size_t nzmax_donut(size_t m);

/**
 * @brief Return the length of the three arrays is equal to the number of non-zero elements in the matrix, nnz for a hgraph
 * 
 * @param m size_t Size of m
 * @return size_t the length of the three arrays is equal to the number of non-zero elements in the matrix
 */
size_t nzmax_hgraph(size_t m);

/**
 * @brief Return the length of the three arrays is equal to the number of non-zero elements in the matrix, nnz for a torus graph
 * 
 * @param m size_t Size of m
 * @return size_t the length of the three arrays is equal to the number of non-zero elements in the matrix
 */
size_t nzmax_torus(size_t m);

/**
 * @brief Return if a board square (i, j) is a corner and its position
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param m integer board width
 * @param t enum graph_type_t kind of graph, SQUARE, HGRAPH, TORUS, DONUT
 * @return enum corner 
 * @retval NONE_CORNER if the square isn't a corner
 * @retval UP_RIGHT1 if the corner is up and right 
 * @retval UP_RIGHT2 if the corner is up and right in the board center
 * @retval UP_LEFT1 if the corner is up and left 
 * @retval UP_LEFT2 if the corner is up and left in the board center
 * @retval DOWN_RIGHT1 if the corner is down and right 
 * @retval DOWN_RIGHT2 if the corner is down and right in the board center
 * @retval DOWN_LEFT1 if the corner is down and left 
 * @retval DOWN_LEFT2 if the corner is down and left in the board center
 * @retval -1 if the kind of graph is unknown
 */
enum corner is_corner(int i, int j,  int m, enum graph_type_t t);

/**
 * @brief Replace the corner c if c by c_expected if the square coordinates (i, j) are (value_expected_i, value_expected_j)
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param c enum corner* pointer of the corner whose the value is modified by side effect
 * @param value_expected_i integer cooridinate i expected
 * @param value_expected_j integer coordinate j expected
 * @param c_expected enum corner
 * 
 */
void add_corner_if_exist(int i, int j, enum corner* c, int value_expected_i, int value_expected_j, enum corner c_expected);

/**
 * @brief  Return if a board square (i, j) is in a border and what kind of border is it 
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param m integer board width
 * @param t enum graph_type_t kind of graph, SQUARE, HGRAPH, TORUS, DONUT
 * @return enum line 
 */
enum line is_border(int i, int j, int m, enum graph_type_t t);

/**
 * @brief Returns the neighbours of the border vertice who's coordinates are (i, j)
 * 
 * @param i integer coordinate row of vertice
 * @param j integer coordinate column of vertice
 * @param m integer size of board
 * @param l enum line border type
 * @param n pointer to neighbour structure
 * @return void 
 */
void neighbour_border(int i, int j, int m, enum line l, struct neighbours* n);

/**
 * @brief Returns the neighbours of the corner vertice who's coodrinates are (i, j)
 * 
 * @param i integer coordinate row of vertice
 * @param j integer coordinate column of vertice
 * @param m integer size of board
 * @param c enum corner corner type
 * @param n pointer to neighbour structure
 * @return void
 */
void neighbour_corner(int i, int j, int m, enum corner c, struct neighbours* n);

/**
 * @brief Returns the neighbours of the intern vertice who's coodrinates are (i, j)
 * 
 * @param i integer coordinate row of vertice
 * @param j integer coordinate column of vertice
 * @param m enum corner corner type
 * @param n pointer to neighbour structure
 * @return void
 */
void neighbour_intern(int i, int j, int m, struct neighbours* n);

/**
 * @brief Return a random color for a square (i, j)
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param m integer width board
 * @return int 
 */
int random_dyeing(int i, int j, int m);

/**
 * @brief Return a cyclic color for a square (i, j)
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param m integer width board
 * @return int (i + j*m)%MAX_COLOR
 */
int cyclic_dyeing(int i, int j, int m);

/**
 * @brief Return number vertice from square position (i, j)
 * 
 * @param i integer coordinate i
 * @param j integer coordinate j
 * @param m integer width board
 * @return int Number vertice
 */
int convert_square_to_vertice(int i, int j, int m);

/**
 * @brief frees the board b
 * 
 * @param b struct board*
 */
void free_board(struct board* b);

/**
 * @brief Return the times in millisec
 * 
 * @return long long 
 */
long long current_timestamp();

#endif // _BOARD_H_


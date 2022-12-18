/**
 * @file display.h
 * @brief Displayer of the project
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "../graph.h"
#include "../color.h"

/**
 * @brief Returns the absolute value for a float number
 * 
 * @param x A float(double) number 
 * @return double 
 */
double float_abs(double x);

/**
 * @brief Returns the graph type
 * 
 * @param graph A pointer on a graph
 * @return enum graph_type_t 
 */
enum graph_type_t graph_type(struct graph_t* graph);

/**
 * @brief Returns the number of lines(columns) of the matrix
 * 
 * @param graph A pointer on a graph
 * @param type A type of graph
 * @return int 
 */
int matrix_m(struct graph_t* graph, enum graph_type_t type);

/**
 * @brief Returns the rgb color of colors[i*m+j]
 * 
 * @param colors An array of colors
 * @param m The graph width
 * @param i The line
 * @param j The column
 * @return int 
 */
int rgb_color(enum color_t* colors, int m, int i, int j);

/**
 * @brief Copies in new_colors the colors of the graph for the cases square and torus
 * 
 * @param colors An array of colors
 * @param new_colors An array of colors
 * @param m The graph width
 */
void square_and_torus_case(enum color_t* colors, enum color_t* new_colors, int m);

/**
 * @brief Copies in new_colors the colors of the graph for the case donut (the center hole is black)
 * 
 * @param colors An array of colors
 * @param new_colors An array of colors
 * @param m The graph width
 */
void donut_case(enum color_t* colors, enum color_t* new_colors, int m);

/**
 * @brief Copies in new_colors the colors of the graph for the case hgraph (the top and bottom in the middle are black)
 * 
 * @param colors An array of colors
 * @param new_colors An array of colors
 * @param m The graph width
 */
void hgraph_case(enum color_t* colors, enum color_t* new_colors, int m);

/**
 * @brief Copies in new_colors the colors of the graph depending on its type
 * 
 * @param colors An array of colors
 * @param type A type of graph
 * @param m The graph width
 * @param new_colors An array of colors
 */
void convert(enum color_t* colors, enum graph_type_t type, int m, enum color_t* new_colors);

/**
 * @brief Displays a graph
 * 
 * @param colors An array of colors
 * @param graph A pointer on a graph
 */
void graph_disp(enum color_t* colors, struct graph_t* graph); 

#endif // __DISPLAY_H__

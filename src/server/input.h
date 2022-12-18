/**
 * @file input.h
 * @brief Manage the inputs
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/**
 * @brief Change the graph type to the one chosen by the user
 * 
 * @param a char*
 * @param graph_type int*
 */
void change_graph(char *a, int *graph_type);

/**
 * @brief Changes the arguments to the ones chosen by the user
 * 
 * @param argc int
 * @param argv char*
 * @param m int*
 * @param c int*
 * @param a int*
 * @param f int*
 * @param t int*
 */
void scan_option(int argc, char *argv[], int *m, int *c, int *a, int *f, int *t);

/**
 * @brief Check if the string str is equal to "install"
 * 
 * @param str char*
 * @return int 
 */
int check_install(char* str);

#endif // _INPUT_H_
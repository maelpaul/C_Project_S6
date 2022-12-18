#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "graph.h"
#include "input.h"


void change_graph(char *a, int *graph_type)
{
    switch (*a) {
    case 'c':
        *graph_type = SQUARE;
        break;
    case 'd':
        *graph_type = DONUT;
        break;
    case 'h':
        *graph_type = HGRAPH;
        break;
    case 't':
        *graph_type = TORUS;
    default:
        break;
    }
}

void scan_option(int argc, char *argv[], int *m, int *c, int *a, int *f, int *t)
{
  int opt = 0;
  while ((opt = getopt(argc, argv, "m:c:a:f:t:")) != -1)
  {
    switch (opt)
    {
    case 'm':
        if (atoi(optarg))
            *m = atoi(optarg);
      break;
    case 'c':
        if (atoi(optarg))
            *c = atoi(optarg);
      break;
    case 'a':
        if (atoi(optarg))
            *a = atoi(optarg);
      break;
    case 'f':
        if (atoi(optarg))
            *f = atoi(optarg);
      break;
    case 't':
        if (optarg)
            change_graph(optarg, t);
    }
  }
}

int check_install(char* str) {
    return str[0] == 'i' && str[1] == 'n' && str[2] == 's' && str[3] == 't' && str[4] == 'a' && str[5] == 'l' && str[6] == 'l';
}
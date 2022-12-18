#include "player.h"
#include "display.h"

double float_abs(double x)
{
    if (x >= 0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}

enum graph_type_t graph_type(struct graph_t* graph)
{
    double a = sqrt(2) * sqrt(graph->num_vertices) * (float)3/4;
    double b = sqrt(7) * sqrt(graph->num_vertices) * (float)3/7;  
    if (float_abs(a - round(a)) < 0.001)
    {
        return 1;
    }
    else if (float_abs(b - round(b)) < 0.001)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int matrix_m(struct graph_t* graph, enum graph_type_t type)
{
    double a;
    switch (type)
    {
        case 1:
            a = sqrt(2) * sqrt(graph->num_vertices) * (float)3/4;
            break;
        case 2:
            a = sqrt(7) * sqrt(graph->num_vertices) * (float)3/7;        
            break;
        default:
            a = sqrt(graph->num_vertices);    
            break;                    
    }
    int m = (int)a;
    return m;
}

int rgb_color(enum color_t* colors, int m, int i, int j)
{
    int c = 0;
    switch (colors[i*m+j]) 
    {
        case 0:
            c = 16711680;
            break;
        case 1:
            c = 255;
            break;
        case 2:
            c = 65280;                         
            break;
        case 3:
            c = 65535;
            break;                                        
        case 4:
            c = 42495;
            break;
        case 5:
            c = 16711935;
            break;
        case 6:
            c = 16776960;
            break;
        case 7:
            c = 13353215;
            break;
        default:
            c = 0;
            break;                                                                                                    
    }
    return c;    
}

void square_and_torus_case(enum color_t* colors, enum color_t* new_colors, int m)
{
    for (int i = 0; i < m*m; ++i)
    {
        new_colors[i] = colors[i];
    }
}

void donut_case(enum color_t* colors, enum color_t* new_colors, int m)
{
    for (int i = m/3; i < 2*m/3; ++i)
    {
        for (int j = m/3; j < 2*m/3; ++j)
        {
            new_colors[i*m+j] = NO_COLOR;
        }
    }
    int idx = 0;
    for (int k = 0; k < m*m; ++k)
    {
        if (new_colors[k] != NO_COLOR)
        {
            new_colors[k] = colors[idx];
            idx++;
        }
    }
}

void hgraph_case(enum color_t* colors, enum color_t* new_colors, int m)
{
    for (int i = 0; i < m/3; ++i)
    {
        for (int j = m/3; j < 2*m/3; ++j)
        {
            new_colors[i*m+j] = NO_COLOR;
        }
    }
    for (int i = 2*m/3; i < m; ++i)
    {
        for (int j = m/3; j < 2*m/3; ++j)
        {
            new_colors[i*m+j] = NO_COLOR;
        }
    }
    int idx = 0;
    for (int k = 0; k < m*m; ++k)
    {
        if (new_colors[k] != NO_COLOR)
        {
            new_colors[k] = colors[idx];
            idx++;
        }
    }
}

void convert(enum color_t* colors, enum graph_type_t type, int m, enum color_t* new_colors)
{
    for (int i = 0; i < m*m; ++i)
    {
        new_colors[i] = MAX_COLOR;
    }
    switch (type) 
    {
        case 0:
            square_and_torus_case(colors, new_colors, m);
            break;
        case 1:
            donut_case(colors, new_colors, m);
            break;
        case 2:
            hgraph_case(colors, new_colors, m);
            break;
        default:
            break;            
    }
}

void graph_disp(enum color_t* colors, struct graph_t* graph) 
{
    enum graph_type_t type = graph_type(graph);
    int m = matrix_m(graph, type);
    enum color_t* new_colors = malloc(m*m*sizeof(enum color_t));
    convert(colors, type, m, new_colors);
    int c = 0;
    printf("#\n");
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            c = rgb_color(new_colors, m, i, j);
            printf("%d ", c);
        }
        printf("\n");
    }
    free(new_colors);
}

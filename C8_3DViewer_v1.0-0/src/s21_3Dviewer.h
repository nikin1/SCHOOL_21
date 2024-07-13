#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct vertex_struct {
    double * coord_array;
    unsigned int * connect_array;
    int col;
    int col_connect;
} vertex_t;

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;


//vertex_t Parsing(char * filename, int * error);
vertex_t Parsing(FILE *file, int * error);

vertex_t Scale(vertex_t data, double corner);
vertex_t Shift(vertex_t data, double corner, char c);
vertex_t TurnAround(vertex_t data, double corner, char c);

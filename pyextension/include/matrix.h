#ifndef matrix_h
#define matrix_h


#include <stdio.h>
#include <string.h>
#include "data_structure.h"


typedef enum _MatDType {
    ULONG = 0,
    DOUBLE,
} MatDType;

/* double matrix */
typedef struct _MatrixDouble {
    size_t row;     /* 行数 */
    size_t col;     /* 列数 */
    MatDType dtype;
    double *data;
} MatrixDouble;

typedef struct _MatrixULong {
    size_t row;     /* 行数 */
    size_t col;     /* 列数 */
    MatDType dtype;
    unsigned long *data;
} MatrixULong;

void print_matrix(void *matrix, MatDType dtype);
int transpose(void *_matrix, MatDType dtype);
unsigned long find_best_discrete_prop(unsigned long *matirx, unsigned long *class, size_t n_sample, size_t n_prop);
int contiguous_c_to_f(void *matrix, MatDType dtype);


#endif	/* matrix_h */

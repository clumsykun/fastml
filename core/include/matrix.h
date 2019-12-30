#ifndef matrix_h
#define matrix_h


#include <stdio.h>
#include <string.h>
#include "data_structure.h"


void print_matrix(double *matrix, size_t nRow, size_t nCol);
double *col_variance(double *matrix, size_t nRow, size_t nCol);


#endif	/* matrix_h */

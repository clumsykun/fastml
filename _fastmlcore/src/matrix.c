/**
 * matrix
 * 
 **/


#include "matrix.h"

void print_matrix(double *matrix, size_t nRow, size_t nCol)
{
    size_t idx;
    printf("\n------------------------------\n");
    for (size_t i = 0; i < nRow; i++) {
        for (size_t j = 0; j < nCol; j++) {
            idx = i * nCol + j;
            printf("%6.2f\t", matrix[idx]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
}


/* 计算一个矩阵的列方差 */
double *col_variance(double *matrix, size_t nRow, size_t nCol)
{
    size_t total_size = nRow * nCol;
    size_t idx;
    double diff;

    /* 求均值 */
    double *mean = (double *)malloc(nCol * sizeof(double));
    for (size_t i = 0; i < total_size; i++) {
        idx = i % nCol;
        mean[idx] += matrix[i];
    }
    for (size_t i = 0; i < nCol; i++) {
        mean[i] = mean[i] / (double)nRow;
    }

    /* 求方差 */
    double *variance = (double *)malloc(nCol * sizeof(double));
    memset(variance, 0, nCol * sizeof(double));
    for (size_t i = 0; i < total_size; i++) {
        idx = i % nCol;
        diff = matrix[i] - mean[idx];
        variance[idx] += (diff * diff) / nRow;
    }

    free(mean);
    return variance;
}


/**
 * matrix
 * 所有的矩阵以竖向排序，也就是 Fortran 风格
 **/


#include "matrix.h"


void print_matrix(void *matrix, MatDType dtype)
{
    printf("\n------------------------------\n");

    switch (dtype) {

        case ULONG:
            for (size_t i = 0; i < ( (MatrixULong *)matrix )->row; i++) {
                for (size_t j = 0; j < ( (MatrixULong *)matrix )->col; j++)
                    printf("\t%6d",
                           ( (MatrixULong *)matrix )->data[i + j * ( (MatrixULong *)matrix )->row]);

                printf("\n");
            }

            break;

        case DOUBLE:

            for (size_t i = 0; i < ( (MatrixDouble *)matrix )->row; i++) {
                for (size_t j = 0; j < ( (MatrixDouble *)matrix )->col; j++)
                    printf("\t%6.2f",
                           ( (MatrixDouble *)matrix )->data[i + j * ( (MatrixDouble *)matrix )->row]);

                printf("\n");
            }
            break;

        default:
            break;
    }

    printf("------------------------------\n");
}

int transpose(void *matrix, MatDType dtype)
{
    unsigned long tmp_ulong;
    double tmp_double;
    size_t row, row_new, col, col_new;
    void *tmp_memeory;

    switch (dtype) {

        case ULONG:
            row = ((MatrixULong *)matrix)->row;
            col = ((MatrixULong *)matrix)->col;
            ( (MatrixULong *)matrix )->row = row_new = col;
            ( (MatrixULong *)matrix )->col = col_new = row;
            tmp_memeory = malloc( row*col*sizeof(unsigned long) );
            if (tmp_memeory == NULL)
                return -1;
            memcpy(
                tmp_memeory,
                ( (MatrixULong *)matrix )->data, row*col*sizeof(unsigned long)
            );
            for (size_t i = 0; i < col; i++)
                for (size_t j = 0; j < row; j++)
                    ( (MatrixULong *)matrix )->data[i + row_new * j] =
                        ((unsigned long *)tmp_memeory)[j + row * i];
            free(tmp_memeory);
            break;

        case DOUBLE:
            row = ((MatrixDouble *)matrix)->row;
            col = ((MatrixDouble *)matrix)->col;
            ( (MatrixDouble *)matrix )->row = row_new = col;
            ( (MatrixDouble *)matrix )->col = col_new = row;
            tmp_memeory = malloc( row*col*sizeof(double) );
            if (tmp_memeory == NULL)
                return -1;
            memcpy(
                tmp_memeory,
                ( (MatrixDouble *)matrix )->data, row*col*sizeof(double)
            );
            for (size_t i = 0; i < col; i++)
                for (size_t j = 0; j < row; j++)
                    ( (MatrixDouble *)matrix )->data[i + row_new * j] =
                    ((double *)tmp_memeory)[j + row * i];
            free(tmp_memeory);
            break;

        default:
            return -1;
    }
    return 0;
}

int contiguous_c_to_f(void *matrix, MatDType dtype)
{
    void *tmp_memory;
    size_t row, col, idx = 0;

    switch (dtype) {
        case ULONG:
            row = ( (MatrixULong *)matrix )->row;
            col = ( (MatrixULong *)matrix )->col;
            tmp_memory = (unsigned long *)malloc(
                row * col * sizeof(unsigned long));

            memcpy(tmp_memory,
                   ( (MatrixULong *)matrix )->data,
                   row * col * sizeof(unsigned long));

            for (size_t j = 0; j < col; j++)
                for (size_t i = 0; i < row; i++) {
                    ( (MatrixULong *)matrix )->data[idx] =
                        ( (unsigned long *)tmp_memory )[i * col + j];
                    idx++;
                }
            free(tmp_memory);
            break;
        
        default:
            break;
    }

    return 0;
}

/* 返回最佳的分裂属性索引，其中列是属性，行是样本 */
unsigned long find_best_discrete_prop(unsigned long *matirx,
                                      unsigned long *class,
                                      size_t n_sample,
                                      size_t n_prop)
{

    return 0;
}
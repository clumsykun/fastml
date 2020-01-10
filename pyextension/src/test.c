/**
 * 测试函数
 * 
 **/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data_structure.h"
#include "mathtool.h"
#include "matrix.h"
#include "utils.h"


int test_shannon()
{
    size_t size = 1000;
    // unsigned int *array = random_array_int(1, 10, size, 1);
    unsigned long array[6] = {1, 1, 1, 1, 3};
    double entropy = information_entropy(array, 5);
    printf("information entropy: %.2f\n", entropy);
    return 0;
}

int test_information_entropy_with_label()
{
    unsigned long Y_arr[17] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2 ,2 ,2 ,2};
    unsigned long prop_arr[17] = {1, 2, 2, 1, 3, 1, 2, 2, 2, 1, 3, 3, 1, 3, 2, 3, 1};
    double entropy = info_entropy_discrete_prop(Y_arr, prop_arr, 17);
    printf("information entropy: %.2f\n", entropy);
    return 0;
}

int test_class_counter()
{

    /* 测试用 code 来计数 */
    unsigned long array[10] = {1, 2, 1, 2, 1, 2, 3, 4, 5, 10};
    ClassCounter *counter = class_counter_create();
    for (size_t i = 0; i < 10; i++)
        class_counter_count(counter, array[i]);

    int count_sum = 0, count;
    printf("\n------------------------------\n");
    for (size_t i = 0; i < counter->size; i++) {
        count = counter->count_result[i];
        if (count == 0) continue;
        printf("%4d - %4d\n", i, counter->count_result[i]);
        count_sum += (int)counter->count_result[i];
    }
    printf("------------------------------\n\n");
    assert(count_sum == 10);
    class_counter_delete(counter);

    return 0;
}

int test_find_best_discrete_prop()
{
    unsigned long watermelon[] = {
        1, 1, 1, 1, 1, 1,
        2, 1, 2, 1, 1, 1,
        2, 1, 1, 1, 1, 1,
        1, 1, 2, 1, 1, 1,
        3, 1, 1, 1, 1, 1,
        1, 2, 1, 1, 2, 2,
        2, 2, 1, 2, 2, 2,
        2, 2, 1, 1, 2, 1,
        2, 2, 2, 2, 2, 1,
        1, 3, 3, 1, 3, 2,
        3, 3, 3, 3, 3, 1,
        3, 1, 1, 3, 3, 2,
        1, 2, 1, 2, 1, 1,
        3, 2, 2, 2, 1, 1,
        2, 2, 1, 1, 2, 2,
        3, 1, 1, 3, 3, 1,
        1, 1, 2, 2, 2, 1,
    };

    unsigned long class[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    MatrixULong *matrix = (MatrixULong *)malloc(sizeof(MatrixULong));
    matrix->dtype = ULONG;
    matrix->row = 17;
    matrix->col = 6;
    matrix->data = watermelon;

    print_matrix(matrix, matrix->dtype);
    contiguous_c_to_f(matrix, matrix->dtype);
    print_matrix(matrix, matrix->dtype);

    // find_best_discrete_prop(matrix, matrix->dtype);

    return 0;
}

int test_transpose_matrix(void)
{
    unsigned long data[] = {1, 2, 3, 4, 5, 6};
    MatrixULong *matrix = (MatrixULong *)malloc(sizeof(MatrixULong));
    matrix->col = 2;
    matrix->row = 3;
    matrix->data = data;
    matrix->dtype = ULONG;
    print_matrix(matrix, matrix->dtype);
    transpose(matrix, matrix->dtype);
    print_matrix(matrix, matrix->dtype);
    free(matrix);

    double data2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    MatrixDouble *matrix2 = (MatrixDouble *)malloc(sizeof(MatrixDouble));
    matrix2->col = 2;
    matrix2->row = 3;
    matrix2->data = data2;
    matrix->dtype = DOUBLE;
    print_matrix(matrix2, matrix2->dtype);
    transpose(matrix2, matrix2->dtype);
    print_matrix(matrix2, matrix2->dtype);

    free(matrix2);
    return 0;
}


int main(int argc, char const *argv[])
{
    // test_shannon();
    // test_class_counter();
    // test_information_entropy_with_label();
    test_find_best_discrete_prop();
    // test_transpose_matrix();
    return 0;
}

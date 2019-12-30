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
    unsigned int array[6] = {1, 1, 1, 1, 3};
    double entropy = information_entropy(array, 5);
    return 0;
}

int test_information_entropy_with_label()
{
    unsigned int Y_arr[17] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2 ,2 ,2 ,2};
    unsigned int prop_arr[17] = {1, 2, 2, 1, 3, 1, 2, 2, 2, 1, 3, 3, 1, 3, 2, 3, 1};
    double entropy = information_entropy_with_label(Y_arr, prop_arr, 17);
    return 0;
}


int test_class_counter()
{

    /* 测试用 code 来计数 */
    unsigned int array[10] = {1, 2, 1, 2, 1, 2, 3, 4, 5, 10};
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


int test_col_variance()
{
    size_t nRow = 5;
    size_t nCol = 2;
    double *X = malloc(nRow * nCol * sizeof (double));

    for (size_t i = 0; i < nRow * nCol; i++) {
        X[i] = (double)(i * i);
    }
    print_matrix(X, nRow, nCol);
    double *Y = col_variance(X, nRow, nCol);
    print_matrix(Y, 1, nCol);
    return 0;
}


int main(int argc, char const *argv[])
{
    test_shannon();
    test_class_counter();
    test_col_variance();
    test_information_entropy_with_label();
    return 0;
}

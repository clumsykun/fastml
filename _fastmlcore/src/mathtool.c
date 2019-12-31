/**
 * 数学工具
 **/


#include "mathtool.h"


/* 根据一个计数器计算出香农熵 */
double information_entropy_by_counter(ClassCounter *counter)
{
    double entropy = 0, prob;
    for (size_t i = 0; i < counter->size; i++) {
        prob = (double)counter->count_result[i] / (double)counter->num_of_samples;
        if (prob)
            entropy -= prob * log2(prob);
    }

    return entropy;
}

/* 计算一个数组的香农熵 */
double information_entropy(unsigned long *array, size_t size)
{
    ClassCounter *counter = class_counter_create();

    for (size_t i = 0; i < size; i++)
        class_counter_count(counter, array[i]);

    double entropy = information_entropy_by_counter(counter);
    free(counter);
    return entropy;
}

/* 在有标签的情况下计算信息熵，用于计算信息增益 */
double info_entropy_discrete_prop(unsigned long *Y_arr, unsigned long *prop_arr, size_t size)
{
    ClassCounter *counter_prop = class_counter_create();
    ClassCounter *counter_class = class_counter_create();
    double entropy_total, entropy_by_prop, result;

    for (size_t i = 0; i < size; i++) {
        class_counter_count(counter_prop, prop_arr[i]);
        class_counter_count(counter_class, Y_arr[i]);
    }

    entropy_total = information_entropy_by_counter(counter_class);

    /* 计算每个子类的信息熵 */
    ClassCounter *counters_of_prop[counter_prop->size];  /* 一组计数器 */
    double prop_entropy[counter_prop->size];  /* 保存属性各取值的信息熵 */
    memset(prop_entropy, 0, counter_prop->size*sizeof(double));

    for (size_t i = 0; i < counter_prop->size; i++)  /* 初始化计数器 */
        counters_of_prop[i] = class_counter_create();

    for (size_t i = 0; i < size; i++) /* 计算属性各取值的信息熵 */
        class_counter_count(counters_of_prop[ prop_arr[i] ], Y_arr[i]);

    entropy_by_prop = 0;  /* 初始化 */
    for (size_t i = 0; i < counter_prop->size; i++)
        if (counter_prop->count_result[i])
            entropy_by_prop += (double)counter_prop->count_result[i] / (double)size *
                               information_entropy_by_counter(counters_of_prop[i]);

    /* 处理内存 */
    class_counter_delete(counter_prop);
    class_counter_delete(counter_class);
    for (size_t i = 0; i < counter_prop->size; i++)
        class_counter_delete(counters_of_prop[i]);

    result = entropy_total - entropy_by_prop;
    return result;
}

/* 生成一个 unsigned int 随机数组 */
unsigned int *random_array_int(unsigned int min, unsigned int max, size_t size, unsigned int seed)
{
    srand(seed);
    int range = max - min + 1;
    unsigned int *array = (unsigned int *)malloc(size * sizeof(unsigned int));
    for (size_t i = 0; i < size; i++) {
        array[i] = (rand() % range) + min;
    }
    return array;
}

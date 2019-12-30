#ifndef data_structure_h
#define data_structure_h

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SIZE_OF_NAME 1024
#define SIZE_OF_LONG 20  /* 整数的最大长度 */
typedef size_t size_t;


typedef struct _ClassCounter {
    size_t size;                  /* 计数器记录的类别数 */
    size_t num_of_samples;        /* 计数器统计的样本数 */
    unsigned long *count_result;  /* 计数结果 */
} ClassCounter;


ClassCounter *class_counter_create(void);
int class_counter_extend(ClassCounter *counter, size_t size);
int class_counter_count(ClassCounter *counter, unsigned long code);
int class_counter_delete(ClassCounter *counter);


#endif	/* data_structure_h */

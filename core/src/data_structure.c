/**
 * 基本数据类型：
 *   - LinkedList
 **/


#include "data_structure.h"

#define CLASS_EXTEND_SIZE 10
#define CLASS_MAX_SIZE 10000

/** ================================================================================
 * Class Counter
 ================================================================================ **/

/**
 * 异常返回值：返回 NULL
 **/
ClassCounter *class_counter_create()
{
    ClassCounter *counter = (ClassCounter *) malloc ( sizeof(ClassCounter) );
    if (counter == NULL)  /* 内存分配失败 */
        return NULL;

    counter->num_of_samples = 0;
    counter->size = CLASS_EXTEND_SIZE;  /* 类别数初始化 */
    counter->count_result   = (unsigned long *) malloc ( counter->size * sizeof(unsigned long) );
    memset( counter->count_result, 0, counter->size * sizeof(unsigned long) );
    
    if (counter->count_result == NULL) {  /* 内存分配失败 */
        free(counter);
        return NULL;
    }

    return counter;
}

/**
 * 
 * 计算正常时返回 0，否则返回 -1。
 **/
int class_counter_extend(ClassCounter *counter, size_t size)
{
    if (size <= counter->size)  /* 不需要扩充 */
        return 0;

    unsigned long *old_result = counter->count_result;
    size_t old_size = counter->size;
    counter->size   = (size_t)(ceil( (double)size / CLASS_EXTEND_SIZE ) * CLASS_EXTEND_SIZE);
    counter->count_result     = (unsigned long *)malloc( counter->size * sizeof(unsigned long) );
    memset( counter->count_result, 0, counter->size * sizeof(unsigned long) );

    memcpy( counter->count_result, old_result, old_size * sizeof(unsigned long) );
    free(old_result);

    return 0;
}

/**
 * 
 * 计算正常时返回 0，否则返回 -1。
 **/
int class_counter_count(ClassCounter *counter, unsigned long code)
{
    if (code > CLASS_MAX_SIZE)  /* 类别数过大 */
        return -1;

    if ( counter->size < code + 1 )  /* 类别数等于类别编号加一 */
        if ( class_counter_extend ( counter, (size_t) (code + 1) ) )
            return -1;  /* 扩展类别数出错 */

    counter->count_result[code]++;  /* 计数 */
    counter->num_of_samples++;
    return 0;
}

int class_counter_delete(ClassCounter *counter)
{

    free(counter->count_result);
    free(counter);
    return 0;
}


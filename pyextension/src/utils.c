/**
 * 工具函数
 * 
 * 逻辑类函数：
 *   - 为真时返回 1
 *   - 为假时返回 0
 *   - 错误时返回 -1
 * 
 **/

#include "utils.h"


int unicode_is_pure_ascii(const char *source)
{
    if (source == NULL)
        return -1;

    for (size_t i = 0; source[i] != '\0'; i++)
        if ( (int)source[i] < 0 )
            return 0;

    return 1;
}

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


int s_is_pure_ascii(const char *text)
{
    if (text == NULL)
        return -1;

    for (n_t i = 0; text[i] != '\0'; i++)
        if ( (int)text[i] < 0 )
            return 0;

    return 1;
}

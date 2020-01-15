/**
 * 测试函数
 * 
 **/

#include <Python.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "utils.h"


int test_str_is_pure_ascii()
{
    char *string1 = "上海abcaaabcaabcbca";
    char *string2 = "asdsada";
    char *string3 = NULL;

    assert(str_is_pure_ascii(string1) == 0);
    assert(str_is_pure_ascii(string2) == 1);
    assert(str_is_pure_ascii(string3) == -1);
    return 0;
}


int main(int argc, char const *argv[])
{
    return 0;
}

import pyextension
import jieba
from collections import namedtuple
from time import time

string_list = ['1123', '上海123', '  ', ',，']

for string in string_list:
    print(string, ': ', pyextension.str_is_pure_ascii(string))

print('\n--------------------------------------------------\n')

Date = namedtuple('DateTime', ['Year', 'Month', 'Day'])
a = Date(1999, 12, 31)
pyextension.print_type_name(a)


print('\n--------------------------------------------------\n')

source = '我在上海居住了三年。123abcAsadxaA;as'
my_dict = {
    '上海': 1,
    '居住': 2,
    '三年': 3,
    '我': 4,
    '在': 5,
}

start = time()
key_word = pyextension.str_extract_keyword(source, my_dict, True)
spend = time() - start
print(key_word)    
print('time spend: ', spend)

start = time()
key_word = pyextension.str_extract_keyword(source, my_dict, False)
spend = time() - start
print(key_word)    
print('time spend: ', spend)


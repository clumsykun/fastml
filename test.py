import pyextension
import jieba
from collections import namedtuple

string_list = ['1123', '上海123', '  ', ',，']

for string in string_list:
    print(string, ': ', pyextension.str_is_pure_ascii(string))

print('\n--------------------------------------------------\n')

Date = namedtuple('DateTime', ['Year', 'Month', 'Day'])
a = Date(1999, 12, 31)
pyextension.print_type_name(a)


print('\n--------------------------------------------------\n')

source = '我在上海居住了三年。'
my_dict = {
    1: '上海',
    2: '居住',
    3: '三年',
    4: '我',
    5: '在',
}

result = jieba.cut(source)
print(list(result))
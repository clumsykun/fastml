import pyextension
from collections import namedtuple

string_list = ['1123', '上海123', '  ', ',，']

for string in string_list:
    print(string, ': ', pyextension.str_is_pure_ascii(string))

print('\n--------------------------------------------------\n')

Date = namedtuple('DateTime', ['Year', 'Month', 'Day'])
a = Date(1999, 12, 31)
pyextension.print_type_name(a)


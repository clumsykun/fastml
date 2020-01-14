import pyextension

string_list = ['1123', '上海123', '  ', ',，']

for string in string_list:
    print(string, ': ', pyextension.utf8_is_pure_ascii(string))


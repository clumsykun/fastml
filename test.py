import pyextension
import jieba
from collections import namedtuple
from time import time

string_list = ['1123', '上海123', '  ', ',，']

for string in string_list:
    print(string, ': ', pyextension.str_is_pure_ascii(string))


print('\n--------------------------------------------------\n')

unicode = '我在上海居住了三年。123abcAsadxaA;as'
my_dict = {
    '上海': 1,
    '上海市': 2,
    '居住': 2,
    '三年': 3,
    '我': 4,
    '在': 5,
}

start = time()
key_word = pyextension.str_extract_keyword(unicode, my_dict)
spend = time() - start
print(key_word)
print('time spend: ', spend)

print('\n--------------------------------------------------\n')

word_tfidf = pyextension.str_cal_tfidf(unicode, my_dict)
print(word_tfidf)

print('\n--------------------------------------------------\n')

unicode = ''.join(['这是一行测试文本。This is test text!'] * 10000000)

start = time()
rv = pyextension.str_reverse(unicode)
spend = time() - start

print('pyextension: ', spend)

start = time()
rv = unicode[::-1]
spend = time() - start

print('original: ', spend)

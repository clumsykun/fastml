import fastml.core as core
import numpy as np
import time

def col_variance(matrix):
    mean = matrix.mean(axis=0)

    result = []
    for i in range(matrix.shape[1]):
        value = np.power(matrix[:, i]-mean[i], 2) / matrix.shape[0]
        result.append(value.sum())
    return np.array(result)

X = np.random.rand(10000, 10)
# print(X)

start = time.time()
Y = col_variance(X)
spend = time.time() - start
print('diy python func spend time: %.2f' % spend)
print(Y)

start = time.time()
Y = core.col_variance(X)
spend = time.time() - start
print('diy c func spend time: %.2f' % spend)
print(Y)

start = time.time()
Y = np.var(X, axis=0)
spend = time.time() - start
print('original spend time: %.2f' % spend)
print(Y)

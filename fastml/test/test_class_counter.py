import fastml.core as core
import numpy as np
from collections import Counter
from random import shuffle
import time


X = np.random.randint(10000, size=100000000).astype(np.uint16)
print("X: ", X[:10])


start = time.time()
Y = core.class_counter(X)
spend = time.time() - start
print("core time: ", spend)
# print("Y: ", Y)

start = time.time()
Y = Counter(X)
spend = time.time() - start
print("counter time: ", spend)
# print("Y: ", Y.most_common())


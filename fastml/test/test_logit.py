import numpy as np
import fastml.core as core


a = np.array([0.1, 0.2, 0.3], dtype=np.float32)
b = core.logit(a)
print('np.float32:\t\t', b)

# np.float64 等于 np.double
a = np.array([0.1, 0.2, 0.3], dtype=np.float64)
b = core.logit(a)
print('np.float64/np.double:\t', b)

a = np.array([0.1, 0.2, 0.3], dtype=np.longdouble)
b = core.logit(a)
print('np.longdouble:\t\t', b)

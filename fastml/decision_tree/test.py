import pandas as pd
import numpy as np
import fastml.core as core
from decision_tree import DecisionTree


watermelon = pd.read_csv('watermelon.csv')

X = watermelon[['色泽','根蒂','敲声','纹理','脐部','触感']].values
Y = watermelon['类别'].values.astype(np.uint)

core.information_entropy_with_prop(Y, watermelon['色泽'].values.astype(np.uint))

tree = DecisionTree()
tree.fit(X, Y)

print(1)


if __name__ == '__main__':
    pass

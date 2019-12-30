import pandas as pd
import numpy as np
from fastml import core
from decision_tree import DecisionTree


watermelon = pd.read_csv('fastml/decision_tree/watermelon.csv')

X = watermelon[['色泽','根蒂','敲声','纹理','脐部','触感']].values
Y = watermelon['类别'].values.astype(np.uint)

for field in watermelon.columns:
    print(
        '%s - %.4f' % (
            field, 
            core.information_entropy_with_prop( Y, watermelon[field].values.astype(np.uint) )
        )
    )


if __name__ == '__main__':
    pass

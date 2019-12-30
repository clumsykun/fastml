"""
decision tree
"""

import fastml.core as core


class DecisionTree:

    def __init__(self):
        self.tree = None
    
    def fit(self, X, Y):
        core.class_counter(Y)
        print(1)

    def predict(self, X):
        pass

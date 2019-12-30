import fastml.core as core
from collections import namedtuple
import numpy as np


# ==================================================
# python  class
# ==================================================

CityInfo = namedtuple('CityInfo', ['name', 'country', 'population'])

class City:
    def __init__(self, name, country, population):
        self.info = CityInfo(
            name=name,
            country=country,
            population=population,
        )

shanghai = City('shanghai', 'china', 2424)
print(shanghai.__dict__)




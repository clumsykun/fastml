#/usr/bin/env python3

from setuptools import setup, Extension, find_packages
from numpy.distutils.misc_util import get_numpy_include_dirs

setup(
        name            = 'fastml',
        version         = '0.2',
        packages        = find_packages(),
        description     = 'My Python Extension Module',
        include_dirs    = get_numpy_include_dirs(),
        ext_modules     =   [
                            Extension(
                                '_fastmlcore',
                                sources = [
                                    '_fastmlcore/src/core_module.c',
                                    '_fastmlcore/src/utilities.c',
                                    '_fastmlcore/src/matrix.c',
                                    '_fastmlcore/src/data_structure.c',
                                    '_fastmlcore/src/mathtool.c',
                                ],
                                include_dirs = ['_fastmlcore/include/'])
                            ]
      )

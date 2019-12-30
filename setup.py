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
                                    'core/src/core_module.c',
                                    'core/src/utilities.c',
                                    'core/src/matrix.c',
                                    'core/src/data_structure.c',
                                ],
                                include_dirs = ['core/include/'])
                            ]
      )

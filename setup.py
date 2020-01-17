#/usr/bin/env python3

from setuptools import setup, Extension, find_packages
from numpy.distutils.misc_util import get_numpy_include_dirs

setup(
        name            = 'pyextension',
        version         = '0.5',
        packages        = find_packages(),
        description     = 'My Python Extension Module',
        include_dirs    = get_numpy_include_dirs(),
        ext_modules     =   [
                            Extension(
                                'pyextension',
                                sources = [
                                    'pyextension/src/pyextension_module.c',
                                    'pyextension/src/utils.c',
                                    'pyextension/src/pyfunc.c'
                                ],
                                include_dirs = ['pyextension/include/'])
                            ]
      )

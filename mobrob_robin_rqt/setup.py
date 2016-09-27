#!/usr/bin/env python

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    packages=['mobrob_robin_rqt'],
    package_dir={'': 'src'}
)

setup(**d)

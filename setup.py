from distutils.core import setup, Extension

module1=Extension('bcoll', sources=['bcollmodule.c'])

setup(
  name='BColl',
  version='1.0',
  description='A Stack Implementation',
  ext_modules=[module1]
)

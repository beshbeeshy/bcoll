from distutils.core import setup, Extension

module1=Extension('bcollections', sources=['bstackmodule.c'])

setup(
  name='BCollections',
  version='1.0',
  description='A Stack Implementation',
  ext_modules=[module1]
)

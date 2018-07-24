import os
from setuptools import setup

with open('README.md', 'r') as fh:
    long_description = fh.read()

setup(
    author='Serguei Kalentchouk',
    description='InputFormDialog provides a simple multi-type input dialog for Qt5',
    install_requires=['Qt.py'],
    license='MIT',
    long_description=long_description,
    long_description_content_type='text/markdown',
    py_modules=['input_form_dialog'],
    name='input_form_dialog',
    url='https://github.com/serguei-k/input-form-dialog/tree/master/python',
    version='1.0.1',
    zip_safe=False
)

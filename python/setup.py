import os
from setuptools import setup

setup(
    author='Serguei Kalentchouk',
    description='Input Form Dialog provides a simple multi-type input dialog for Qt5',
    install_requires=['Qt.py'],
    license='MIT',
    long_description=open('README.md').read(),
    name='input_form_dialog',
    package_dir={'input_form_dialog': 'src'},
    packages=['input_form_dialog'],
    url='https://github.com/serguei-k/input-form-dialog/python',
    version='1.0.0'
)
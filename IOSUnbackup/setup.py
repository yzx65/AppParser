
# setup.py
from distutils.core import setup
import py2exe

setup(console=["backup_tool.py","keychain_tool.py"])
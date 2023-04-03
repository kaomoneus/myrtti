import lit.formats
import os

config.name = "MyRTTI"
config.test_format = lit.formats.ShTest("0")
config.suffixes = ['.c', '.cpp']

config.excludes = ['Inputs', 'CMakeLists.txt', 'README.txt', 'LICENSE.txt']

MYRTTI_CLANG_ROOT = os.environ["MYRTTI_CLANG_ROOT"]

config.substitutions.append(('%clang',  MYRTTI_CLANG_ROOT + "/bin/clang"))
config.substitutions.append(('%clang\+\+', MYRTTI_CLANG_ROOT + "/bin/clang++"))
config.substitutions.append(('%bin', os.environ["MYRTTI_BIN_DIR"]))
config.substitutions.append(('%lib', os.environ["MYRTTI_LIB_DIR"]))
config.substitutions.append(('FileCheck', os.environ["FILECHECK"]))
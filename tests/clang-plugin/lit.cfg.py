# Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
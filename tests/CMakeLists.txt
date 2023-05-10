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

if (MYRTTY_CLANG_ROOT)
    add_subdirectory(clang-plugin)
endif()

find_package(benchmark)


if (benchmark_FOUND)
    message("Found Google Benchmark. Benchmarks are enabled.")
    add_subdirectory(benchmark)
else()
    message("Google Benchmarks not found, benchmarks will be disabled.")
endif()

find_package(GTest)

if (GTEST_FOUND)
    message("Found Google Test. Unittests are enabled.")
    add_subdirectory(unit)
else()
    message("Google Test not found, unit tests will be disabled.")
endif()
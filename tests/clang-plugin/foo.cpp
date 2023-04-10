// Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Just make sure whole LIT thing works as expected.

// RUN: (! %clang ) 2>&1 | FileCheck %s
// RUN: (! %clang ) 2>&1 | FileCheck %s --check-prefixes=CHECK2

// CHECK: no input files
// CHECK2-NOT: nope input files

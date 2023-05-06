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

#ifndef VAMACRO_HELPER
#define VAMACRO_HELPER

#include "narg.h"

// (pref, arg) pref arg

#define VAMACRO_PREFIX_1(pref, arg) pref arg
#define VAMACRO_PREFIX_2(pref, arg1, arg2) pref arg1, pref arg2
#define VAMACRO_PREFIX_3(pref, arg1, arg2) pref arg, pref arg, pref arg

// generate up to 64 VAMACRO_PREFIX_<N>

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define VA_PREF_N(N, pref, ...) \
    CONCATENATE(VAMACRO_PREFIX_, N)(pref, __VA_ARGS__)
#define VA_PREF(pref, ...) \
    VA_PREF_N(PP_NARG(__VA_ARGS__), pref, __VA_ARGS__) \

#endif

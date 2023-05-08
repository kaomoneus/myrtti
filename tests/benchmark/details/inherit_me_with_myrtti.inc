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

#ifndef WITHOUT_MYRTTI

#define ROOT(newClass) \
    with_rtti_root(newClass) \
    with_rtti_end()

#define INHERIT_ME(baseClass, newClass) \
    with_rtti(struct, newClass, (baseClass)) \
    with_rtti_end()

#define INHERIT_ME_MULTI(bases, newClass) \
    with_rtti_parents(struct, newClass, bases) \
    with_rtti_end()

#else

#define ROOT(newClass) struct newClass {}

#define __MYRTTI_BENCHMARKS_ESC(...) __VA_ARGS__

#define INHERIT_ME(baseClass, newClass) struct newClass : baseClass {}
#define INHERIT_ME_MULTI(bases, newClass) struct newClass : __MYRTTI_BENCHMARKS_ESC(bases) {}

#endif
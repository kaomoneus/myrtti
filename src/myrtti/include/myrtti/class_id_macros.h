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

#ifndef MYRTTI_CLASSID_MACROS
#define MYRTTI_CLASSID_MACROS

#if 1
#define MYRTTI_CLASSID class_id()
#define MYRTTI_DEFINE_CLASSID(...)                         \
    static MYRTTI_INLINE  constexpr myrtti::class_id_t class_id() {    \
        constexpr myrtti::class_id_t myId{__VA_ARGS__}; \
        return myId;                                          \
    }
#else
#define MYRTTI_CLASSID class_id
#define MYRTTI_DEFINE_CLASSID(...) static constexpr myrtti::class_id_t class_id{__VA_ARGS__};
#endif

#endif

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

#ifndef MYRTTI_BENCHMARKS_COMMON
#define MYRTTI_BENCHMARKS_COMMON

#include <afx.h>
#include <benchmark/benchmark.h>
#include <myrtti.h>


using namespace myrtti;

namespace _myrtti {
    struct Root : public RTTI<Root> {
        DEFINE_RTTI(Root, Object);
    };
}

namespace _mfc {
    class Root : public CObject {
    public:
        DECLARE_DYNAMIC(Root);
    };
    IMPLEMENT_DYNAMIC(Root, CObject);
}

#define MYRTTI_CLASS(Name, Parent)                  \
namespace _myrtti {                                  \
    struct Name : public Parent, RTTI<Name> { \
                                               \
            DEFINE_RTTI(Name, Parent)          \
    };                                         \
}

#define MFC_CLASS(Name, Parent)       \
namespace _mfc {                       \
    class Name : public Parent {    \
    public:                         \
        DECLARE_DYNAMIC(Name)       \
    };                              \
    IMPLEMENT_DYNAMIC(Name, Parent) \
}                                   \

#define CLASS_PAIR(Name, Parent) \
    MYRTTI_CLASS(Name, Parent)        \
    MFC_CLASS(Name, Parent)        \


#define DEEP(NameBase)                       \
    CLASS_PAIR(NameBase ## 0, Root)          \
    CLASS_PAIR(NameBase ## Wrong, Root)      \
    CLASS_PAIR(NameBase ## 1, NameBase ## 0) \
    CLASS_PAIR(NameBase ## 2, NameBase ## 1) \
    CLASS_PAIR(NameBase ## 3, NameBase ## 2) \
    CLASS_PAIR(NameBase ## 4, NameBase ## 3) \
    CLASS_PAIR(NameBase ## 5, NameBase ## 4) \
    CLASS_PAIR(NameBase ## 6, NameBase ## 5) \
    CLASS_PAIR(NameBase ## 7, NameBase ## 6) \
    CLASS_PAIR(NameBase ## 8, NameBase ## 7) \
    CLASS_PAIR(NameBase ## 9, NameBase ## 8) \
    CLASS_PAIR(NameBase ## 10, NameBase ## 9) \
    CLASS_PAIR(NameBase ## 11, NameBase ## 10) \
    CLASS_PAIR(NameBase ## 12, NameBase ## 11) \
    CLASS_PAIR(NameBase ## 13, NameBase ## 12) \
    CLASS_PAIR(NameBase ## 14, NameBase ## 13) \
    CLASS_PAIR(NameBase ## 15, NameBase ## 14) \
    CLASS_PAIR(NameBase ## 16, NameBase ## 15) \
    CLASS_PAIR(NameBase ## 17, NameBase ## 16) \
    CLASS_PAIR(NameBase ## 18, NameBase ## 17) \
    CLASS_PAIR(NameBase ## 19, NameBase ## 18) \


DEEP(DeepTest)

template<typename BaseT, typename FinalT, typename FinalWrongT>
class InheritanceFixture : public benchmark::Fixture
{
public:
    InheritanceFixture() {
#ifdef GOOGLE_BENCHMARK_ITERATIONS
        Iterations(50);
#endif
    }
    /// Before each run, build a vector of random integers.
    void SetUp(benchmark::State&) override
    {
        this->basePtr = &this->instance;
        this->finalPtr = &this->instance;
    }

    FinalT instance;
    FinalWrongT instanceWrong;

    FinalT* finalPtr;
    BaseT* basePtr;
};

#ifndef NUM_OPERATIONS
constexpr int NUM_OPERATIONS = 1000000;
#endif

// Here, make it noinline

#define MYRTTI_CAST(To, From) From->cast<To*>()
#define MYRTTI_TRY_STATIC_CAST(To, From) myrtti::try_static_cast<To*>(From)

#define __MYRTTI_BENCHMARK(name, Fixture, DYN_CAST, To, From, Res) \
    BENCHMARK_F(Fixture, name)(benchmark::State& state) \
    { \
        for (auto _ : state) { \
            for (int i = 0; i!=NUM_OPERATIONS;++i) { \
                auto *r = DYN_CAST(To, From); \
                if ((r != nullptr) != Res) abort(); \
                benchmark::DoNotOptimize(r); \
            } \
        } \
    } \

using  MyRttiFixture = InheritanceFixture<_myrtti::Root, _myrtti::DeepTest19, _myrtti::DeepTestWrong>;
using  MFCFixture = InheritanceFixture<_mfc::Root, _mfc::DeepTest19, _mfc::DeepTestWrong>;

#define MYRTTI_CAST_BENCHMARK(name, To, From, Res) \
    __MYRTTI_BENCHMARK(name, MyRttiFixture, MYRTTI_CAST, To, From, Res);

#define MYRTTI_TRY_STATIC_CAST_BENCHMARK(name, To, From, Res) \
    __MYRTTI_BENCHMARK(name, MyRttiFixture, MYRTTI_TRY_STATIC_CAST, To, From, Res);


#define LEGACY_CAST_BENCHMARK(name, To, From, Res) \
    __MYRTTI_BENCHMARK(name, MFCFixture, DYNAMIC_DOWNCAST, To, From, Res);

#define COMPARE_CASTS_BENCHMARK(namePrefix, To, From, Res) \
    LEGACY_CAST_BENCHMARK(namePrefix##_mfc, _mfc::To, From, Res); \
    MYRTTI_CAST_BENCHMARK(namePrefix##_myrtti, _myrtti::To, From, Res); \
    MYRTTI_TRY_STATIC_CAST_BENCHMARK(namePrefix##_myrttiTryStatic, _myrtti::To, From, Res); \

#endif // MYRTTI_BENCHMARKS_COMMON
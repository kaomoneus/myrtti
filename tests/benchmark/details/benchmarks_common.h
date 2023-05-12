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

#include <benchmark/benchmark.h>
#include <myrtti.h>

using namespace myrtti;

using VirtualBase = myrtti::Object;

#include "inherit_me_with_myrtti.inc"
#include "hierarchy_20items.inc"

struct BenchmarkContextTrait {
    void setup() {
        this->deep = new DeepFinal;
        this->deepBase = this->deep;
        this->deepVirtualBase = this->deep;

        this->wide = new WideFinal;
        this->wideBase = this->wide;
        this->wideVirtualBase = this->wide;
    }

    void teardown() {
        if (this->deep != nullptr)
        {
            delete this->deep;
        }

        if (this->wide != nullptr)
        {
            delete this->wide;
        }
    }

    DeepFinal* deep;
    DeepRoot* deepBase;
    VirtualBase* deepVirtualBase;

    WideFinal* wide;
    WideRoot* wideBase;
    VirtualBase* wideVirtualBase;
};

class InheritanceFixture : public benchmark::Fixture, public BenchmarkContextTrait
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
        setup();
    }

    /// After each run, clear the vector of random integers.
    void TearDown(benchmark::State&) override
    {
        teardown();
    }
};

struct BenchmarkContext : BenchmarkContextTrait {
    BenchmarkContext() { setup(); }
    ~BenchmarkContext() { teardown(); }

    static BenchmarkContext* instance() {
        static BenchmarkContext ctx;
        return &ctx;
    }
};

#ifndef NUM_OPERATIONS
constexpr int NUM_OPERATIONS = 1000000;
#endif

// Here, make it noinline

template<typename ToT, typename FromT>
__attribute__((noinline)) ToT* __legacy_cast(FromT o, bool res) {
    ToT* r = dynamic_cast<ToT*>(o);
    if ((r != nullptr) != res) abort();
    benchmark::DoNotOptimize(r);
    return r;
}

template<typename ToT, typename FromT>
__attribute__((noinline)) ToT* __myrtti_cast(FromT o, bool res) {
    ToT* r = myrtti::dyn_cast<ToT*>(o);
    if ((r != nullptr) != res) abort();
    benchmark::DoNotOptimize(r);
    return r;
}

// TODO: consider making multiple instances to check average
//   unordered_map performance.
#define __MYRTTI_BENCHMARK(name, DYN_CAST, To, From, Res) \
    BENCHMARK_F(InheritanceFixture, name)(benchmark::State& state) \
    { \
        for (auto _ : state) { \
            for (int i = 0; i!=NUM_OPERATIONS;++i) { \
                DYN_CAST<To>(From, Res); \
            } \
        } \
    } \

#define MYRTTI_CAST_BENCHMARK(name, To, From, Res) __MYRTTI_BENCHMARK(name, __myrtti_cast, To, From, Res);
#define LEGACY_CAST_BENCHMARK(name, To, From, Res) __MYRTTI_BENCHMARK(name, __legacy_cast, To, From, Res);

#define COMPARE_CASTS_BENCHMARK(namePrefix, To, From, Res) \
    LEGACY_CAST_BENCHMARK(namePrefix##_dynamic_cast, To, From, Res); \
    MYRTTI_CAST_BENCHMARK(namePrefix##_myrtti, To, From, Res); \



// ----------------------------------------------------------------------------
// Casts time comparison
// ----------------------------------------------------------------------------

/// Macro defines set of cast benchmarks.
///    DEFINITION_MACRO - substitute exact definition macro:
///       * MYRTTI_CAST_BENCHMARK - runs benchmarks for myrtti library.
///       * LEGACY_CAST_BENCHMARK - runs benchmarks for legacy dynamic_cast
///       * BENCHMARK_COMPARE - compares benchmarks: dynamic_cast vs myrtti
///
#define DEFINE_CAST_BENCHMARKS(DEFINITION_MACRO) \
    DEFINITION_MACRO(deep_fromBase, DeepFinal, this->deepBase, true); \
    DEFINITION_MACRO(deep_fromVirtualBase, DeepFinal, this->deepVirtualBase, true); \
\
    DEFINITION_MACRO(wide_fromBase, WideFinal, this->wideBase, true); \
    DEFINITION_MACRO(wide_fromVirtualBase, WideFinal, this->wideVirtualBase, true); \
\
    DEFINITION_MACRO(deep_toBase, DeepRoot, this->deep, true); \
    DEFINITION_MACRO(deep_toVirtualBase, VirtualBase, this->deep, true); \
\
    DEFINITION_MACRO(wide_toBase, WideRoot, this->wide, true); \
    DEFINITION_MACRO(wide_toVirtualBase, VirtualBase, this->wide, true); \
\
    DEFINITION_MACRO(deep_toSelf, DeepFinal, this->deep, true); \
    DEFINITION_MACRO(wide_toSelf, WideFinal, this->wide, true); \


#define DEFINE_CAST_NEG_BENCHMARKS(DEFINITION_MACRO) \
    DEFINITION_MACRO(deep_fromBaseNeg, WideFinal, this->deepBase, false); \
    DEFINITION_MACRO(deep_toBaseNeg, WideRoot, this->deep, false); \

// Run the benchmark
#ifndef NO_BENCHMARK_MAIN
BENCHMARK_MAIN();
#endif

#endif // MYRTTI_BENCHMARKS_COMMON
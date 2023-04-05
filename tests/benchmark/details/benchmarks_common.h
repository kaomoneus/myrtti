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
__attribute__((noinline)) ToT* __legacy_cast(FromT o) {
    ToT* r = dynamic_cast<ToT*>(o);
    if (!r) abort();
    benchmark::DoNotOptimize(r);
    return r;
}

template<typename ToT, typename FromT>
__attribute__((noinline)) ToT* __myrtti_cast(FromT o) {
    ToT* r = myrtti::dyn_cast<ToT*>(o);
    if (!r) abort();
    benchmark::DoNotOptimize(r);
    return r;
}

#define __MYRTTI_BENCHMARK(name, DYN_CAST, To, From) \
    BENCHMARK_F(InheritanceFixture, name)(benchmark::State& state) \
    { \
        for (auto _ : state) { \
            for (int i = 0; i!=NUM_OPERATIONS;++i) { \
                DYN_CAST<To>(From); \
            } \
        } \
    } \

#define MYRTTI_CAST_BENCHMARK(name, To, From) __MYRTTI_BENCHMARK(name, __myrtti_cast, To, From);
#define LEGACY_CAST_BENCHMARK(name, To, From) __MYRTTI_BENCHMARK(name, __legacy_cast, To, From);

#define COMPARE_CASTS_BENCHMARK(namePrefix, To, From) \
    LEGACY_CAST_BENCHMARK(namePrefix##_dynamic_cast, To, From); \
    MYRTTI_CAST_BENCHMARK(namePrefix##_myrtti, To, From); \



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
    DEFINITION_MACRO(deep_fromBase, DeepFinal, this->deepBase); \
    DEFINITION_MACRO(deep_fromVirtualBase, DeepFinal, this->deepVirtualBase); \
\
    DEFINITION_MACRO(wide_fromBase, WideFinal, this->wideBase); \
    DEFINITION_MACRO(wide_fromVirtualBase, WideFinal, this->wideVirtualBase); \
\
    DEFINITION_MACRO(deep_toBase, DeepRoot, this->deep); \
    DEFINITION_MACRO(deep_toVirtualBase, VirtualBase, this->deep); \
\
    DEFINITION_MACRO(wide_toBase, WideRoot, this->wide); \
    DEFINITION_MACRO(wide_toVirtualBase, VirtualBase, this->wide); \
\
    DEFINITION_MACRO(deep_toSelf, DeepFinal, this->deep); \
    DEFINITION_MACRO(wide_toSelf, WideFinal, this->wide); \


// Run the benchmark
#ifndef NO_BENCHMARK_MAIN
BENCHMARK_MAIN();
#endif

#endif // MYRTTI_BENCHMARKS_COMMON
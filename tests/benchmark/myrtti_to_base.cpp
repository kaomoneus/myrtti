// Benchmark sketch taken from John Farrier's repo:
//   https://github.com/DigitalInBlue/Priori/blob/master/benchmark/benchmark.cpp

#define NO_BENCHMARK_MAIN
// #define GOOGLE_BENCHMARK_ITERATIONS 50
// #define NUM_OPERATIONS 1000000

#include "details/benchmarks_common.h"

#define DEFINE_TEST_CAST(name, To, From) \
    void name() { \
        auto *ctx = BenchmarkContext::instance(); \
        auto *p = From; \
        __myrtti_cast<To>(p); \
    } \

DEFINE_TEST_CAST(deepToBase, DeepRoot, ctx->deep);
DEFINE_TEST_CAST(deepToVirtualBase, VirtualBase, ctx->deep);
DEFINE_TEST_CAST(wideToBase, WideRoot, ctx->wide);
DEFINE_TEST_CAST(wideToVirtualBase, VirtualBase, ctx->wide);

int main() {
    deepToBase();
}

#if 0
__attribute__((noinline)) void virtualBase_info() { benchmark::DoNotOptimize(VirtualBase::info()); }
__attribute__((noinline)) void deepBase_info() { benchmark::DoNotOptimize(DeepRoot::info()); }
__attribute__((noinline)) void wideBase_info() { benchmark::DoNotOptimize(WideRoot::info()); }

BENCHMARK_F(InheritanceFixture, rttiCosts_virtualBaseInfo)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            virtualBase_info();
        }
    }
}
BENCHMARK_F(InheritanceFixture, rttiCosts_wideBaseInfo)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            wideBase_info();
        }
    }
}
BENCHMARK_F(InheritanceFixture, rttiCosts_deepBaseInfo)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            deepBase_info();
        }
    }
}
#endif
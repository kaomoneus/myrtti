// Benchmark sketch taken from John Farrier's repo:
//   https://github.com/DigitalInBlue/Priori/blob/master/benchmark/benchmark.cpp

#include "details/benchmarks_common.h"

BENCHMARK_F(InheritanceFixture, rttiCosts_typeinfo)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(typeid(WideFinal));
        }
    }
}

BENCHMARK_F(InheritanceFixture, rttiCosts_typeinfoHash)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(typeid(WideFinal).hash_code());
        }
    }
}

BENCHMARK_F(InheritanceFixture, rttiCosts_typeinfoName)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(typeid(WideFinal).name());
        }
    }
}
BENCHMARK_F(InheritanceFixture, rttiCosts_myrttiName)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(WideFinal::info()->name);
        }
    }
}

BENCHMARK_F(InheritanceFixture, rttiCosts_myrttiClassId)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(WideFinal::class_id);
        }
    }
}

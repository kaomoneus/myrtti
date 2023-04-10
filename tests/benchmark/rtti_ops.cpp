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

// Benchmarks inspired by John Farrier's repo:
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

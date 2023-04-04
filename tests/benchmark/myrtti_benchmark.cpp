// Benchmark sketch taken from John Farrier's repo:
//   https://github.com/DigitalInBlue/Priori/blob/master/benchmark/benchmark.cpp

#include <benchmark/benchmark.h>
#include <myrtti.h>

using namespace myrtti;

using VirtualBase = myrtti::Object;

#include "inherit_me_with_myrtti.inc"
#include "hierarchy_20items.inc"

class InheritanceFixture : public benchmark::Fixture
{
public:
    /// Before each run, build a vector of random integers.
    void SetUp(benchmark::State&) override
    {
        this->deep = new DeepFinal;
        this->deepBase = this->deep;
        this->deepVirtualBase = this->deep;

        this->wide = new WideFinal;
        this->wideBase = this->wide;
        this->wideVirtualBase = this->wide;
    }

    /// After each run, clear the vector of random integers.
    void TearDown(benchmark::State&) override
    {
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

constexpr int NUM_OPERATIONS = 1000000;

#define LEGACY_DYN_CAST(To, From) auto *r = dynamic_cast<To*>(From); if (!r) abort(); benchmark::DoNotOptimize(r);
#define MYRTTI_DYN_CAST(To, From) auto *r = myrtti::dyn_cast<To*>(From); if (!r) abort(); benchmark::DoNotOptimize(r);

// ----------------------------------------------------------------------------
// Cast from a base to the derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_fromBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(DeepFinal, this->deepBase);
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_fromBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(DeepFinal, this->deepBase);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a virtual base to the derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_fromVirtualBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(DeepFinal, this->deepVirtualBase);
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_fromVirtualBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(DeepFinal, this->deepVirtualBase);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a base to the derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, wide_fromBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(WideFinal, this->wideBase);
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_fromBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(WideFinal, this->wideBase);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a virtual base to the derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, wide_fromVirtualBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(WideFinal, this->wideVirtualBase);
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_fromVirtualBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(WideFinal, this->wideVirtualBase);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the base type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_toBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(DeepRoot, this->deep);
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_toBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(DeepRoot, this->deep);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the base type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_toVirtualBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(VirtualBase, this->deep);
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_toVirtualBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(VirtualBase, this->deep);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the base type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, wide_toBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(WideRoot, this->wide);
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_toBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(WideRoot, this->wide);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the virtual base type.
// ----------------------------------------------------------------------------

BENCHMARK_F(InheritanceFixture, wide_toVirtualBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(VirtualBase, this->wide);
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_toVirtualBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(VirtualBase, this->wide);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the same derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_toSelf_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(DeepFinal, this->deep);
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_toSelf_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(DeepFinal, this->deep);
        }
    }
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the same derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, wide_toSelf_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            LEGACY_DYN_CAST(WideFinal, this->wide);
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_toSelf_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            MYRTTI_DYN_CAST(WideFinal, this->wide);
        }
    }
}

// ----------------------------------------------------------------------------
// Experiments for rtti operations costs.
// ----------------------------------------------------------------------------
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

// Run the benchmark
BENCHMARK_MAIN();
// Benchmark sketch taken from John Farrier's repo:
//   https://github.com/DigitalInBlue/Priori/blob/master/benchmark/benchmark.cpp

#include <benchmark/benchmark.h>
#include <myrtti.h>

using namespace myrtti;

#define INHERIT_ME(baseClass, newClass) \
    RTTI_STRUCT_BEGIN(newClass, (baseClass)) \
    RTTI_STRUCT_END()

RTTI_STRUCT_ROOT_BEGIN(Base) \
RTTI_STRUCT_END()

INHERIT_ME(Base, Wide1);
INHERIT_ME(Wide1, Wide2);
INHERIT_ME(Wide2, Wide3);
INHERIT_ME(Wide3, Wide4);
INHERIT_ME(Wide4, Wide5);
INHERIT_ME(Wide5, Wide6);
INHERIT_ME(Wide6, Wide7);
INHERIT_ME(Wide7, Wide8);
INHERIT_ME(Wide8, Wide9);
INHERIT_ME(Wide9, WideFinal);

INHERIT_ME(Base, Deep1);
INHERIT_ME(Deep1, Deep2);
INHERIT_ME(Deep2, Deep3);
INHERIT_ME(Deep3, Deep4);
INHERIT_ME(Deep4, Deep5);
INHERIT_ME(Deep5, Deep6);
INHERIT_ME(Deep6, Deep7);
INHERIT_ME(Deep7, Deep8);
INHERIT_ME(Deep8, Deep9);
INHERIT_ME(Deep9, DeepFinal);


class InheritanceFixture : public benchmark::Fixture
{
public:
    /// Before each run, build a vector of random integers.
    void SetUp(benchmark::State&) override
    {
        this->deep = new DeepFinal;
        this->deepBase = this->deep;

        this->wide = new WideFinal;
        this->wideBase = this->wide;
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

    DeepFinal* deep{ nullptr };
    Object* deepBase{ nullptr };

    WideFinal* wide{ nullptr };
    Object* wideBase{ nullptr };
};

constexpr int NUM_OPERATIONS = 2000000;

// ----------------------------------------------------------------------------
// Cast from a base to the derrived type.
// ----------------------------------------------------------------------------
BENCHMARK_F(InheritanceFixture, deep_fromBase_dynamic_cast)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(dynamic_cast<DeepFinal*>(this->deepBase));
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_fromBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<DeepFinal*>(this->deepBase));
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
            benchmark::DoNotOptimize(dynamic_cast<WideFinal*>(this->wideBase));
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_fromBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<WideFinal*>(this->wideBase));
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
            benchmark::DoNotOptimize(dynamic_cast<Base*>(this->deep));
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_toBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<Base*>(this->deep));
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
            benchmark::DoNotOptimize(dynamic_cast<Base*>(this->wide));
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_toBase_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<Base*>(this->wide));
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
            benchmark::DoNotOptimize(dynamic_cast<DeepFinal*>(this->deep));
        }
    }
}

BENCHMARK_F(InheritanceFixture, deep_toSelf_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<DeepFinal*>(this->deep));
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
            benchmark::DoNotOptimize(dynamic_cast<WideFinal*>(this->wide));
        }
    }
}

BENCHMARK_F(InheritanceFixture, wide_toSelf_myrtti)(benchmark::State& state)
{
    for (auto _ : state) {
        for (int i = 0; i!=NUM_OPERATIONS;++i) {
            benchmark::DoNotOptimize(myrtti::dyn_cast<WideFinal*>(this->wide));
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
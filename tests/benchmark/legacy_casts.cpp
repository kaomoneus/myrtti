// Benchmark sketch taken from John Farrier's repo:
//   https://github.com/DigitalInBlue/Priori/blob/master/benchmark/benchmark.cpp

#include "details/benchmarks_common.h"

#define WITHOUT_MYRTTI
DEFINE_CAST_BENCHMARKS(LEGACY_CAST_BENCHMARK);

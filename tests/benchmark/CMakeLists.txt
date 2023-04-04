set(BENCHMARK_TARGET myrtti_benchamrk)

find_package(benchmark REQUIRED)

add_executable(${BENCHMARK_TARGET} myrtti_benchmark.cpp)
target_link_libraries(${BENCHMARK_TARGET} benchmark::benchmark myrtti)

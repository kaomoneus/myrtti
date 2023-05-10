#pragma once

template<typename Tp>
inline void DoNotOptimize(Tp const& value) {
	asm volatile("" : : "r,m"(value) : "memory");
}

#define CASTS_PER_TICK 2500000
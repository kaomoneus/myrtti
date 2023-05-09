#pragma once

template<typename Tp>
inline void DoNotOptimize(Tp const& value) {
	asm volatile("" : : "r,m"(value) : "memory");
}
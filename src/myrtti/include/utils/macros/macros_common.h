//
// Created by Dyatkovskiy Stepan on 5/9/23.
//

#ifndef MYRTTI_MACROS_COMMON
#define MYRTTI_MACROS_COMMON


#define MYRTTI_ESC(...) __VA_ARGS__

#ifdef __clang__
#define MYRTTI_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define MYRTTI_INLINE __forceinline
#else
#warning "Unable to determine compiler, class_id() might not be inline and thus will be slower then planned."
#define MYRTTI_INLINE inline
#endif

#endif

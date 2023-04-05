#ifndef WITHOUT_MYRTTI

#define ROOT(newClass) \
    RTTI_STRUCT_ROOT_BEGIN(newClass) \
    RTTI_STRUCT_END()

#define INHERIT_ME(baseClass, newClass) \
    RTTI_STRUCT_BEGIN(newClass, (baseClass)) \
    RTTI_STRUCT_END()

#define INHERIT_ME_MULTI(bases, newClass) \
    RTTI_STRUCT_BEGIN(newClass, bases) \
    RTTI_STRUCT_END()

#else

#define ROOT(newClass) struct newClass {}

#define __MYRTTI_BENCHMARKS_ESC(...) __VA_ARGS__

#define INHERIT_ME(baseClass, newClass) struct newClass : baseClass {}
#define INHERIT_ME_MULTI(bases, newClass) struct newClass : __MYRTTI_BENCHMARKS_ESC(bases) {}

#endif
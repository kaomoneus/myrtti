#define ROOT(newClass) \
    RTTI_STRUCT_ROOT_BEGIN(newClass) \
    RTTI_STRUCT_END()

#define INHERIT_ME(baseClass, newClass) \
    RTTI_STRUCT_BEGIN(newClass, (baseClass)) \
    RTTI_STRUCT_END()

#define INHERIT_ME_MULTI(bases, newClass) \
    RTTI_STRUCT_BEGIN(newClass, bases) \
    RTTI_STRUCT_END()

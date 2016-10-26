#include <stdlib.h>
#include <string.h>

#include "misc/utils.h"
#include "misc/primitive.h"

#define _newconst(type) \
type *type ##_new(type a) {\
    type *p = (type *) malloc(sizeof(type));\
    *p = a;\
    return p;\
}

#define _newcomp(type)\
int type ##_compare(type a, type b) {\
    if (a < b)\
        return -1;\
    if (a == b)\
        return 0;\
    return 1;\
}

#define _newrefcomp(type)\
int type ## ref_compare(const void *a, const void *b) {\
    return type ##_compare(deref(a, type), deref(b, type));\
}

#define _decl(type) _newconst(type) _newcomp(type) _newrefcomp(type)

_decl(bool)
_decl(char)
_decl(short)
_decl(int)
_decl(long)
_decl(float)
_decl(double)

_decl(int8_t)
_decl(int16_t)
_decl(int32_t)
_decl(int64_t)
_decl(uint8_t)
_decl(uint16_t)
_decl(uint32_t)
_decl(uint64_t)

int strref_compare(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

#undef _decl

#undef _newconst
#undef _newcomp
#undef _newrefcomp

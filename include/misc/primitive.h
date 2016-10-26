#pragma once

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_ 1

#include <stdint.h>
#include <stdbool.h>

#define _newconst(type) type *type ##_new(type)
#define _newcomp(type) int type ##_compare(type, type)
#define _newrefcomp(type) int type ## ref_compare(const void *, const void *)

#define _decl(type) _newconst(type); _newcomp(type); _newrefcomp(type)

_decl(bool);
_decl(char);
_decl(short);
_decl(int);
_decl(long);
_decl(float);
_decl(double);

_decl(int8_t);
_decl(int16_t);
_decl(int32_t);
_decl(int64_t);
_decl(uint8_t);
_decl(uint16_t);
_decl(uint32_t);
_decl(uint64_t);

int strref_compare(const void *, const void *);

#undef _decl

#undef _newconst
#undef _newcomp
#undef _newrefcomp

#endif /* ifndef _PRIMITIVE_H_ */

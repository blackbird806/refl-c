#ifndef TEST_H
#define TEST_H

#include "reflect.h"

typedef struct test_s_t
{
	int a, b, c;
	float f;
} test_s;

REFLECT_STRUCT_BEGIN(test_s)
	REFLECT_MEMBER(test_s, int, a)
	REFLECT_MEMBER(test_s, int, b)
	REFLECT_MEMBER(test_s, int, c)
	REFLECT_MEMBER(test_s, float, f)
REFLECT_STRUCT_END()

#endif
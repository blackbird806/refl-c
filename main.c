#include <stdio.h>
#include <string.h>

#include "reflect.h"
#include "attribute.h"

#include "print_struct.h"

#include "test.h"

typedef struct foo_t
{
    int a, b, c;
	float x;
	double r;
	test_s test;
} foo;

REFLECT_STRUCT_BEGIN(foo)
    REFLECT_MEMBER(foo, int, a)
    REFLECT_MEMBER(foo, int, b)
    REFLECT_MEMBER(foo, int, c)
    REFLECT_MEMBER(foo, float, x)
    REFLECT_MEMBER(foo, double, r)
    REFLECT_MEMBER(foo, test_s, test)
REFLECT_STRUCT_END()

typedef struct bar_t
{
	foo f;
	int p;
	float t;
} bar;

attribute attr = { PRINTABLE, NULL};

REFLECT_STRUCT_BEGIN(bar)
    REFLECT_MEMBER_ATTR(bar, foo, f, attr)
    REFLECT_MEMBER(bar, int, p)
    REFLECT_MEMBER_ATTR(bar, float, t, attr)
REFLECT_STRUCT_END()

int main()
{
	REGISTER_STRUCT(foo);
	REGISTER_STRUCT(bar);
	REGISTER_STRUCT(test_s);
	
    reflect_info info = get_reflect_info_bar();
	bar b;
	b.p = 45;
	b.t = 45.2f;
	b.f.a = 2;
	b.f.b = 3;
	b.f.c = 4;
	b.f.x = 5.2;
	
	for (size_t i = 0; i < num_reflected_structs; i++)
	{
		printf("struct : %s\n", reflected_structs[i].struct_name);
	}

	printf("\n=============\n");

	print_struct(info, &b);

    return 0;
}



#include <stdio.h>
#include <string.h>

#include "reflect.h"
#include "attribute.h"

#include "print_struct.h"

#include "test.h"

typedef struct foo_t
{
	int a;
	float x;
	double r;
	test_s test;
} foo;

REFLECT_STRUCT_BEGIN(foo)
	REFLECT_MEMBER(foo, int, a)
	REFLECT_MEMBER(foo, float, x)
	REFLECT_MEMBER(foo, double, r)
	REFLECT_MEMBER(foo, test_s, test)
REFLECT_STRUCT_END()

typedef struct bar_t
{
	foo f;
	float t;
	const char* str;
} bar;

attribute attr = { PRINTABLE, NULL};

REFLECT_STRUCT_BEGIN(bar)
	REFLECT_MEMBER_ATTR(bar, foo, f, attr)
	REFLECT_MEMBER(bar, string, str)
	REFLECT_MEMBER_ATTR(bar, float, t, attr)
REFLECT_STRUCT_END()

int main()
{
	REGISTER_STRUCT(foo);
	REGISTER_STRUCT(bar);
	REGISTER_STRUCT(test_s);
	
	reflect_info info = get_reflect_info_bar();
	bar b;
	b.str = "a string";
	b.t = 45.2f;
	b.f.a = 2;
	b.f.x = 5.2;
	
	for (size_t i = 0; i < num_reflected_structs; i++)
	{
		printf("struct : %s\n", reflected_structs[i].struct_name);
	}

	printf("\n=============\n");

	print_struct(info, &b);

	field const* f_t = get_field(&info, "t");
	float value = * (float*) GET_MEMBER_PTR(&b, *f_t);
	printf("field : %f", value);

	free_registered_structs();
	return 0;
}



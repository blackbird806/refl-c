# refl-c

## How to use

main.c and print_struct.h show most (if not all) the features of the library.

Registering manually reflected structs by calling REGISTER_STRUCT(...) is needed if you need to get struct info with it's name with get_struct_info()  for example.

Types are stored as string so you're not forced to use C types when registering to the reflection.

You can pass an attribute (an arbitrary user provided pointer) to a reflected data with REFLECT_MEMBER_ATTR(...).

Declaring a reflected struct looks like this :
```C
typedef struct foo_t
{
	int a;
 	float x;
} foo;

REFLECT_STRUCT_BEGIN(foo)
	REFLECT_MEMBER(foo, int, a)
	REFLECT_MEMBER(foo, float, x)
REFLECT_STRUCT_END()
```

Then you can get it's info like this :

```C
int main()
{
	REGISTER_STRUCT(foo);
	
	// print all registered structs
	for (size_t i = 0; i < num_reflected_structs; i++)
	{
		printf("struct : %s\n", reflected_structs[i].struct_name);
	}

	reflect_info info = get_reflect_info_foo();
	// or
	info = *get_struct_info("foo"); // works only if foo was registered with REGISTER_STRUCT(foo) 
	get_struct_info("not a true struct"); // will return NULL

	for (int i = 0; i < info.num_fields; i++)
	{
		// print the name and the type of each reflected field
		printf("%s %s : ", info.fields[i].type, info.fields[i].name);
	}

    return 0;
}
```

#ifndef REFLECT_H
#define REFLECT_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct field_t
{
	const char* type;
	const char* name;
	size_t offset;
	void* attr;
} field;

typedef struct reflect_info_t
{
	const char* struct_name;
	size_t num_fields;
	field const* fields;
} reflect_info;

size_t num_reflected_structs = 0;
reflect_info* reflected_structs = NULL;

void add_reflected_struct(reflect_info info)
{
	reflect_info* new_infos = (reflect_info*) malloc(sizeof(reflect_info) * (num_reflected_structs + 1));
	assert(new_infos != NULL);
	if (num_reflected_structs > 0)
	{
		memcpy(new_infos, reflected_structs,  sizeof(reflect_info) * num_reflected_structs);
		free(reflected_structs);
	}
	new_infos[num_reflected_structs] = info;
	reflected_structs = new_infos;
	num_reflected_structs++;
}

reflect_info* get_struct_info(const char* struct_name)
{
	for (size_t i = 0; i < num_reflected_structs; i++)
	{
		if (strcmp(struct_name, reflected_structs[i].struct_name) == 0)
		{
			return &reflected_structs[i];
		}
	}
	return NULL;
}

#define REFLECT_STRUCT_BEGIN(S)\
reflect_info get_reflect_info_##S () \
{ \
	reflect_info info = {};\
	info.struct_name = #S;\
	static const field s_fields[] = { 

#define REFLECT_MEMBER_ATTR(S, T, M, A)\
		{ #T, #M, offsetof(S, M), & (A)},

#define REFLECT_MEMBER(S, T, M)\
		{ #T, #M, offsetof(S, M), NULL},

#define REFLECT_STRUCT_END() \
	};\
	info.fields = s_fields;\
	info.num_fields = sizeof(s_fields) / sizeof(s_fields[0]);\
	return info;\
}

#define GET_MEMBER_PTR(S, F) ((char*)S + F.offset)

#define REGISTER_STRUCT(S) add_reflected_struct(get_reflect_info_##S())

#endif

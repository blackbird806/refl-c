#ifndef PRINT_STRUCT_H
#define PRINT_STRUCT_H

#include <stdio.h>
#include "reflect.h"
#include "attribute.h"

void print_indent(unsigned indent_level)
{
	for (unsigned i = 0; i < indent_level; i++)
	{
		printf("\t");
	}
}

void print_struct_indent(reflect_info info, void* struct_, unsigned indent_level)
{
	print_indent(indent_level);
	printf("struct %s :\n", info.struct_name);
	for (size_t i = 0; i < info.num_fields; i++)
	{
		print_indent(indent_level);

#ifdef REQUIRE_PRINTABLE_ATTRIBUTE // print only fields with the attribute flag PRINTABLE
		attribute* attr = (attribute*) info.fields[i].attr;
		if (attr == NULL || attr->flags & PRINTABLE != PRINTABLE)
			continue;
#endif
		printf("%s %s : ", info.fields[i].type, info.fields[i].name);
		
		void* member_ptr = GET_MEMBER_PTR(struct_, info.fields[i]);
		if (strcmp(info.fields[i].type, "int") == 0)
		{
			int val = *(int*) member_ptr;
			printf("%d", val);
		}
		else if (strcmp(info.fields[i].type, "float") == 0)
		{
			float val = *(float*) member_ptr;
			printf("%f", val);
		}
		else if (strcmp(info.fields[i].type, "double") == 0)
		{
			double val = *(double*) member_ptr;
			printf("%f", val);
		}
		else 
		{
			// if type name is not recognized check if it is a registered struct
			reflect_info* sub_struct_info = get_struct_info(info.fields[i].type);
			if (sub_struct_info) 
			{
				printf("\n");
				print_struct_indent(*sub_struct_info, member_ptr, indent_level + 1);
			}
		}
		printf("\n");
	}
}

void print_struct(reflect_info info, void* struct_)
{
	print_struct_indent(info, struct_, 0);
}

#endif

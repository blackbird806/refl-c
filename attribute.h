#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <stdint.h>

enum attribute_kind_e
{
	PRINTABLE = 1
};

typedef struct attribute_t
{
	uint64_t flags;
	void* userdata;
} attribute;

#endif
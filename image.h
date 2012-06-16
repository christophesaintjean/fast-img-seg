#include <stdlib.h>
#ifndef _IMAGE_H
#define _IMAGE_H
typedef struct {
	size_t w;
	size_t h;
	float * data;
} Image;
#endif
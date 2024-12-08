#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif // MALLOC_H

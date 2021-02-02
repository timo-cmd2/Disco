#ifndef RIFT_API_ALLOC_H
#define RIFT_API_ALLOC_H

#include <stdlib.h>

void *rift_malloc(size_t);
void *rift_realloc(void *, size_t);
void rift_free(void *);

#endif

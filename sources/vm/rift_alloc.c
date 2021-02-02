#include "rift_alloc.h"

void *rift_malloc(size_t size) {
    void *result = malloc(size);
    if (result == NULL) {
        abort();
    }
    return result;
}

void *rift_realloc(void *ptr, size_t new_size) {
    void *result = realloc(ptr, new_size);
    if (result == NULL) {
        abort();
    }
    return result;
}

void rift_free(void *ptr) {
    free(ptr);
}

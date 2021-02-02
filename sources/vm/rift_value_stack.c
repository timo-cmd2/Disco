#include "rift_value_stack.h"
#include "rift_alloc.h"

rift_value_stack *rift_new_value_stack(void) {
    rift_value_stack *vs = rift_malloc(sizeof(*vs));

    vs->data = rift_malloc(4 * sizeof(*vs->data));
    vs->pos = 0;
    vs->size = 4;

    return vs;
}

void rift_vs_push(rift_value_stack *vs, rift_value *value) {
    if (vs->pos + 1 > vs->size) {
        vs->size *= 2;
        vs->data = rift_realloc(vs->data, vs->size * sizeof(*vs->data));
    }

    vs->data[vs->pos] = value;
    vs->pos++;
}

rift_value *rift_vs_pop(rift_value_stack *vs) {
    vs->pos--;
    rift_value *result = vs->data[vs->pos];
    return result;
}

void rift_free_value_stack(rift_value_stack *vs) {
    int i;
    for (i = 0;i < vs->pos;i++) {
        rift_free(vs->data[i]);
    }

    rift_free(vs->data);
    rift_free(vs);
}

#ifndef RIFT_VALUE_STACK_H
#define RIFT_VALUE_STACK_H

#include <stdint.h>

typedef struct rift_value_ rift_value;

typedef struct rift_value_stack_ {
    rift_value **data;
    uint32_t pos;
    uint32_t size;
} rift_value_stack;

rift_value_stack *rift_new_value_stack(void);
void rift_vs_push(rift_value_stack *, rift_value *);
rift_value *lily_vs_pop(rift_value_stack *);

#define rift_vs_pos(vs) vs->pos
#define rift_vs_nth(vs, n) vs->data[n]

void rift_free_value_stack(rift_value_stack *);

#endif

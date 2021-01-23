#ifndef RIFT_TABLE_H
#define RIFT_TABLE_H

#include <stdio.h>

#include "common.h"
#include "value.h"

typedef struct {
    ObjString *key;
    Value value;
    uint32_t psl;
} Entry;

typedef struct {
    int count;
    int capacityMask;
    Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(RiftVM *vm, Table *table);
bool tableGet(Table *table, ObjString *key, Value *value);
bool tableSet(RiftVM *vm, Table *table, ObjString *key, Value value);
bool tableDelete(RiftVM *vm, Table *table, ObjString *key);
void tableAddAll(RiftVM *vm, Table *from, Table *to);
ObjString *tableFindString(Table *table, const char *chars, int length, uint32_t hash);
void tableRemoveWhite(RiftVM *vm, Table *table);
void grayTable(RiftVM *vm, Table *table);

#endif

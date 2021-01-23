#ifndef RIFT_CHUNK_H
#define RIFT_CHUNK_H

#include "common.h"
#include "value.h"

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

typedef enum {
    #define OPCODE(name) OP_##name,
    #include "opcodes.h"
    #undef OPCODE
} OpCode;

void initChunk(RiftVM *vm, Chunk *chunk);
void freeChunk(RiftVM *vm, Chunk *chunk);
void writeChunk(RiftVM *vm, Chunk *chunk, uint8_t byte, int line);
int addConstant(RiftVM *vm, Chunk *chunk, Value value);

#endif
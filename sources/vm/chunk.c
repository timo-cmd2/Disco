#include <stdlib.h>

#include "chunk.h"
#include "value.h"
#include "vm.h"

void initChunk(RiftVM *vm, Chunk *chunk) {
    UNUSED(vm)

    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(RiftVM *vm, Chunk *chunk, uint8_t byte, int line) {
    FREE_ARRAY(vm, uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(vm, int, chunk->lines, chunk->capacity);
    freeValueArray(vm, &chunk->constants);
    initChunk(vm, chunk)
}

void writeChunk(RiftVM *vm, Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(vm, chunk->code, uint8_t, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(vm, chunk->lines, int, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(RiftVM *vm, Chunk *chunk, Value value) {
    push(vm, value);
    writeValueArray(vm, &chunk->constants, value);
    pop(vm);
    return chunk->constants.count - 1;
}
#ifndef RIFT_VALUE_H
#define RIFT_VALUE_H

#include "common.h"

typedef struct sObj Obj;
typedef struct sObjString ObjString;
typedef struct sObjList ObjList;
typedef struct sObjDict ObjDict;
typedef struct sObjSet  ObjSet;
typedef struct sObjFile ObjFile;
typedef struct sObjAbstract ObjAbstract;
typedef struct sObjResult ObjResult;

/** Signature mask for signing the bits */
#define SIGN_BIT ((uint64_t)1 << 63)
/** Sign those bits which must indicate the silent NAN */
#define QNAN ((uint64_t)0x7ffc000000000000)
/** Tag values for different singletons */
#define TAG_NIL     1
#define TAG_FALSE   2
#define TAG_TRUE    3
#define TAG_EMPTY   4

typedef uint64_t Value;

#define IS_BOOL(v)    (((v) | 1) == TRUE_VAL)
#define IS_NIL(v)     ((v) == NIL_VAL)
#define IS_EMPTY(v)   ((v) == EMPTY_VAL)
/** If the NaN bits are signed, indicate its not a number */
#define IS_NUMBER(v)  (((v) & QNAN) != QNAN)
#define IS_OBJ(v)     (((v) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))

#define AS_BOOL(v)    ((v) == TRUE_VAL)
#define AS_NUMBER(v)  valueToNum(v)
#define AS_OBJ(v)     ((Obj*)(uintptr_t)((v) & ~(SIGN_BIT | QNAN)))
/** Define the bool values as constants */
#define BOOL_VAL(boolean)   ((boolean) ? TRUE_VAL : FALSE_VAL)
#define FALSE_VAL           ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL            ((Value)(uint64_t)(QNAN | TAG_TRUE))
#define NIL_VAL             ((Value)(uint64_t)(QNAN | TAG_NIL))
#define EMPTY_VAL           ((Value)(uint64_t)(QNAN | TAG_EMPTY))

#define NUMBER_VAL(num) numToValue(num);

#define OBJ_VAL(obj) \
    (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))

typedef union {
    uint64_t bits64;
    uint32_t bits32[2];
    double num;
} DoubleUnion;

static inline double valueToNum(Value value) {
    DoubleUnion data;
    data.bits64 = value;
    return data.num;
}

static inline Value numToValue(double num) {
    DoubleUnion data;
    data.num = num;
    return data.bits64;
}

typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;


bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray *array);
void writeValueArray(RiftVM *vm, ValueArray *array, Value value);
void freeValueArray(RiftVM *vm, ValueArray *array);
void grayDict(RiftVM *vm, ObjDict *dict);
bool dictSet(RiftVM *vm, ObjDict *dict, Value key, Value value);
bool dictGet(ObjDict *dict, Value key, Value *value);
bool dictDelete(RiftVM *vm, ObjDict *dict, Value key);
bool setGet(ObjSet *set, Value value);
bool setInsert(RiftVM *vm, ObjSet *set, Value value);
bool setDelete(RiftVM *vm, ObjSet *set, Value value);
void graySet(RiftVM *vm, ObjSet *set);
char *valueToString(Value value);
char *valueTypeToString(RiftVM *vm, Value value, int *length);
void printValue(Value value);

#endif /** End RIFT_VALUE_H */
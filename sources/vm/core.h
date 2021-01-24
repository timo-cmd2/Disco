#ifndef RIFT_CORE_H
#define RIFT_CORE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define RIFT_MAJOR_VERSION "0"
#define RIFT_MINOR_VERSION "0"
#define RIFT_PATCH_VERSION "1"
#define RIFT_VERSION_EXTRA "-dev"

#define RIFT_VERSION_FULL "0.0.1-dev"

#define UNUSED(__X__) (void) __X__

#define MAX_ERROR_LEN 256

#define ERROR_RESULT            \
do {                            \
char buf[MAX_ERROR_LEN];        \
getStrerror(buf, errno);        \
return newResultError(vm, buf); \
} while false;

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifdef _WIN32
#define DIR_SEPARATOR '\\'
#define DIR_ALT_SEPARATOR '/'
#define DIR_SEPARATOR_AS_STRING "\\"
#define DIR_SEPARATOR_STRLEN 1
#define PATH_DELIMITER ';'
#define PATH_DELIMITER_AS_STRING ";"
#define PATH_DELIMITER_STRLEN 1
#else
#define HAS_REALPATH
#define DIR_SEPARATOR '/'
#define DIR_SEPARATOR_AS_STRING "/"
#define DIR_SEPARATOR_STRLEN 1
#define PATH_DELIMITER ':'
#define PATH_DELIMITER_AS_STRING ":"
#define PATH_DELIMITER_STRLEN 1
#endif

#ifdef DIR_ALT_SEPARATOR
#define IS_DIR_SEPARATOR(c) ((c) == DIR_SEPARATOR || (c) == DIR_ALT_SEPARATOR)
#else
#define IS_DIR_SEPARATOR(c) (c == DIR_SEPARATOR)
#endif

#define NAN_TAGGING
#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION
#define DEBUG_TRAGE_GC
#define DEBUG_TRACE_MEM

#ifndef _MSC_VER
#define COMPUTED_GOTO
#endif

#undef DEBUG_PRINT_CODE
#undef DEBUG_TRACE_EXECUTION
#undef DEBUG_TRACE_GC
#undef DEBUG_TRACE_MEM

#define UINT8_COUNT (UINT8_MAX + 1)

typedef struct _vm RiftVM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} RiftInterpretResult;

RiftVM *riftInitVM(bool repl, int argc, char *argv[]);
void riftFreeVM(RiftVM *vm);

RiftInterpretResult riftInterpret(RiftVM *vm, char *moduleName, char *source);

/** Opcodes in here *//*
OPCODE(CONSTANT)
OPCODE(NIL)
OPCODE(TRUE)
OPCODE(FALSE)
OPCODE(NEW_LIST)
OPCODE(UNPACK_LIST)
OPCODE(NEW_DICT)
OPCODE(SUBSCRIPT)
OPCODE(SUBSCRIPT_ASSIGN)
OPCODE(SUBSCRIPT_PUSH)
OPCODE(SLICE)
OPCODE(POP)
OPCODE(GET_LOCAL)
OPCODE(SET_LOCAL)
OPCODE(GET_GLOBAL)
OPCODE(GET_MODULE)
OPCODE(DEFINE_MODULE)
OPCODE(DEFINE_OPTIONAL)
OPCODE(SET_MODULE)
OPCODE(GET_UPVALUE)
OPCODE(SET_UPVALUE)
OPCODE(GET_PROPERTY)
OPCODE(GET_PROPERTY_NO_POP)
OPCODE(SET_PROPERTY)
OPCODE(SET_CLASS_VAR)
OPCODE(SET_INIT_PROPERTIES)
OPCODE(GET_SUPER)
OPCODE(EQUAL)
OPCODE(GREATER)
OPCODE(LESS)
OPCODE(ADD)
OPCODE(SUBTRACT)
OPCODE(MULTIPLY)
OPCODE(DIVIDE)
OPCODE(POW)
OPCODE(MOD)
OPCODE(NOT)
OPCODE(NEGATE)
OPCODE(JUMP)
OPCODE(JUMP_IF_FALSE)
OPCODE(JUMP_IF_NIL)
OPCODE(LOOP)
OPCODE(CALL)
OPCODE(INVOKE)
OPCODE(SUPER)
OPCODE(CLOSURE)
OPCODE(CLOSE_UPVALUE)
OPCODE(RETURN)
OPCODE(EMPTY)
OPCODE(CLASS)
OPCODE(SUBCLASS)
OPCODE(END_CLASS)
OPCODE(METHOD)
OPCODE(IMPORT)
OPCODE(IMPORT_BUILTIN)
OPCODE(IMPORT_BUILTIN_VARIABLE)
OPCODE(IMPORT_VARIABLE)
OPCODE(IMPORT_FROM)
OPCODE(IMPORT_END)
OPCODE(USE)
OPCODE(OPEN_FILE)
OPCODE(BREAK)
OPCODE(CLOSE_FILE)
OPCODE(BITWISE_AND)
OPCODE(BITWISE_XOR)
OPCODE(BITWISE_OR)
OPCODE(POP_REPL)*/

/** Values */
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

#define OBJ_VAL(obj) (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))

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

#endif /** End RIFT_COMMON_H */

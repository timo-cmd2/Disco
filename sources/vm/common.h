#ifndef RIFT_COMMON_H
#define RIFT_COMMON_H

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

#endif /** End RIFT_COMMON_H */

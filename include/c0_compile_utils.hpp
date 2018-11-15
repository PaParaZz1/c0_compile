#ifndef _C0_COMPILE_UTILS_H_
#define _C0_COMPILE_UTILS_H_

typedef int compile_errcode;

#define SYSTEM_ERROR 1000
#define COMPILE_ERROR 2000

#define COMPILE_OK 0
#define BAD_FILE_ERROR                  (-(SYSTEM_ERROR | 1))
#define INVALID_STRING_LENGTH_ERROR     (-(SYSTEM_ERROR | 2))
#define UNKNOWN_CHARACTER_ERROR         (-(COMPILE_ERROR | 1))
#define INVALID_DIGIT_ERROR             (-(COMPILE_ERROR | 2))
#define INVALID_DOUBLE_QUOTE_ERROR      (-(COMPILE_ERROR | 3))
#define INVALID_SINGLE_QUOTE_ERROR      (-(COMPILE_ERROR | 4))

#endif // _C0_COMPILE_UTILS_H_

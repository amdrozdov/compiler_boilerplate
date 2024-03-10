#include "engine.h"

#define L_API extern "C"

extern "C++" Engine *hawk_engine;

L_API char* hawk_get_str(char* arg);
L_API char* hawk_is_eq(char *arg1, char* arg2);
L_API char* hawk_is_eq_c(char *arg1, char* arg2);
L_API char* hawk_is_c_eq(char *arg1, char* arg2);
L_API char* hawk_is_gt(char *arg1, char* arg2, int strict);
L_API char* hawk_is_lt(char *arg1, char* arg2, int strict);
L_API char* hawk_is_gt_c(char *arg1, char* arg2, int strict);
L_API char* hawk_is_lt_c(char *arg1, char* arg2, int strict);
L_API char* hawk_is_c_gt(char *arg1, char* arg2, int strict);
L_API char* hawk_is_c_lt(char *arg1, char* arg2, int strict);
L_API char* hawk_concat(char* arg1, char* arg2);
L_API char* hawk_and(char* arg1, char* arg2);
L_API char* hawk_or(char* arg1, char* arg2);

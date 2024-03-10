#include "lang.h"
#include <cassert>
#include <cstring>

std::string get_arg(char* arg){
    // Returns argument by $x
    assert(arg[0] == '$');
    int pos = atoi(arg+1);
    std::string result;
    if(pos > 0){
        result = hawk_engine->get_str(pos-1);
    } else {
        result = hawk_engine->full_str();
    }
    return result;
}

char* is_eq(std::string arg1, std::string arg2){
    // Returns True if arg1 == arg2 in yacc representation
    char* res = "0";
    if(arg1 == arg2){
        res = "1";
    }
    return res;
}

char* is_lte(int a, int b, int strict){
    // Returns True if arg1 <(=) arg2 in yacc representation
    char* res = "0";
    if(strict && (a < b)){
        res = "1";
    }
    if(!strict && (a <= b)){
        res = "1";
    }
    return res;
}

char* is_gte(int a, int b, int strict){
    // Returns True if arg1 >(=) arg2 in yacc representation
    char* res = "0";
    if(strict && (a > b)){
        res = "1";
    }
    if(!strict && (a >= b)){
        res = "1";
    }
    return res;
}

char* hawk_concat(char* arg1, char* arg2){
    // Concats to strings for va_args implementation
    char* res = (char*) malloc(strlen(arg1) + strlen(arg2) + 2);
    strcat(res, arg1);
    strcat(res, ", ");
    strcat(res, arg2);
    return res;
}

char* hawk_and(char* arg1, char* arg2){
    // Implements AND in yacc representation
    char* res = "0";
    if(!strcmp(arg1, "1") && !strcmp(arg2, "1")){
        res = "1";
    }
    return res;
}

char* hawk_or(char* arg1, char* arg2){
    // Implements OR in yacc representation
    char* res = "0";
    if(!strcmp(arg1, "1") && !strcmp(arg2, "1")){
        res = "1";
    }
    if(!strcmp(arg1, "1") && !strcmp(arg2, "0")){
        res = "1";
    }
    if(!strcmp(arg1, "0") && !strcmp(arg2, "1")){
        res = "1";
    }
    return res;
}

// Wrappers for yacc/bison usage
char* hawk_is_eq(char* arg1, char* arg2){
    auto a = get_arg(arg1);
    auto b = get_arg(arg2);
    return is_eq(a, b);
}

char* hawk_is_eq_c(char* arg1, char* arg2){
    auto a = get_arg(arg1);
    auto b = std::string(arg2);
    return is_eq(a, b);
}

char* hawk_is_c_eq(char* arg1, char* arg2){
    auto a = std::string(arg1);
    auto b = get_arg(arg2);
    return is_eq(a, b);
}

char* hawk_is_gt(char* arg1, char* arg2, int strict){
    auto a = atoi(get_arg(arg1).c_str());
    auto b = atoi(get_arg(arg2).c_str());
    return is_gte(a, b, strict);
}

char* hawk_is_lt(char* arg1, char* arg2, int strict){
    auto a = atoi(get_arg(arg1).c_str());
    auto b = atoi(get_arg(arg2).c_str());
    return is_lte(a, b, strict);
}

char* hawk_is_gt_c(char *arg1, char* arg2, int strict){
    auto a = atoi(get_arg(arg1).c_str());
    auto b = atoi(arg2);
    return is_gte(a, b, strict);
}

char* hawk_is_lt_c(char *arg1, char* arg2, int strict){
    auto a = atoi(get_arg(arg1).c_str());
    auto b = atoi(arg2);
    return is_lte(a, b, strict);
}

char* hawk_is_c_gt(char *arg1, char* arg2, int strict){
    auto a = atoi(arg1);
    auto b = atoi(get_arg(arg2).c_str());
    return is_gte(a, b, strict);
}

char* hawk_is_c_lt(char *arg1, char* arg2, int strict){
    auto a = atoi(arg1);
    auto b = atoi(get_arg(arg2).c_str());
    return is_lte(a, b, strict);
}

char* hawk_get_str(char* arg){
    std::string result = get_arg(arg);
    // Need to duplicate memory from string to return back to flex/bison
    char* out = strdup((char*)result.c_str());
    return out;
}
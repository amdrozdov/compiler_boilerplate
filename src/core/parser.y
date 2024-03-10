/* Pre defined structs */
%{
#include <stdio.h>

#define YYSTYPE char*
extern char* hawk_get_str(char *arg);

extern char* hawk_is_eq(char *arg1, char* arg2);
extern char* hawk_is_eq_c(char *arg1, char* arg2);
extern char* hawk_is_c_eq(char *arg1, char* arg2);

extern char* hawk_is_gt(char *arg1, char* arg2, int strict);
extern char* hawk_is_lt(char *arg1, char* arg2, int strict);

extern char* hawk_is_gt_c(char *arg1, char* arg2, int strict);
extern char* hawk_is_lt_c(char *arg1, char* arg2, int strict);
extern char* hawk_is_c_gt(char *arg1, char* arg2, int strict);
extern char* hawk_is_c_lt(char *arg1, char* arg2, int strict);

extern char* hawk_concat(char* arg1, char* arg2);
extern char* hawk_or(char* arg1, char* arg2);
extern char* hawk_and(char* arg1, char* arg2);

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
%}

%define api.value.type { char* }

%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%token OB CB
%token PO PC
%token PVAR
%token SEP
%token EQ LT GT LTE GTE
%token PRINT
%token AND OR

/* Grammar */
%%

hawk:
  | hawk term EOL { printf("%s\n", $2); }
  | hawk va_conds PO term PC EOL { if(!strcmp($2, "1")) { printf("%s\n", $4); } }
;

term: PVAR { $$ = strdup(hawk_get_str($1));}
  | PRINT OB va_args CB { $$ = $3; }
;

va_args: PVAR { $$ = strdup(hawk_get_str($1));}
  | PVAR SEP va_args { $$ = strdup(hawk_concat(hawk_get_str($1), $3));}
;

va_conds: cond { $$ = $1;}
  | cond OR cond { $$ = strdup(hawk_or($1, $3)); }
  | cond AND cond { $$ = strdup(hawk_and($1, $3)); }
  | cond OR va_conds { $$ = hawk_or($1, $3); }
  | cond AND va_conds { $$ = hawk_and($1, $3); }

cond: PVAR EQ PVAR { $$ = strdup(hawk_is_eq($1, $3)); }
  |  PVAR EQ NUMBER { $$ = strdup(hawk_is_eq_c($1, $3)); }
  |  PVAR GT PVAR { $$ = strdup(hawk_is_gt($1, $3, 1)); }
  |  PVAR LT PVAR { $$ = strdup(hawk_is_lt($1, $3, 1)); }
  |  PVAR GTE PVAR { $$ = strdup(hawk_is_gt($1, $3, 0)); }
  |  PVAR LTE PVAR { $$ = strdup(hawk_is_lt($1, $3, 0)); }
  |  PVAR GT NUMBER { $$ = strdup(hawk_is_gt_c($1, $3, 1)); }
  |  PVAR LT NUMBER { $$ = strdup(hawk_is_lt_c($1, $3, 1)); }
  |  PVAR GTE NUMBER { $$ = strdup(hawk_is_gt_c($1, $3, 0)); }
  |  PVAR LTE NUMBER { $$ = strdup(hawk_is_lt_c($1, $3, 0)); }
  |  NUMBER GT PVAR { $$ = strdup(hawk_is_c_gt($1, $3, 1)); }
  |  NUMBER LT PVAR { $$ = strdup(hawk_is_c_lt($1, $3, 1)); }
  |  NUMBER GTE PVAR { $$ = strdup(hawk_is_c_gt($1, $3, 0)); }
  |  NUMBER LTE PVAR { $$ = strdup(hawk_is_c_lt($1, $3, 0)); }
;
%%

/* Code */
void yyerror(char *s){
    fprintf(stderr, "error: %s\n", s);
}
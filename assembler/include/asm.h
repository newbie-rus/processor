#ifndef ASM_H
#define ASM_H

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "../../library/config.h"
#include "../../library/commands.h"
#include "../../library/error.h"
#include "../include/log.h"

#include "../../library/color.h"


// STRUCT LIST
struct Array {
    char   *arr_ptr;
    size_t size_arr;
};

struct Label {
    char name_lab[MAX_SIZE_STR];
    int jmp_id;
};


// FUNCTIONS LIST
int create_byte_code(FILE *fp_src, FILE *fp_res);

int assembly(struct Array *src_struct_arr, struct Array *res_struct_arr, struct Label *arr_lab, int pass_num);

struct Array *ctor_struct_arr(FILE *fp_src);

size_t search_size_file(FILE *fp_src);

int check_num_reg(const char *str);

void create_log_str(char *str, int flag, const char *info);

char *itoa(void *num_ptr, char *str_res, char type);


// DEFINE LIST

#ifdef LOG
    #include "./log.h"

    void print_log_partition(FILE *fp_log);
    void print_log_title(FILE *fp_log);

    #define PRINT_LOG_PARTITION(fp) print_log_partition(fp)
    #define PRINT_LOG_TITLE(fp)     print_log_title(fp)

    FILE *fp_log = NULL;
    #define OPEN_LOG_FIlE()              \
        fp_log = fopen(argv[3], "a");    \
        CHECK_OPEN_FILE(fp_log);

    #define CLOSE_LOG_FILE() fclose(fp_log)
    
    #define PRINT_LOG_STR(fp, first_col, tp1, second_col, tp2, third_col, tp3, fourth_col, tp4)    \
        fprintf(fp, "|%*s%*" tp1 "|",   INDENT_COL, " ", -WIDTH_COL, first_col);                   \
        fprintf(fp, "%*s%*"  tp2 "|",   INDENT_COL, " ", -WIDTH_COL, second_col);                  \
        fprintf(fp, "%*s%*"  tp3 "|",   INDENT_COL, " ", -WIDTH_COL, third_col);                   \
        fprintf(fp, "%*s%*"  tp4 "|\n", INDENT_COL, " ", -WIDTH_COL, fourth_col);                  \
        print_log_partition(fp);
#else
    #define OPEN_LOG_FIlE()          {}
    #define CLOSE_LOG_FILE()         {}
    #define PRINT_LOG_PARTITION(...) {}
    #define PRINT_LOG_TITLE(...)     {}
    #define PRINT_LOG_STR(...)       {}    
#endif // DEBUG

#define NUM_CMD_EQUALS_JMP_OR_CALL(num_cmd) ((num_cmd >= cmd_jmp) && (num_cmd <= cmd_jne)) || (num_cmd == cmd_call)

#define ORG_NOT_CORRECT(org_id, current_pc) ((size_t)org_id < current_pc) || (org_id < 0)

#endif

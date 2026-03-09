// Basic string parsing

#ifndef BSP_H
#define BSP_H

#include "bsp_types.h"
// remember to free after use!

char** split(char* str, char* delim);
void   split_free(char** arr);
char*  trim(char* str); 
int    starts_with(char* str, char* prefix);
int    ends_with(char* str, char* suffix);
char*  join(char** arr, char* delim);
find_result_t* find(char* str, char* pattern);
find_result_t* find_all(char* str, char* pattern);
void  free_findresult(find_result_t* result);
char* to_upper(char* str);
char* to_lower(char* str);
char* replace(char* str, char* old_str, char* new_str);
char* replace_all(char* str, char* old_str, char* new_str);
char* format(char* fmt, ...);
char* collapse_whitespace(char* str);

#endif

// Basic string parsing

#ifndef BSP_H
#define BSP_H

#include "bsp_types.h"
// remember to free after use!

char** split(char* str, char* delim);
void   split_free(char** arr);
char*  trim(char* str); 
int    startsWith(char* str, char* prefix);
int    endsWith(char* str, char* suffix);
char*  join(char** arr, char* delim);
find_result_t* find(char* str, char* pattern);
find_result_t* findAll(char* str, char* pattern);
void  freefindresult(find_result_t* result);
char* toUpper(char* str);
char* toLower(char* str);
char* replace(char* str, char* old_str, char* new_str);
char* replaceAll(char* str, char* old_str, char* new_str);
char* format(char* fmt, ...);
char* collapseWhitespace(char* str);

#endif

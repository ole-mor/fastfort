// Basic string parsing

#ifndef BSP_H
#define BSP_H

typedef struct {
    int start;
    int end; 
    int line;
} strloc_t;

typedef struct {
    int count;
    strloc_t** locations;
} findresult_t;

// remember to free after use!

char** split(char* str, char* delim);
void split_free(char** arr);
char* trim(char* str); 
int startsWith(char* str, char* prefix);
int endsWith(char* str, char* suffix);
char* join(char** arr, char* delim);
findresult_t* find(char* str, char* pattern);
findresult_t* findAll(char* str, char* pattern);
void freefindresult(findresult_t* result);
char* toUpper(char* str);
char* toLower(char* str);
char* replace(char* str, char* old_str, char* new_str);
char* replaceRegex(char* str, char* pattern, char* replacement);

#endif

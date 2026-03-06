# Basic string parsing

## Functions that already is in C standard libraries.
**<string.h>**
- size_t strlen(char* s);
- char*  strcpy(char* dst, char* src)     // copy
- char*  strncpy(char* dst, char* src, size_t n)   // copy up to n chars
- char*  strcat(char* dst, char* src)     // append
- char*  strncat(char* dst, char* src, size_t n)   // append up to n chars
- int    strcmp(char* a, char* b)         // compare
- int    strncmp(char* a, char* b, size_t n)       // compare up to n chars
- char*  strchr(char* s, int c)           // find first char
- char*  strrchr(char* s, int c)          // find last char
- char*  strstr(char* s, char* needle)    // find substring
- size_t strspn(char* s, char* accept)    // length of prefix matching chars
- size_t strcspn(char* s, char* reject)   // length of prefix not matching chars
- char*  strpbrk(char* s, char* accept)   // find first of any char in set
- char*  strtok(char* s, char* delim)     // tokenize (destructive)
- char*  strdup(char* s)                  // malloc+copy
- char*  strndup(char* s, size_t n)       // malloc+copy up to n chars

**<strlib.h>**
- int    atoi(char* s)                            // string to int (no error checking)
- double atof(char* s)                            // string to double (no error checking)
- long   strtol(char* s, char** end, int base)    // string to long (with error checking)
- double strtod(char* s, char** end)              // string to double (with error checking)

**<ctype.h>**
- int isspace(int c)
- int isdigit(int c)
- int isalpha(int c)
- int isalnum(int c)
- int isupper(int c)
- int islower(int c)
- int toupper(int c)
- int tolower(int c)

**<stdio.h>**
- int sprintf(char* buf, char* fmt, ...)           // format into buffer
- int snprintf(char* buf, size_t n, char* fmt, ...) // format into buffer with size limit
- int sscanf(char* s, char* fmt, ...)              // parse from string




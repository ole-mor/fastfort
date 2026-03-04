// Base parsing system
//
// Includes:
// split() + free_split()
// trim() 
// startsWith(), endsWith()
// join()
// find(), findAll()
// match()
// toUpper(), toLower()
// replace(), replacePattern()
//
//
// Existing parsing fn => sscanf, #include <string.h> -> 
// strchr, strstr, strspn, strtok
// strdup, strndup, strlen ? 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/////////////////////////////////////////////

char** split(char* str, char* delim){
    // [NB!] Remember to use split_free after use.
    if (str == NULL || delim == NULL) return NULL;

    // variable definitions
    size_t dlen = strlen(delim);
    int count = 1;
    char* p = str;
    char* start = str;
    int i = 0;

    while((p = strstr(p, delim))) {
        count++;
        p += dlen;
    }
    
    // Allocating space for array of pointers
    char** result = malloc((count+1) * sizeof(char*));
    if (!result) return NULL;

    // Think memory
    // String is "AAA,AAB,AAC" from A100 to A110.
    // strstr(p, delim) if delim == "," -> ",AAB,AAC" : delim at A103
    // strndup(start, p - start) => start = A100, p = A103
    // result at i++ is stored as char* from A100 and and up 3 since 
    // 103 - 100 = 3 
    // then start is set to p = A103 + ',' = 1 = A104. 
    while ((p = strstr(start, delim))) {
        result[i++] = strndup(start, p - start);
        start = p + dlen;
    }
    // Final element and /n to indicate end of array.
    result[i++] = strdup(start);
    result[i] = NULL;

    return result;
}

void split_free(char** arr){
    // We have to deallocate pointers 
    // Then we can deallocate array 
    if(arr == NULL) return NULL;
    for (int i = 0; arr[i] != NULL; i++}
            free(arr[i]);
    free(arr);
}

/////////////////////////////////////////////

char* trim(char* str){
    if (str == NULL) return NULL;
    
    char* start = str;
    char* end = str + strlen(str) - 1;

    // what are we trimming ? ' ', '\t', '\n', '\r', '\v', '\f'
    //
    while (isspace(*start)) start++;
    while (isspace(*end)) end--;

    return strndup(start, end - start + 1)
}

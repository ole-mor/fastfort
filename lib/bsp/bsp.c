// Basic string parsing
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
#include "bsp.h"

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
    if(arr == NULL) return;
    for (int i = 0; arr[i] != NULL; i++)
            free(arr[i]);
    free(arr);
}

/////////////////////////////////////////////

char* trim(char* str){
    if (str == NULL) return NULL;
    
    char* start = str;
    char* end = str + strlen(str) - 1;

    // trims ' ', '\t', '\n', '\r', '\v', '\f'
    
    while (isspace(*start)) start++;
    while (isspace(*end)) end--;

    return strndup(start, end - start + 1);
}

/////////////////////////////////////////////

int startsWith(char* str, char* prefix){
    if (str == NULL || prefix == NULL) return -1;
    if (strlen(prefix) > strlen(str)) return -1;

    // strncmp("hello", "hello", 5)  // 0  — equal
    // strncmp("hello", "hellu", 5)  // < 0  — 'o' < 'u' in ASCII
    // strncmp("hello", "hellu", 4)  // 0    — first 4 chars "hell" are equal

    return strncmp(str, prefix, strlen(prefix)) == 0;    
}

int endsWith(char* str, char* suffix){
    if (str == NULL || suffix == NULL) return -1;
    if (strlen(suffix) > strlen(str)) return -1; // we need to add error handling
    
    char* start_end = str + strlen(str) - strlen(suffix);
    return strncmp(start_end, suffix, strlen(suffix)) == 0;
}

//////////////////////////////////////////////

char* join(char** arr, char* delim){
    if (arr == NULL || delim == NULL) return NULL;
    
    int i = 0;
    int total_len = 0;

    // check total 
    while(arr[i] != NULL) {
        total_len += strlen(arr[i]);
        if (arr[i + 1] != NULL) {
            total_len += strlen(delim);
        }
        i++;
    }

    i = 0;

    char* result = malloc(total_len + 1);
    // if malloc fails.
    if (result == NULL) return NULL;
    result[0] = '\0';

    while (arr[i] != NULL) {
        strcat(result, arr[i]);
        if(arr[i + 1] != NULL) {
            strcat(result, delim);
        }
        i++;
    }
    return result;
}

////////////////////////////////////////////////

findresult_t* find(char* str, char* pattern){
    if (str == NULL || pattern == NULL) return NULL;
    
    findresult_t* result = malloc(sizeof(findresult_t));
    if (result == NULL) return NULL;

    result->count = 0;
    result->locations = NULL;
    int line = 0;
    char* p = str;

    char* match = strstr(str, pattern);
    if (match == NULL) return result;

    strloc_t* loc = malloc(sizeof(strloc_t));
    if (loc == NULL) return result;
    loc->start = match - str; 
    loc->end = match - str + strlen(pattern);

     while((p = strchr(p, '\n')) != NULL && p < match){
        line++;
        p++;
    }

    loc->line = line;
   
    result->locations = malloc(sizeof(strloc_t*) * 2);
    if (result->locations == NULL) return result;
    result->locations[0] = loc;
    result->locations[1] = NULL;

    result->count++;

    return result;
}

findresult_t* findAll(char* str, char* pattern){
    if (str == NULL || pattern == NULL) return NULL;

    findresult_t* result = malloc(sizeof(findresult_t));
    if (result == NULL) return NULL;

    result->count = 0;
    result->locations = NULL;
    int line = 0;
    char* p = str;
    char* p_l = str;
    char* match;
    while ((match = strstr(p, pattern)) != NULL){
        result->locations = realloc(result->locations, sizeof(strloc_t*) * (result->count + 2));

        strloc_t* loc = malloc(sizeof(strloc_t));
        if (loc == NULL) return NULL;
        loc->start = match - str;
        loc->end = match - str + strlen(pattern);
        loc->line = 0;
        
        while((p_l = strchr(p_l, '\n')) != NULL && p_l < match){
            line++;
            p_l++;
        }

        loc->line = line;

        result->locations[result->count] = loc;
        result->count++;
        p = match + strlen(pattern);
    }

    if (result->locations != NULL)
        result->locations[result->count] = NULL;

    return result;
}

void freefindresult(findresult_t* result){
    if (result == NULL) return; 
    if (result->locations != NULL){
        for (int i = 0; i < result->count; i++){
            free(result->locations[i]);
        }
        free(result->locations);
    }
    free(result);
}

////////////////////////////////////////////////


char* toUpper(char* str){
    if (str == NULL) return NULL;
    char* result = strdup(str);
    if (result == NULL) return NULL;
    for (int i = 0; result[i] != '\0'; i++){
        result[i] = toupper(result[i]);
    }
    return result;
}

char* toLower(char* str){
    if (str == NULL) return NULL;
    char* result = strdup(str);
    if (result == NULL) return NULL;
    for (int i = 0; result[i] != '\0'; i++){
        result[i] = tolower(result[i]);
    }
    return result;
}

////////////////////////////////////////////////

char* replace(char* str, char* old_str, char* new_str){
    if (str == NULL || old_str == NULL || new_str == NULL) return NULL;

    char* match = strstr(str, old_str);
    if (match == NULL) return strdup(str);

    int result_len = strlen(str) - strlen(old_str) + strlen(new_len);

    char* result = malloc((result_len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int prefix_len = match - str;
    strncpy(result, str, prefix_len);
    strcpy(result + prefix_len, new_str);
    strcpy(result + prefix_len + strlen(new_str), match + strlen(old_str));

    return result; 
}


char* replaceAll(char* str, char* old_str, char* new_str){
    if (str == NULL || old_str == NULL || new_str == NULL) return NULL;
    
    char* result = strdup(str);
    char* temp;

    while ((strstr(result, old_str)) != NULL){
        temp = replace(result, old_str, new_str);
        free(result);
        current = temp;
    }
    return result;
}


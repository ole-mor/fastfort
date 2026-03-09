// Basic file interfaces

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include "bsp.h"
#include "./bfi_macho_config.h"
#include "./bfi.h"

// csv
char** csv_r(const char* filename, int start, int end){
    if (filename == NULL) return NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) return NULL;
    
    char c;
    int total_lines = 0;
    while ((c = fgetc(file)) != EOF)
        if (c == '\n') total_lines ++;
    rewind(file);

    if (start < 0 || start > total_lines) return NULL;
    if (end < start || end > total_lines) return NULL;
    int num_lines = end - start;

    char** result = malloc((num_lines + 1) * sizeof(char*));
    if (result == NULL) { 
        fclose(file); 
        return NULL; }


    char tmp[1024];
    for (int i = 0; i < start; i++)
        fgets(tmp, sizeof(tmp), file); // reads, then discards. Now starts reading from start;

    for (int i = 0; i < num_lines; i++){
        long pos = ftell(file);
        int len = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF) len++;
        fseek(file, pos, SEEK_SET);

        result[i] = malloc(len + 1);
        if (result[i] == NULL) { 
            csv_free(result); 
            fclose(file); 
            return NULL; 
        }
        fgets(result[i], len + 1, file);
        fgetc(file);
    }

    result[num_lines] = NULL; // sets last line as NULL;
    fclose(file);
    return result;
}

// ...


void csv_free(char** data){
    if (data == NULL) return;

    int i = 0;
    while (data[i] != NULL){
        free(data[i]);
        i++;
    }
    free(data);
}




// Mach-O -> structured binary for macOS
void macho_w(char* payload){
    char* data = payload;
    uint32_t datalen = (uint32_t)strlen(data) + 1;
    uint32_t cmdsize = sizeof(macho_load_cmd) + sizeof(macho_segment) + sizeof(macho_section); 
    uint32_t sizeofcmds = cmdsize;
    uint32_t data_offset = sizeof(macho_header) + sizeofcmds;

    macho_header   hdr  = macho_default_header(1, sizeofcmds);
    macho_load_cmd lc   = { LC_SEGMENT_64, cmdsize }; 
    macho_segment  seg  = macho_text_segment(datalen, data_offset, datalen, 1);
    macho_section  sect = macho_cstring_section(datalen, data_offset);

    FILE* file = fopen(MACHO_OUTPUT_PATH, "wb");
    if (!file) { perror("fopen"); return; } // take inspiration from this :) 

    fwrite(&hdr,  sizeof(hdr),  1, file);
    fwrite(&lc,   sizeof(lc),   1, file);
    fwrite(&seg,  sizeof(seg),  1, file);
    fwrite(&sect, sizeof(sect), 1, file);
    fwrite(data,  datalen,      1, file);

    fflush(file);
    fsync(fileno(file));
    fclose(file);
}

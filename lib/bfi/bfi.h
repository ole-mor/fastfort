#ifndef BFI_H
#define BFI_H

//csv crud operations
void csv_a(const char* filename, const char* fmt, int line, ...); // line to csv file at line (line = -1 means at bottom)
void csv_w(const char* filename, char** rows); // rewrites the whole file
char** csv_r(const char* filename, int start, int end);
void csv_d(const char* filename, int row, int col);
void csv_free(char** data);

// macho
void macho_w(char* payload);

#endif

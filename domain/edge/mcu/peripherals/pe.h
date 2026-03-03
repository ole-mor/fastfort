#ifndef PE_H
#define PE_H

typedef struct {
    char id[37];           
    char label[64];       
    char manufacturer[64]; 
    char model[32];
    char hw_revision[16];
    char location[128];  
    char installed[11]; 
} identity_t;

#endif

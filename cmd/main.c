#include <stdio.h>

#include "../lib/mm/mm.h"
#include "../lib/mo/mo.h"
#include "../lib/res/res.h"
#include "../lib/bsp/bsp.h"

int main(void) {

    char** t = split("Hello world", " ");
    printf("%s", t[0]);
    split_free(t);
    

    mo_t test = {.obj = "test"};
    result_t r1 = process(test, mo_t);
    if (RES_IS_ERR(r1)) {
        printf("Error: %d '%s' %s %d\n", r1.code, r1.message, r1.file, r1.line);
    }
    return 0;
}

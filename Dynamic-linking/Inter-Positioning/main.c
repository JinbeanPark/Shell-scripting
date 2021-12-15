#include <stdio.h>
#include <stdlib.h>

#ifdef COMPILE_TIME
#include "debug_malloc.h"
#endif

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int num_bytes = atoi(argv[i]);
        void *p = malloc(num_bytes);
        free(p);
    }
    return(0); 
}



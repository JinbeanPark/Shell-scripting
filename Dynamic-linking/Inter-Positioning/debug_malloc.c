/* debug_malloc.c */

#ifdef COMPILE_TIME
#include <stdio.h>
#include <stdlib.h>

void *debug_malloc(size_t size) {
    void *ptr = malloc(size); 
    printf("malloc(%d)=%p\n", (int)size, ptr); 
    return ptr;
}

void debug_free(void *ptr) {
    free(ptr);
    printf("free(%p)\n", ptr);
}
#endif


#ifdef LINK_TIME
#include <stdio.h>

void *__real_malloc(size_t size); 
void __real_free(void *ptr);

void *__wrap_malloc(size_t size) {
    void *ptr = __real_malloc(size); 
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}

void __wrap_free(void *ptr) {
    __real_free(ptr); 
    printf("free(%p)\n", ptr); }
#endif

#ifdef LOAD_TIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void *malloc(size_t size) {
    void *(*mallocp)(size_t size);
    char *error;
    mallocp = dlsym(RTLD_NEXT, "malloc"); 
    if ((error = dlerror())) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    char *ptr = mallocp(size); 
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}


void free(void *ptr) {
    void (*freep)(void *) = NULL; 
    char *error;
    if (!ptr){
        return;
    }
    freep = dlsym(RTLD_NEXT, "free"); 
    if ((error = dlerror())) {
        fprintf(stderr, "%s\n", error);
        exit(1); 
    }
    freep(ptr); /* Call libc free */
    printf("free(%p)\n", ptr); 
}
#endif



/* debug_malloc.h */

#define malloc(size) debug_malloc(size) 
#define free(ptr) debug_free(ptr)

void *debug_malloc(size_t size); 
void debug_free(void *ptr);


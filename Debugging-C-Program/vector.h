#ifndef CS35L_LAB4_VECTOR_H
#define CS35L_LAB4_VECTOR_H

#include <stdlib.h>

typedef struct IntVector IntVector;

IntVector *int_vec(void);

int int_vec_get(IntVector const *const vec, size_t const index);

size_t int_vec_len(IntVector const *const vec);

void int_vec_push(IntVector *vec, int item);

void int_vec_free(IntVector *vec);

#endif //CS35L_LAB4_VECTOR_H

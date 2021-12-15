#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main() {
    IntVector *vec = int_vec();
    if (!vec) {
        fprintf(stderr, "failed to create int vector\n");
        exit(EXIT_FAILURE);
    }
    int_vec_push(vec, 9);
    int_vec_push(vec, 3);
    int_vec_push(vec, -10);
    int_vec_push(vec, 7);
    int_vec_push(vec, 100);
    int_vec_push(vec, 23);
    int_vec_push(vec, 6);
    int_vec_push(vec, 7);
    int_vec_push(vec, 8);
    int_vec_push(vec, 9);
    int_vec_push(vec, 10);
    int_vec_push(vec, 11);
    int_vec_push(vec, 12);
    int_vec_push(vec, 13);
    int_vec_push(vec, 14);
    int_vec_push(vec, 15);
    int_vec_push(vec, 16);
    int_vec_push(vec, 17);
    int_vec_push(vec, 18);
    int_vec_push(vec, 19);
    int_vec_push(vec, 20);
    int_vec_push(vec, 21);
    int_vec_push(vec, 22);
    int_vec_push(vec, 23);
    int_vec_push(vec, 24);
    int_vec_push(vec, 25);

    size_t len = int_vec_len(vec);

    printf("\n=> checking the vector's content\n");
    size_t i;
    for (i = 0; i < len; ++i) {
        printf("vec[%zu]: %d\n", i, int_vec_get(vec, i));
    }
    int_vec_free(vec);

    return 0;
}

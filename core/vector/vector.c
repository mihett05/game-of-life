#include "vector.h"

vector_t vector_new(int x, int y) {
    vector_t vec = {
        .x = x,
        .y = y
    };

    return vec;
}

double vector_len(vector_t vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

vector_t vector_add(vector_t vec1, vector_t vec2) {
    return vector_new(
        vec1.x + vec2.x,
        vec1.x + vec2.y
    );
}

vector_t vector_sub(vector_t vec1, vector_t vec2) {
    return vector_new(
        vec1.x - vec2.x,
        vec1.x - vec2.y
    );
}

vector_t vector_mul(vector_t vec, int scalar) {
    return vector_new(vec.x * scalar, vec.y * scalar);
}
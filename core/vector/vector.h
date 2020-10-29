//
// Created by admin on 13.10.2020.
//

#ifndef CORE_RAY_VECTOR_H
#define CORE_RAY_VECTOR_H

#include <math.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
    int x;
    int y;
} vector_t;

vector_t vector_new(int x, int y);
double vector_len(vector_t vec1);

vector_t vector_add(vector_t vec1, vector_t vec2);
vector_t vector_sub(vector_t vec1, vector_t vec2);

vector_t vector_mul(vector_t vec, int scalar);

#endif //CORE_RAY_VECTOR_H

#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t cell;
} field_update_t;

typedef struct {
    uint8_t** map;
    field_update_t* updates;
    uint32_t updates_count;
    uint32_t updates_size;
    uint16_t w;
    uint16_t h;
} field_t;

field_t* field_new(uint16_t w, uint16_t h);

uint8_t field_get_cell(field_t* field, int x, int y);
void field_set_cell(field_t* field, int x, int y, uint8_t value);

void field_handle(field_t* field);
uint8_t cell_handle(uint8_t cell, uint8_t neighbours);

#endif //LIFE_FIELD_H

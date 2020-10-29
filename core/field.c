#include "field.h"
#include <windows.h>

field_t* field_new(uint16_t w, uint16_t h) {
    field_t* field = (field_t*)malloc(sizeof(field_t));
    field->map = (uint8_t**)calloc(sizeof(uint8_t*), h);

    for (size_t i = 0; i < h; ++i) {
        field->map[i] = (uint8_t*)calloc(sizeof(uint8_t), w);
    }

    field->updates_size = (uint32_t)w * (uint32_t)h;
    field->updates_count = 0;
    field->updates = (field_update_t*)calloc(sizeof(field_update_t), field->updates_size);

    field->w = w;
    field->h = h;

    return field;
}

void field_set_cell(field_t* field, int x, int y, uint8_t value) {
    int real_y = (y < 0? field->h - 1 + y : y) % field->h;
    int real_x = (x < 0? field->w - 1 + x : x) % field->w;
    field->map[real_y][real_x] = value;
}

uint8_t field_get_cell(field_t* field, int x, int y) {
    int real_y = (y < 0? field->h - 1 + y : y) % field->h;
    int real_x = (x < 0? field->w - 1 + x : x) % field->w;

    return field->map[real_y][real_x];
}

uint8_t cell_handle(uint8_t cell, uint8_t neighbours) {
    if (cell == 0) { // EMPTY CELL
        if (neighbours == 3) {
            cell = 1;
        }
    } else if (cell == 1) {// LIFE CELL
        if (neighbours != 2 && neighbours != 3) {
            cell = 0;
        }
    }

    return cell;
}

void field_handle(field_t* field) {
    memset(field->updates, 0, sizeof(field_update_t) * field->updates_count);
    field->updates_count = 0;

    for (uint16_t y = 0; y < field->h; ++y) {
        for (uint16_t x = 0; x < field->w; ++x) {
            uint8_t cell = field_get_cell(field, x, y);
            uint8_t neighbours = 0;

            for (int cy = -1; cy <= 1; ++cy) {
                for (int cx = -1; cx <= 1; ++cx) {
                    if (cy == 0 && cx == 0) continue;

                    neighbours += field_get_cell(field, x + cx, y + cy);
                }
            }

            uint8_t old_cell = cell;
            cell = cell_handle(cell, neighbours);

            if (cell != old_cell) {
                field_update_t update = {
                    .x = x,
                    .y = y,
                    .cell = cell
                };
                field->updates[field->updates_count] = update;
                ++field->updates_count;
            }
        }
    }

    for (size_t i = 0; i < field->updates_count; ++i) {
        field_update_t update = field->updates[i];
        field_set_cell(field, update.x, update.y, update.cell);
    }
}
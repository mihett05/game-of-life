#ifndef LIFE_APP_H
#define LIFE_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#include <SDL2/SDL.h>

#include "field.h"

typedef struct {
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Event event;

    SDL_TimerID field_timer_id;
    uint16_t cell_size;
    field_t* field;

    _Bool is_active;
    _Bool is_paused;
} app_t;

app_t* app_new(uint16_t width, uint16_t height);
void app_draw(app_t* app);
void app_loop(app_t* app);

#endif //MATH_GRAPHIC_APP_H

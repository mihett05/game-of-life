#include <stdio.h>
#include <SDL2/SDL.h>

#include "core/app.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GL_LoadLibrary(NULL) == 0) {
        app_t* app = app_new(800, 800);
        app_loop(app);
    } else {
        printf("Can't initialize SDL2\n");
    }
    return 0;
}

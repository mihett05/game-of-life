#include "app.h"

Uint32 field_cb(Uint32 interval, app_t* app) {
    field_handle(app->field);
    return interval;
}

app_t* app_new(uint16_t width, uint16_t height) {
    app_t* app = (app_t*)malloc(sizeof(app_t));
    memset(app, 0, sizeof(app_t));

    app->window = SDL_CreateWindow(
        "App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN
    );
    if (app->window != NULL) {
        app->surface = SDL_GetWindowSurface(app->window);
        app->renderer = SDL_CreateRenderer(
            app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

        app->is_active = 1;
        app->is_paused = 1;
        app->field = field_new(64, 64);
        app->cell_size = app->surface->w / app->field->w;

        return app;
    } else {
        printf("Can't create window\n");
        return NULL;
    }
}

void app_draw(app_t* app) {
    SDL_SetRenderDrawColor(app->renderer, 0x0, 0x0, 0x0, 0xff);
    SDL_RenderClear(app->renderer);

    SDL_Rect r = {
        .x = 0,
        .y = 0,
        .w = app->cell_size,
        .h = app->cell_size
    };

    for (uint16_t y = 0; y < app->field->h; ++y) {
        for (uint16_t x = 0; x < app->field->w; ++x) {
            if (field_get_cell(app->field, x, y) == 1) {
                r.x += 1;
                r.y += 1;
                r.w -= 1;
                r.h -= 1;

                SDL_SetRenderDrawColor(app->renderer, 0x00, 0xff, 0x00, 0xff);
                SDL_RenderFillRect(app->renderer, &r);

                r.x -= 1;
                r.y -= 1;
                r.w += 1;
                r.h += 1;
            } else {
                SDL_SetRenderDrawColor(app->renderer, 0x69, 0x69, 0x69, 0xff);
                SDL_RenderDrawRect(app->renderer, &r);
            }

            r.x += app->cell_size - 1;
        }
        r.x = 0;
        r.y += app->cell_size - 1;
    }
    if ((app->event.type == SDL_MOUSEMOTION || app->event.type == SDL_MOUSEBUTTONDOWN) && app->event.button.button == SDL_BUTTON_LEFT) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        field_set_cell(
            app->field, x / (app->cell_size - 1),
            y / (app->cell_size - 1),
            1
        );
    }

    SDL_RenderPresent(app->renderer);
}

void app_loop(app_t* app) {
    while (app->is_active) {
        while (SDL_PollEvent(&(app->event)) != 0) {
            if (app->event.type == SDL_QUIT) {
                app->is_active = 0;
            } else if (app->event.type == SDL_KEYDOWN && app->event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if (app->is_paused) {
                    app->field_timer_id = SDL_AddTimer(200, (SDL_TimerCallback)field_cb, app);
                } else {
                    SDL_RemoveTimer(app->field_timer_id);
                }
                app->is_paused = !app->is_paused;
            }
        }

        app_draw(app);
        SDL_Delay(20);
    }
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

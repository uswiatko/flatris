#include "app.h"

int core_app::on_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "flatris - experimental version",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480, 0);
    if (!window)
        return -1;

    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_SOFTWARE);
    if (!renderer)
        return -1;

    return 0;
}

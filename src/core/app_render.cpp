#include "app.h"

void core_app::on_render()
{
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80,
            SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

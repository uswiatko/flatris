#include "app.h"

void core_app::on_cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

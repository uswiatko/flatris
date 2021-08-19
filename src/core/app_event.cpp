#include "app.h"

void core_app::on_event(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
        running = false;
}

#include "app.h"

core_app::core_app()
{
    window = NULL;
    renderer = NULL;

    running = true;
}

int core_app::on_execute()
{
    if (on_init())
        return -1;
    
    SDL_Event event;

    while (running) {
        while(SDL_PollEvent(&event))
            on_event(&event);

        on_loop();
        on_render();
    }

    on_cleanup();

    return 0;
}

int main(int argc, char *argv[])
{
    core_app app;

    return app.on_execute();
}

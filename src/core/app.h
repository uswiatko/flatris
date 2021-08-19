#ifndef _APP_H_
#define _APP_H_

#include "SDL.h"

class core_app {
    private:
        bool running;

        SDL_Window *window;
        SDL_Renderer *renderer;

    public:
        core_app();

        int on_execute();
        int on_init();
        void on_event(SDL_Event *event);
        void on_loop();
        void on_render();
        void on_cleanup();
};
#endif

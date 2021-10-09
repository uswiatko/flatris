#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include "SDL.h"

class TetrisGame {
    public:
        TetrisGame(int w, int h);

        void key_pressed(SDL_Keycode key);
        void loop();
        void render(SDL_Renderer *renderer);

    private:
        int _w, _h;
};

#endif

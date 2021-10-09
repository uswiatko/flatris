#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include "SDL.h"

#include "map/tetris_map.h"

class TetrisGame {
    public:
        TetrisGame(int w, int h, int block);

        void key_pressed(SDL_Keycode key);
        void loop();
        void render(SDL_Renderer *renderer);

    private:
        TetrisMap _map;
        int _w, _h;
};

#endif

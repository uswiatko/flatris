#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include "SDL.h"

#include "text/text_manager.h"
#include "map/tetris_map.h"

class TetrisGame {
    public:
        TetrisGame(int w, int h, int block, SDL_Renderer *renderer);

        void key_pressed(SDL_Keycode key);
        void loop();
        void render();
        int set_new_active();

    private:
        SDL_Renderer *_renderer;
        TextManager _text;

        TetrisMap _map;
        int _w, _h;
        int _block;
        int _game_speed = 10;
        int _points = 0;
        bool _blocked = false;
};

#endif

#ifndef _TETRIS_MAP_H_
#define _TETRIS_MAP_H_

#include "SDL.h"

#include <array>

class TetrisMap {
    public:
        TetrisMap(int block_size);

        void render(SDL_Renderer *renderer);

        std::array<std::array<int, 10>, 20> loc;

    private:
        int _block_size;
};

#endif

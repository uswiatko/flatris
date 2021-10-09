#ifndef _TETRIS_MAP_H_
#define _TETRIS_MAP_H_

#include "SDL.h"

#include <array>

#include "blocks/tetris_block.h"

class TetrisMap {
    public:
        TetrisMap(int block_size);

        void render(SDL_Renderer *renderer);

        int insert(TetrisBlock &block);
        int move(TetrisBlock &block, int x, int y);

        std::array<std::array<int, 10>, 20> loc;

    private:
        void clear();

        int _block_size;
};

#endif

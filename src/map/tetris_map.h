#ifndef _TETRIS_MAP_H_
#define _TETRIS_MAP_H_

#include "SDL.h"

#include <array>

#include "blocks/tetris_block.h"

class TetrisMap {
    public:
        TetrisMap(int block_size);

        void render(SDL_Renderer *renderer);

        int insert_new(TetrisBlock &block);
        int move(TetrisBlock &block, int x, int y);
        int rotate(TetrisBlock &block);

        int find_full(TetrisBlock &block);
        void clear();

        std::array<std::array<int, 10>, 20> loc;

    private:
        void delete_full(int start, int &points);
        void move_shadow(TetrisBlock &block);
        int insert(TetrisBlock &block);

        int _block_size;
        TetrisBlock _shadow;
};

#endif

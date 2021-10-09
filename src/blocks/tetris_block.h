#ifndef _TETRIS_BLOCK_H_
#define _TETRIS_BLOCK_H_

#include <vector>

struct TetrisBlockPos {
    int row;
    int col;
};

class TetrisBlock {
    public:
        TetrisBlock() { };
        TetrisBlock(std::vector<struct TetrisBlockPos> blocks);

        std::vector<struct TetrisBlockPos> elements;

    private:
};

#endif

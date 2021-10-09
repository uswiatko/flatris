#include "tetris_game.h"

#include <algorithm>
#include <iostream>

#include "blocks/tetris_block.h"

static TetrisBlock Z_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {1, 4}, {1, 5}, {0, 5}, {0, 6} });
static TetrisBlock S_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {0, 4}, {0, 5}, {1, 5}, {1, 6} });
static TetrisBlock O_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {1,5}, {0,5}, {0,6}, {1,6} });
static TetrisBlock L_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {0, 4}, {1, 4}, {2, 4}, {2, 5} });
static TetrisBlock J_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {0,5}, {1,5}, {2,5}, {2,4} });
static TetrisBlock T_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {0,4}, {0,5}, {0,6}, {1,5} });
static TetrisBlock I_block = TetrisBlock(std::vector<struct TetrisBlockPos>
        { {0, 3}, {0, 4}, {0, 5}, {0, 6} });
static struct TetrisBlock *blocks_tab[] = {
    &S_block, &Z_block, &O_block, &L_block, &J_block, &T_block, &I_block
};
static TetrisBlock active;

TetrisGame::TetrisGame(int w, int h, int block)
    : _w(w), _h(h), _map(TetrisMap(block))
{
    set_new_active();
}

int TetrisGame::set_new_active()
{
    TetrisBlock *block = blocks_tab[std::rand() % std::size(blocks_tab)];

    if (_map.insert(*block))
        return -1;
    
    active = TetrisBlock(*block);
    return 0;
}

void TetrisGame::key_pressed(SDL_Keycode key)
{
    switch(key)
    {
    case SDLK_RIGHT:
        _map.move(active, 0, 1);
        break;
    case SDLK_LEFT:
        _map.move(active, 0, -1);
        break;
    case SDLK_UP:
        break;
    case SDLK_DOWN:
        break;
    case SDLK_d:
        break;
    }
}

void TetrisGame::loop()
{
    static int loop_cnt;

    if (loop_cnt++ > _game_speed) {
        if (_map.move(active, 1, 0)) {
            if (set_new_active())
                std::cout << "End game";
        }
        loop_cnt = 0;
    }
}

void TetrisGame::render(SDL_Renderer *renderer)
{
    _map.render(renderer);
}

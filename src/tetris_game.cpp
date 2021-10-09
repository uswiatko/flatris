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
static TetrisBlock *next_one;

static TetrisBlock *_get_random_next()
{
    return blocks_tab[std::rand() % std::size(blocks_tab)];
}

TetrisGame::TetrisGame(int w, int h, int block,
                       SDL_Renderer *renderer)
    : _w(w), _h(h), _map(TetrisMap(block)), _block(block)
    , _renderer(renderer), _text(TextManager(renderer))
{
    next_one = _get_random_next();
    set_new_active();
}

int TetrisGame::set_new_active()
{
    TetrisBlock *block = next_one; 

    if (_map.insert_new(*block))
        return -1;
    
    active = TetrisBlock(*block);
    next_one = _get_random_next();
    return 0;
}

void TetrisGame::key_pressed(SDL_Keycode key)
{
    if (_blocked)
        return;

    switch(key)
    {
    case SDLK_RIGHT:
        _map.move(active, 0, 1);
        break;
    case SDLK_LEFT:
        _map.move(active, 0, -1);
        break;
    case SDLK_DOWN:
        _blocked = true;
        break;
    case SDLK_r:
        _map.rotate(active);
        break;
    }
}

static int _points_to_game_speed(int points)
{
    if (points < 100)
        return 10 - (points / 10);
    return 1;
}

void TetrisGame::loop()
{
    static int loop_cnt;

    if (loop_cnt++ > _game_speed || _blocked) {
        if (_map.move(active, 1, 0)) {
            _blocked = false;

            if (set_new_active()) {
                _map.clear();
                set_new_active();
                _game_speed = 10;
                _points = 0;
            }

            _points += _map.find_full(active);
            _text.new_points(_points);
            _game_speed = _points_to_game_speed(_points);
        }
        loop_cnt = 0;
    }
}

void TetrisGame::render()
{
    int off_x = 450;
    int off_y = 50;

    _map.render(_renderer);
    _text.render();

    for (const auto &el : next_one->elements) {
            SDL_Rect rect = { el.row * _block + off_x,
                              (el.col - 3) * _block + off_y, _block, _block };

            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(_renderer, &rect);

            SDL_Rect fill_rect = { el.row * _block + 1 + off_x,
                                   (el.col - 3) * _block + 1 + off_y,
                                   _block-2, _block-2 };

            SDL_SetRenderDrawColor(_renderer, 255, 128, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(_renderer, &fill_rect);
    }
}

#include "tetris_game.h"

TetrisGame::TetrisGame(int w, int h, int block)
    : _w(w), _h(h), _map(TetrisMap(block))
{
}

void TetrisGame::key_pressed(SDL_Keycode key)
{
    switch(key)
    {
    case SDLK_RIGHT:
        break;
    case SDLK_LEFT:
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

}

void TetrisGame::render(SDL_Renderer *renderer)
{
    _map.render(renderer);
}

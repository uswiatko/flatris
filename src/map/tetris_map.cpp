#include "tetris_map.h"

#include <iostream>

TetrisMap::TetrisMap(int block_size)
    : _block_size(block_size)
{
}

void TetrisMap::render(SDL_Renderer *renderer)
{
    for (int i = 0; i < loc.size(); i++) {
        for (int j = 0; j < loc[i].size(); j++) {
            SDL_Rect rect = { j * _block_size, i * _block_size,
                              _block_size, _block_size };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

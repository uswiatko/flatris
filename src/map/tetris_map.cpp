#include "tetris_map.h"

#include <iostream>

TetrisMap::TetrisMap(int block_size)
    : _block_size(block_size)
{
    clear();
}

void TetrisMap::render(SDL_Renderer *renderer)
{
    for (int i = 0; i < loc.size(); i++) {
        for (int j = 0; j < loc[i].size(); j++) {
            SDL_Rect rect = { j * _block_size, i * _block_size,
                              _block_size, _block_size };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255,
                                   SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rect);

            if (loc[i][j]) {
                SDL_Rect fill_rect = { j * _block_size + 1,
                                       i * _block_size + 1,
                                       _block_size-2, _block_size-2 };

                SDL_SetRenderDrawColor(renderer, 0, 0, 255,
                                       SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &fill_rect);
            }

        }
    }
}

int TetrisMap::insert(TetrisBlock &block)
{
    for (auto &el : block.elements) {
        if (loc[el.row][el.col])
            return -1;
    }

    for (auto &el : block.elements)
        loc[el.row][el.col] = 1;

    return 0;
}

int TetrisMap::move(TetrisBlock &block, int x, int y)
{
    /* delete to avoid detecting collison with the same
     * blocks */
    for (auto &el : block.elements) {
        loc[el.row][el.col] = 0;
    }

    for (auto &el : block.elements) {
        if (el.row + x < 0 || el.row + x >= 20 ||
            el.col + y < 0 || el.col + y >= 10)
            goto err;

        if (loc[el.row + x][el.col + y])
            goto err;
    }

    for (auto &el : block.elements) {
        el.row += x;
        el.col += y;
        loc[el.row][el.col] = 1;
    }

    return 0;

err:
    insert(block);
    return -1;
}

void TetrisMap::clear()
{
    for (auto &row : loc)
        for (auto &col : row)
            col = 0;
}

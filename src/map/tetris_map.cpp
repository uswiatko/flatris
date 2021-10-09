#include "tetris_map.h"

#include <algorithm>
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
    for (auto &el : block.elements)
        loc[el.row][el.col] = 0;

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

int TetrisMap::rotate(TetrisBlock &block)
{
    for (auto &el : block.elements)
        loc[el.row][el.col] = 0;

    std::array<std::array<int, 4>, 4> temp{};

    int min_row = 20, min_col = 10, max_row = 0, max_col = 0;
    for (const auto &el : block.elements) {
        if (el.row < min_row)
            min_row = el.row;
        if (el.row > max_row)
            max_row = el.row;
        if (el.col < min_col)
            min_col = el.col;
        if (el.col > max_col)
            max_col = el.col;
    }

    std::cout << "r1 " << min_row << " r2 " << max_row << " c1 " << min_col
              << " c2 " << max_col << "\n";

    int start_row = 1, start_col = 1;
    if (max_row - min_row > 2 || min_row == 0)
        start_row = 0;
    if (max_row == 19)
        start_row = 3 - (19 - min_row);
    if (max_col - min_col > 2 || min_col == 0)
        start_col = 0;
    if (max_col == 9)
        start_col = 3 - (9 - min_col); 

    std::cout << "start col " << start_col << " start_row " << start_row << "\n";
    int offset_row = min_row, offset_col = min_col;

    for (const auto &el : block.elements)
        temp[start_col + el.col - offset_col][start_row + el.row - offset_row] = 1;
    std::reverse(temp.begin(), temp.end());

    std::vector<struct TetrisBlockPos> temp_blocks;
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i].size(); j++) {
            if (temp[i][j]) {
                temp_blocks.push_back({i - start_row + offset_row,
                                       j - start_col + offset_col});
                std::cout << "row " << i - start_row + offset_row <<
                             " col " << j - start_col + offset_col << "\n";
            }
        }
    }

    TetrisBlock temp_block = TetrisBlock(temp_blocks);
    if (!insert(temp_block)) {
        for (int i = 0; i < block.elements.size(); i++) {
            block.elements[i].row = temp_block.elements[i].row;
            block.elements[i].col = temp_block.elements[i].col;
        }

        return 0;
    }

    insert(block);
    return -1;
}

void TetrisMap::delete_full(int start, int &points)
{
    int i;

    std::cout << "start " << start << "\n";
    for (i = start; i >= 0; i--) {
        
        if (std::count(loc[i].begin(), loc[i].end(), 1) == 10) {
            points += 10;
            for (int j = i - 1; j >= 0; j--) {
                for (int k = 0; k < loc[j].size(); k++)
                    loc[j+1][k] = loc[j][k];
            }
            break;
        }
    }

    if (i == -1)
        return;

    delete_full(i, points);
}

int TetrisMap::find_full(TetrisBlock &block)
{
    int points = 0;

    for (auto &el : block.elements)
        loc[el.row][el.col] = 0;

    delete_full(loc.size() - 1, points);

    insert(block);

    return points;
}

void TetrisMap::clear()
{
    for (auto &row : loc)
        for (auto &col : row)
            col = 0;
}

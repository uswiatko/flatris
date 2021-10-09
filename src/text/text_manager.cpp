#include "text_manager.h"

#include <iostream>

TextManager::TextManager(SDL_Renderer *renderer)
    : _renderer(renderer)
{
    TTF_Init();
    _font = TTF_OpenFont("/usr/share/fonts/liberation-mono/LiberationMono-Bold.ttf", 24);

    if (!_font)
        std::cout << "Can't load font\n";

    fill_texture_and_rect("Kolejka:", 420, 6, &_next_tex, &_next_rec);
    fill_texture_and_rect("Wynik: ", 420, 770, &_result_tex, &_result_rec);
    fill_texture_and_rect("0", _result_rec.x + _result_rec.w + 10,
                         _result_rec.y, &_points_tex, &_points_rec);
}

void TextManager::fill_texture_and_rect(const std::string &text, int x, int y,
                                        SDL_Texture **texture, SDL_Rect *rect)
{
    SDL_Color color = {255, 255, 255, 0};
    SDL_Surface *surf;

    surf = TTF_RenderText_Solid(_font, text.c_str(), color);
    *texture = SDL_CreateTextureFromSurface(_renderer, surf);

    rect->x = x;
    rect->y = y;
    rect->w = surf->w;
    rect->h = surf->h;
}

void TextManager::new_points(int points)
{
    fill_texture_and_rect(std::to_string(points), _result_rec.x + _result_rec.w + 10,
                         _result_rec.y, &_points_tex, &_points_rec);
}

void TextManager::render()
{
    SDL_RenderCopy(_renderer, _next_tex, NULL, &_next_rec);
    SDL_RenderCopy(_renderer, _result_tex, NULL, &_result_rec);
    SDL_RenderCopy(_renderer, _points_tex, NULL, &_points_rec);
}

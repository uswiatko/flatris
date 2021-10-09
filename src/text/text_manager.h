#ifndef _TEXT_MANAGER_H_
#define _TEXT_MANAGER_H_

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

class TextManager {
    public:
        TextManager(SDL_Renderer *renderer);

        void render();

        void new_points(int points);

    private:
        void fill_texture_and_rect(const std::string &text, int x, int y,
                                   SDL_Texture **texture, SDL_Rect *rect);
        SDL_Renderer *_renderer;

        SDL_Rect _next_rec;
        SDL_Texture *_next_tex;

        SDL_Rect _result_rec;
        SDL_Texture *_result_tex;

        SDL_Rect _points_rec;
        SDL_Texture *_points_tex;

        TTF_Font *_font;
};

#endif

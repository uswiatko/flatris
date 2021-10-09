#include "SDL.h"

#include <algorithm>
#include <iostream>
#include <thread>

#include "text/text_manager.h"
#include "tetris_game.h"

static const int SCREEN_H = 800;
static const int SCREEN_W = 600;
static const int BLOCK_SIZE = 40;
static const char *SCREEN_NAME = "flatris v0";

const std::chrono::milliseconds MS_PER_FRAME = std::chrono::milliseconds(25);

static void _render_screen(SDL_Renderer *renderer, TetrisGame &game)
{
    SDL_RenderClear(renderer);

    game.render();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderPresent(renderer);
}

static bool _process_events(TetrisGame &game)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return true;
        case SDL_KEYDOWN:
            game.key_pressed(event.key.keysym.sym);
            break;
        }
    }

    return false;

}

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *_window = SDL_CreateWindow(
            SCREEN_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_W, SCREEN_H, 0);

    SDL_Renderer *_renderer = SDL_CreateRenderer(_window, -1,
            SDL_RENDERER_SOFTWARE);

    TetrisGame game = TetrisGame(SCREEN_W, SCREEN_H, BLOCK_SIZE, _renderer);

    while (1) {
        if (_process_events(game))
            break;

        auto start = std::chrono::system_clock::now();

        game.loop();
        
        auto end = std::chrono::system_clock::now();
        auto elapsed = end - start;

        std::this_thread::sleep_for(MS_PER_FRAME - elapsed); 

        _render_screen(_renderer, game);
    }
}

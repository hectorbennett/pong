#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "game.h"
#include "paddle.h"

bool Game::init () {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return false;
    }

    game_window = SDL_CreateWindow(
        "PONG",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (game_window == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
        return false;
    }

    game_renderer = SDL_CreateRenderer(
        game_window, -1, SDL_RENDERER_ACCELERATED
    );

    if (game_renderer == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(game_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialise PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}


void Game::close () {
    // Destroy window	
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(game_window);
	game_window = NULL;
	game_renderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::run () {
    printf("main\n");
    if(!init()) {
        printf("Failed to initialize\n");

        close();
        return;
    }

    bool quit = false;

    // Event handler
    SDL_Event e;

    Paddle paddle;

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            paddle.handleEvent(e);
        }

        paddle.move();

        //Clear screen
        SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
        SDL_RenderClear(game_renderer);

        paddle.render(game_renderer);

        //Update screen
        SDL_RenderPresent(game_renderer);
    }

    close();
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "game.h"
#include "timer.h"
#include "paddle.h"
#include "ball.h"

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

    Timer fps_timer;
    Timer cap_timer;
    Timer delta;
    int frame_count = 0;
    fps_timer.start();
    delta.start();

    Paddle* left_paddle = new Paddle(100);
    Paddle* right_paddle = new Paddle(SCREEN_WIDTH -100);
    Ball* ball = new Ball();

    while (!quit) {

        cap_timer.start();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            left_paddle -> handleEvent(e);
            right_paddle -> handleEvent(e);
        }

        printf("frame_count: %d\n", frame_count);

        int ticks = fps_timer.getTicks();
        int delta_ticks = delta.getTicks();

        // Calculate and correct fps
        float avg_fps = frame_count / (ticks / 1000.f);

        printf("FPS: %f\n", avg_fps);

        left_paddle -> move(delta_ticks);
        right_paddle -> move(delta_ticks);
        ball -> move(delta_ticks);

        delta.start();

        //Clear screen
        SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
        SDL_RenderClear(game_renderer);

        left_paddle -> render(game_renderer);
        right_paddle -> render(game_renderer);
        ball -> render(game_renderer);

        //Update screen
        SDL_RenderPresent(game_renderer);
        ++frame_count;

        int frame_ticks = cap_timer.getTicks();
        if (frame_ticks < SCREEN_TICK_PER_FRAME) {
            // wait
            SDL_Delay(SCREEN_TICK_PER_FRAME - frame_ticks);
        }
    }

    delete left_paddle;
    delete right_paddle;
    delete ball;
    close();
}

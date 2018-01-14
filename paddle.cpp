#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "paddle.h"

Paddle::Paddle (int x_coordinate) {
    //Initialize the offsets
    mPosX = x_coordinate;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Paddle::handleEvent (SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: mVelY -= VELOCITY; break;
            case SDLK_DOWN: mVelY += VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: mVelY += VELOCITY; break;
            case SDLK_DOWN: mVelY -= VELOCITY; break;
        }
    }

    printf ("X: %d, Y: %d\n", mVelX, mVelY);
}

void Paddle::move () {

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if ((mPosY < 0) || (mPosY + WIDTH > Game::SCREEN_HEIGHT)) {
        //Move back
        mPosY -= mVelY;
    }
}

void Paddle::render (SDL_Renderer* renderer) {
    //Render red filled quad
    SDL_Rect rect;

    rect.x = mPosX - (WIDTH / 2);
    rect.y = mPosY - (HEIGHT / 2);
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);		
    SDL_RenderFillRect(renderer, &rect);
}

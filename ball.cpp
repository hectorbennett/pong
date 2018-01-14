#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "ball.h"

Ball::Ball () {
    mPosX = Game::SCREEN_WIDTH / 2;
    mPosY = Game::SCREEN_HEIGHT / 2;

    mVelX = 1;
    mVelY = 1;
}

void Ball::move () {
    mPosY += mVelY;
    mPosX += mVelX;

    if ((mPosY < 0) || (mPosY + HEIGHT > Game::SCREEN_HEIGHT)) {
        mVelY = -mVelY;
    }

    if ((mPosX < 0) || (mPosX + WIDTH > Game::SCREEN_WIDTH)) {
        mVelX = -mVelX;
    }
}

void Ball::render (SDL_Renderer* renderer) {
    SDL_Rect rect;

    rect.x = mPosX - (WIDTH / 2);
    rect.y = mPosY - (HEIGHT / 2);
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);		
    SDL_RenderFillRect(renderer, &rect);
}

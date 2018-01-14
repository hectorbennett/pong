#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "game.h"
#include "paddle.h"

Paddle::Paddle () {
    //Initialize the offsets
    mPosX = 0;
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
            case SDLK_LEFT: mVelX -= VELOCITY; break;
            case SDLK_RIGHT: mVelX += VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: mVelY += VELOCITY; break;
            case SDLK_DOWN: mVelY -= VELOCITY; break;
            case SDLK_LEFT: mVelX += VELOCITY; break;
            case SDLK_RIGHT: mVelX -= VELOCITY; break;
        }
    }

    printf ("X: %d, Y: %d\n", mVelX, mVelY);
}

void Paddle::move () {
    //Move the dot left or right
    mPosX += mVelX;
    
    //If the dot went too far to the left or right
    if ((mPosX < 0) || (mPosX + WIDTH > Game::SCREEN_WIDTH)) {
        //Move back
        mPosX -= mVelX;
    }

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

    rect.x = mPosX;
    rect.y = mPosY;
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);		
    SDL_RenderFillRect(renderer, &rect);
}

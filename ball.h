// This is start of the header guard.  ADD_H can be any unique name. 
// By convention, we use the name of the header file.
#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "game.h"
 
// This is the content of the .h file, which is where the declarations go
class Ball {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 10;
    static const int VELOCITY = 1;

    // Init variables
    Ball ();

    void move ();
    void render (SDL_Renderer* renderer);

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};
 
// This is the end of the header guard
#endif

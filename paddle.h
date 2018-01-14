// This is start of the header guard.  ADD_H can be any unique name. 
// By convention, we use the name of the header file.
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include "game.h"
 
// This is the content of the .h file, which is where the declarations go
class Paddle {
public:
    static const int WIDTH = 20;
    static const int HEIGHT = 60;
    static const int VELOCITY = 500;

    // Init variables
    Paddle (int x_coord);

    void handleEvent (SDL_Event& e);
    void move (Uint32 delta_ticks);
    void render (SDL_Renderer* renderer);

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};
 
// This is the end of the header guard
#endif

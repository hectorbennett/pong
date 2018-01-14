// This is start of the header guard.  ADD_H can be any unique name. 
// By convention, we use the name of the header file.
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
// This is the content of the .h file, which is where the declarations go
class Game {
public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    const int SCREEN_FPS = 60;
    const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

    SDL_Window* game_window = NULL;
    SDL_Renderer* game_renderer = NULL;

    bool init ();
    void close ();
    void run ();
};
 
// This is the end of the header guard
#endif

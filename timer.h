// This is start of the header guard.  ADD_H can be any unique name. 
// By convention, we use the name of the header file.
#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include "game.h"

class Timer {
public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

// This is the end of the header guard
#endif

#ifndef SDL_SETUP_H
#define SDL_SETUP_H

#include "stdafx.h"

class SDL_Setup
{
protected:
    SDL_Window* window;             // Window to be rendered to
    SDL_Renderer* renderer;         // Renderer to be updated
    SDL_Event* main_event;           // Event to be updated

public:
    SDL_Setup(bool* quit, const int& _SCREEN_WIDTH, const int& _SCREEN_HEIGHT,
              const std::string& _PROGRAM_TITLE);
    ~SDL_Setup();

    SDL_Renderer* GetRenderer() { return renderer; };
    SDL_Event* GetEvent() { return main_event; };

    void Begin();                   // To reset renderer every game loop
    void End();                     // To render after every update
};

#endif // SDL_SETUP_H

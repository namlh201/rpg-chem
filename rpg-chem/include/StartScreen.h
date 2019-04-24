#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Sound.h"

class StartScreen
{
protected:
    Sprite* startScreen;

    Sprite* logo;

    Sound* cursor_sound;

    TTF_Font* font;

    SDL_Color text_colour;

    SDL_Rect cursorRect;
    SDL_Rect cropCursor;
    SDL_Texture* cursor;

    enum CHOICE {NEW_GAME = 1, CONTINUE, QUIT};

    SDL_Rect newGameRect;
    SDL_Rect cropNewGameText;
    SDL_Surface* newGameSurf;
    SDL_Texture* newGameText;

    SDL_Rect continueRect;
    SDL_Rect cropContinueText;
    SDL_Surface* continueSurf;
    SDL_Texture* continueText;

    SDL_Rect quitRect;
    SDL_Rect cropQuitText;
    SDL_Surface* quitSurf;
    SDL_Texture* quitText;

    SDL_Setup* sdl_setup;

    unsigned state;

    void Update();

public:
    StartScreen(SDL_Setup* _sdl_setup);
    ~StartScreen();

    void ScreenDraw();

    unsigned GetState() { return state; };
};

#endif // START_SCREEN_H

#ifndef MAIN_H
#define MAIN_H

#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "mainCharacter.h"
#include "StartScreen.h"
#include "Map.h"
#include "PeriodicTable.h"
#include "PopUp.h"
#include "Music.h"
#include "Sound.h"

class Main
{
protected:
    MainCharacter* main_char;

    bool quit;

    SDL_Setup* sdl_setup;       // To update sdl_setup

    Map* anotherMap;

    StartScreen* start_screen;   // Start screen
    Sound* ss_choose_sound;

    PeriodicTable* periodic_table;
    Sound* enter_periodic_table_sound;
    Sound* escape_periodic_table_sound;

    PopUp* pop_up;

    Music* music;

    void SetDefault();

public:
    Main(const int& _MAIN_PROGRAM_WIDTH, const int& _MAIN_PROGRAM_HEIGHT);                     // ctor
    ~Main();                    // dtor

    void GameLoop();            // Setup game loop
};

#endif // MAIN_H

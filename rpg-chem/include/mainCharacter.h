#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"

class MainCharacter
{
protected:
    Sprite* character;               // Character
    Sprite* shadow;

    int pos_x;
    int pos_y;

    int time_check;

    SDL_Setup* sdl_setup;

    int step;                   // Step after each move
    bool move_up;
    bool move_left;
    bool move_down;
    bool move_right;
    bool sprint;                // If sprint

    void Update();              // Update character after every keyboard event

    void SavePosition();
    void LoadPosition();

public:
    MainCharacter(SDL_Setup* _sdl_setup);
    ~MainCharacter();

    void SetDefault();

    bool start_moving;

    Sprite* GetChar() { return character; };

    int GetStep() { return step; };

    void CharacterDraw();
    void CharacterDraw(const int& _x, const int& _y);       // Draw character after every update
};

#endif // MAIN_CHARACTER_H

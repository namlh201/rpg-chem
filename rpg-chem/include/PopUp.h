#ifndef POP_UP_H
#define POP_UP_H

#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "PeriodicTable.h"
#include "Sound.h"

class PopUp
{
protected:
    SDL_Setup* sdl_setup;

    PeriodicTable* periodic_table;

    TTF_Font* text_font_36;                                    // Font
    TTF_Font* text_font_20;
    SDL_Color text_colour;                                  // Blacc

/*
 * Element found system
 */
    Sprite* pop_up;                                         // Pop-up whenever an element has been found

    Sprite* element_found_image;

    SDL_Rect pop_up_text_rect;                              //
    SDL_Surface* pop_up_text_surface;                       // Found element text
    SDL_Texture* pop_up_text_texture;                       //

    SDL_Rect prompt_text_rect;
    SDL_Surface* prompt_text_surface;
    SDL_Texture* prompt_text_texture;

    void FoundElement(const int& _Z);                              // To render which element has been found

public:
    PopUp(SDL_Setup* _sdl_setup, PeriodicTable* _periodic_table);
    ~PopUp();

    void RenderPopUp(const int& _Z);                               // To render found element congrats text
};

#endif // POP_UP_H

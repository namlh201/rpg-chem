#include "../include/PopUp.h"

PopUp::PopUp(SDL_Setup* _sdl_setup, PeriodicTable* _periodic_table)
{
    sdl_setup = _sdl_setup;

    periodic_table = _periodic_table;

    std::string FONT_FILE_PATH = "Fonts/pkmnfl.ttf";
    text_font_36 = NULL;
    text_font_36 = TTF_OpenFont(FONT_FILE_PATH.c_str(), 36);

    text_font_20 = NULL;
    text_font_20 = TTF_OpenFont(FONT_FILE_PATH.c_str(), 20);

    text_colour = {0, 0, 0};

/*
 * Element found system
 */
    pop_up = new Sprite(sdl_setup->GetRenderer(), "Sprites/Game/PopUp/pop_up.png", 256, 144, 512, 288);

    pop_up_text_surface = NULL;
    pop_up_text_texture = NULL;

    element_found_image = NULL;

    std::string PROMPT = "Press Enter to continue";
    prompt_text_surface = TTF_RenderText_Blended(text_font_20, PROMPT.c_str(), text_colour);
    prompt_text_rect = {(1024 - prompt_text_surface->w) / 2, 385, prompt_text_surface->w, prompt_text_surface->h};
    prompt_text_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), prompt_text_surface);
}

PopUp::~PopUp()
{
    delete sdl_setup;
    delete periodic_table;

    delete pop_up;

    TTF_CloseFont(text_font_36);
    TTF_CloseFont(text_font_20);

    SDL_FreeSurface(pop_up_text_surface);
    SDL_DestroyTexture(pop_up_text_texture);

    SDL_FreeSurface(prompt_text_surface);
    SDL_DestroyTexture(prompt_text_texture);
}

void PopUp::FoundElement(const int& _Z)
{
    std::string TEXT;
    std::string name = periodic_table->element.at(_Z);

    TEXT = "Congratulations!\n\n\nYou've found " + name + ".";

    pop_up_text_surface = TTF_RenderText_Blended_Wrapped(text_font_36, TEXT.c_str(), text_colour, 424);
    pop_up_text_rect = {(1024 - pop_up_text_surface->w) / 2, 285, pop_up_text_surface->w, pop_up_text_surface->h};
    pop_up_text_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), pop_up_text_surface);
}

void PopUp::RenderPopUp(const int& _Z)
{
    pop_up->SpriteDraw();

    FoundElement(_Z);
    SDL_RenderCopy(sdl_setup->GetRenderer(), pop_up_text_texture, NULL, &pop_up_text_rect);
    SDL_RenderCopy(sdl_setup->GetRenderer(), prompt_text_texture, NULL, &prompt_text_rect);

    SDL_FreeSurface(pop_up_text_surface); pop_up_text_surface = NULL;
    SDL_DestroyTexture(pop_up_text_texture); pop_up_text_texture = NULL;

    element_found_image = periodic_table->GetElementImage(_Z);
    element_found_image->set_w(100); element_found_image->set_h(100);
    element_found_image->DrawSeperate((1024 - element_found_image->get_w()) / 2, 175);
}

#ifndef MAP_H
#define MAP_H

#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "mainCharacter.h"
#include "PeriodicTable.h"
#include "PopUp.h"

class Map
{
protected:
    SDL_Setup* sdl_setup;

    MainCharacter* main_char;

    PeriodicTable* periodicTable;

    PopUp* pop_up;

    int SCREEN_WIDTH;           // == 1024
    int SCREEN_HEIGHT;          // == 576

    int TILE_WIDTH;             // == 32
    int TILE_HEIGHT;            // == 32

    int ROW;                    // == 18
    int COLUMN;                 // == 32

    int current_map_index;

    int AMOUNT_OF_MAPS;         // == 12
    Sprite* map_background;                              // To render background
    std::string MAP_BACKGROUND_FILE_PATH;
    std::vector<std::string> MAP_LAYOUT_FILE_PATH;
    std::vector< std::vector< std::vector<int> > > current_map;  // Layout of each map
    std::vector< std::vector< std::vector<int> > > default_map;  // Default layout

    Sprite* wall;

    enum BallColour {BLUE, GREEN, PURPLE, RED, YELLOW};
    std::vector<Sprite*> element_ball;
    Sprite* element_ball_shadow;
    int element_found;                                          // Atomic number of found element
    bool found_element;                                         // To check if an element has been found
    bool got_element;                                           // To check if said element has been gathered

    Sound* found_element_sound;
    Sound* got_element_sound;
    bool found_element_sound_play;

    Sprite* portal_to_previous_stage;
    Sprite* portal_to_next_stage;

    TTF_Font* text_font;
    SDL_Color text_colour;

    Sprite* e_button;
    SDL_Rect open_pt_rect;
    SDL_Surface* open_pt_surface;
    SDL_Texture* open_pt_texture;

    void Load();
    void Save();

    void UpdateMap(Sprite* _portal);                            // To travel between map

    void Collision();

    void PortalCollision(MainCharacter* _main_char);
    void ElementBallCollision(MainCharacter* _main_char, Sprite* _element_ball);
    void WallCollision(MainCharacter* _main_char);

    void HandleCollision(const SDL_Rect& _char_rect, const SDL_Rect& _object_rect);

public:
    Map(SDL_Setup* _sdl_setup, const int& _SCREEN_WIDTH, const int& _SCREEN_HEIGHT,
        MainCharacter* _main_char, PeriodicTable* _periodicTable, PopUp* _pop_up);
    ~Map();

    void SetDefault();

    void RenderMap();                                           // To render maps
};

#endif // MAP_H

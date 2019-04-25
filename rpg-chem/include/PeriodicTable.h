#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Sound.h"

typedef std::pair<int, bool> ib;

class PeriodicTable
{
protected:
    SDL_Setup* sdl_setup;

    TTF_Font* text_font;                                            // Font
    SDL_Color text_colour;                                          // White

    /*
     * Periodic Table
     */
    int ROW;                    // == 9
    int COLUMN;                 // == 18
    int NUMBER_OF_ELEMENT;      // == 118

    int ELEMENT_TILE_WIDTH;     // == 56
    int ELEMENT_TILE_HEIGHT;    // == 56

    std::vector< std::vector< ib > > foundElement;                  // To check if an element has been found
    std::vector<Sprite*> element_image;                             // Element image
    std::vector<bool> currentCursor;                                // To check which element cursor is pointing at

    void SaveTable();
    void LoadTable();                                               // To load periodic table

    Sprite* periodic_table_bg;                                      // Periodic Table BG
    Sprite* cursor;                                                 // Cursor

    int currentCursorIndex;                                         // To get current element cursor is pointing at

    bool isChosen;                                                  // To check is an element is chosen

    void UpdateTable();                                             // Update cursor

    Sprite* escape;
    SDL_Rect return_to_game_rect;
    SDL_Surface* return_to_game_surface;
    SDL_Texture* return_to_game_texture;

    Sprite* enter;
    SDL_Rect read_info_rect;
    SDL_Surface* read_info_surface;
    SDL_Texture* read_info_texture;

    Sound* cursor_sound;
    Sound* choose_sound;

    /*
     * Element info
     */
    int ELEMENT_INFO_WIDTH;
    int ELEMENT_INFO_HEIGHT;

    std::vector<bool> info;                                         // To render chosen element info
    std::vector<Sprite*> element_image_info;                        // Element image info

    Sprite* element_info_bg;                                        // Element info BG

    SDL_Rect info_text_rect;                                        //
    SDL_Surface* info_text_surface;                                 // Element info text
    SDL_Texture* info_text_texture;                                 //

    Sprite* backspace;
    SDL_Rect return_to_pt_rect;
    SDL_Surface* return_to_pt_surface;
    SDL_Texture* return_to_pt_texture;

    Sprite* a_button;
    SDL_Rect prev_element_rect;
    SDL_Surface* prev_element_surface;
    SDL_Texture* prev_element_texture;

    Sprite* d_button;
    SDL_Rect next_element_rect;
    SDL_Surface* next_element_surface;
    SDL_Texture* next_element_texture;

    std::vector<std::string> element_info;

    std::string GetInfo(const int& _Z) { return element_info.at(_Z); };
    void RenderInfo(const int& _Z);

    bool is_in_info;

    /*
     * General
     */
    void LoadElementName();                                         // To get all element names

public:
    PeriodicTable(SDL_Setup* _sdl_setup);
    ~PeriodicTable();

    void SetDefault();

    void FoundElement(const int& _Z);

    std::map<int, std::string> element;                             // Each element's atomic number and name

    void RenderPeriodicTable();                                     // Draw periodic table

    bool IsInInfo() { return is_in_info; };

    Sprite* GetElementImage(const int& _Z) { return element_image_info.at(_Z); };
};

#endif // PERIODIC_TABLE_H

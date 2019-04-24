#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"

class Sprite
{
protected:
    SDL_Texture* image;             // Image to render
    SDL_Surface* surface;           // Surface to load image
    SDL_Rect image_rect;            // A rectangle to render image
    SDL_Rect crop;                  // A rectangle to only render image at its exact size

    SDL_Renderer* renderer;         // Renderer

    int amount_frame_x;             // Number of columns
    int amount_frame_y;             // Number of rows

public:
    Sprite(SDL_Renderer* _renderer, const std::string& _IMAGE_FILE_PATH,
           const int& _x, const int& _y, const int& _w, const int& _h);   //ctor
    ~Sprite();                      // dtor

    void SpriteDraw();              // To draw sprite to renderer
    void DrawSeperate(const int& _x, const int& _y);

    void set_x(int _x) { image_rect.x = _x; };             // To set position
    void set_y(int _y) { image_rect.y = _y; };
    void set_w(int _w) { image_rect.w = _w; };
    void set_h(int _h) { image_rect.h = _h; };
    void set_position(int _x, int _y) { image_rect.x = _x; image_rect.y = _y; };

    int get_x() { return image_rect.x; };                    // To return position
    int get_y() { return image_rect.y; };
    int get_w() { return image_rect.w; };
    int get_h() { return image_rect.h; };

    SDL_Rect GetImageRect() { return image_rect; };

    int current_frame;               // Current column in sheet
    int animation_delay;

    void SetupAnimation(const int& _amount_frame_x, const int& _amount_frame_y);      // To determine number of animation states = x . y

    void Animation(const int& begin_frame, const int& end_frame,
                   const int& row, const float& speed); // To play animation based on keyboard state
};

#endif // SPRITE_H

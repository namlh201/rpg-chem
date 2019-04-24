#include "../include/Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, const std::string& _IMAGE_FILE_PATH,
           const int& _x, const int& _y, const int& _w, const int& _h)
{
    renderer = _renderer;

    image = NULL;
    surface = NULL;
    surface = IMG_Load(_IMAGE_FILE_PATH.c_str());
    image = SDL_CreateTextureFromSurface(renderer, surface);
    if (image == NULL) std::cout << "Failed to load image at " << _IMAGE_FILE_PATH << '.' << std::endl;

    image_rect = {_x, _y, _w,_h};

    crop = {0, 0, surface->w, surface->h};

    current_frame = 0;               // Current column in sheet
    animation_delay = 0;

    amount_frame_x = 0;             // Number of columns
    amount_frame_y = 0;             // Number of rows
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(image);
    SDL_FreeSurface(surface);

    SDL_DestroyRenderer(renderer);
}

void Sprite::SpriteDraw()           // To draw sprite to renderer
{
    SDL_RenderCopy(renderer, image, &crop, &image_rect);
}

void Sprite::DrawSeperate(const int& _x, const int& _y)
{
    image_rect.x = _x;
    image_rect.y = _y;

    SDL_RenderCopy(renderer, image, &crop, &image_rect);
}

void Sprite::SetupAnimation(const int& _amount_frame_x, const int& _amount_frame_y)   // To determine number of animation states = x . y
{
    amount_frame_x = _amount_frame_x;
    amount_frame_y = _amount_frame_y;
}

void Sprite::Animation(const int& begin_frame /* == 0 */, const int& end_frame,
                       const int& row, const float& speed)    // To play animation based on keyboard state
{   // end_frame - begin_frame + 1 == number of columns in sheet
    if (animation_delay + speed < SDL_GetTicks()) {
        if (current_frame >= end_frame) current_frame = begin_frame;        // Return to initial frame
        else current_frame++;                                            // Update frame

        crop.x = current_frame * (surface->w / amount_frame_x);          // Render frame
        crop.y = row * (surface->h / amount_frame_y);                    // to screen
        crop.w = surface->w / amount_frame_x;
        crop.h = surface->h / amount_frame_y;

        animation_delay = SDL_GetTicks();
    }
}

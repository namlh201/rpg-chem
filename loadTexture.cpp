#include "loadTexture.h"

SDL_Texture* loadTexture(std::string path) {
    // Final texture
    SDL_Texture* newTexture = NULL;

    // Load image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        printf("Failed to load image from %s.\n Error: %s\n", path.c_str(), IMG_GetError());

    else {
        // Create texture
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL)
            printf("Failed to create texture from %s.\nError: %s\n", path.c_str(), SDL_GetError());

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

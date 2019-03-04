#include "loadMedia.h"

bool loadMedia() {
    const std::string PATH = "C:/Users/namlh201/OneDrive/Desktop/INT2202/07_texture_loading_and_rendering/07_texture_loading_and_rendering/texture.png";

    // Loading media success flag
    bool success = true;

    // Load PNG texture
    gTexture = loadTexture(PATH);
    if (gTexture == NULL) {
        printf("Failed to load texture image.\nError: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

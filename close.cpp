#include "close.h"

void close() {
    // Free loaded image
    SDL_DestroyTexture(gTexture);
    //gTexture = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    //gRenderer = NULL;
    //gWindow = NULL;

    // Quit SDL
    IMG_Quit();
    SDL_Quit();
}

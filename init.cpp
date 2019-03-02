#include "init.h"

bool init() {
    // Initialisation flag
    bool success = true;

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialise.\nError: %s\n", SDL_GetError());
        success = false;
    }

    else {
        // Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

        // Create window
        gWindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            printf("Failed to create window.\nError: %s\n", SDL_GetError());
            success = false;
        }

        else {
            // Create renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL) {
                printf("Failed to create renderer.\nError: %s\n", SDL_GetError());
                success = false;
            }

            else {
                // Initialise renderer colour
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);

                // Initialise PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("Failed to initialise SDL_image.\nError: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

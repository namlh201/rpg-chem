#include "variable.h"
#include <SDL.h>
#include <SDL_image.h>

// Window to open
SDL_Window* gWindow = NULL;

// Renderer
SDL_Renderer* gRenderer = NULL;

// Texture
SDL_Texture* gTexture = NULL;

// Screen size
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Program name
const char* PROGRAM_NAME = "test";

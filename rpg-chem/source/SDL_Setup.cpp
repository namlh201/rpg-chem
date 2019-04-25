#include "../include/SDL_Setup.h"

SDL_Setup::SDL_Setup(bool* quit, const int& _SCREEN_WIDTH, const int& _SCREEN_HEIGHT,
                     const std::string& _PROGRAM_TITLE)
{                                           // ctor
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    window = NULL;
    window = SDL_CreateWindow(_PROGRAM_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              _SCREEN_WIDTH, _SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        *quit = true;

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) std::cout << "Failed to create renderer." << std::endl;

    main_event = new SDL_Event();
}

SDL_Setup::~SDL_Setup()                     // dtor
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete main_event;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDL_Setup::Begin()                     // To reset renderer every game loop
{
    SDL_PollEvent(main_event);
    SDL_RenderClear(renderer);
}

void SDL_Setup::End()                       // To render after every update
{
    SDL_RenderPresent(renderer);
}

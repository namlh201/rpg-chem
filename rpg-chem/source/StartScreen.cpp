#include "../include/StartScreen.h"

StartScreen::StartScreen(SDL_Setup* _sdl_setup)
{
    sdl_setup = _sdl_setup;

    logo = new Sprite(sdl_setup->GetRenderer(), "Sprites/Start Screen/Logo.png", 272, -15, 480, 270);

    cursor_sound = new Sound("Audio/SE/SSCursor.wav"); cursor_sound->SetVolume(32);

    std::string FONT_FILE_PATH = "Fonts/Dosis-ExtraBold.ttf";
    font = NULL;
    font = TTF_OpenFont(FONT_FILE_PATH.c_str(), 72);

    startScreen = new Sprite(sdl_setup->GetRenderer(), "Sprites/Start Screen/Wall.jpg", 0, 0, 1024, 576);

    text_colour = {10, 108, 219};

    cursorRect = {312, 250, 400, 100};
    cursor = NULL;
    cursor = IMG_LoadTexture(sdl_setup->GetRenderer(), "Sprites/Start Screen/Cursor.png");
    cropCursor.x = 0;
    cropCursor.y = 0;
    SDL_QueryTexture(cursor, NULL, NULL, &cropCursor.w, &cropCursor.h);

    newGameSurf = NULL;
    newGameSurf = TTF_RenderText_Blended(font, "New Game", text_colour);
    newGameRect = {(1024 - newGameSurf->w) / 2, 250, newGameSurf->w, newGameSurf->h};
    newGameText = NULL;
    newGameText = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), newGameSurf);
    cropNewGameText.x = 0;
    cropNewGameText.y = 0;
    SDL_QueryTexture(newGameText, NULL, NULL, &cropNewGameText.w, &cropNewGameText.h);

    continueSurf = NULL;
    continueSurf = TTF_RenderText_Blended(font, "Continue", text_colour);
    continueRect = {(1024 - continueSurf->w) / 2, 350, continueSurf->w, continueSurf->h};
    continueText = NULL;
    continueText = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), continueSurf);
    cropContinueText.x = 0;
    cropContinueText.y = 0;
    SDL_QueryTexture(continueText, NULL, NULL, &cropContinueText.w, &cropContinueText.h);

    quitSurf = NULL;
    quitSurf = TTF_RenderText_Blended(font, "Quit", text_colour);
    quitRect = {(1024 - quitSurf->w) / 2, 450, quitSurf->w, quitSurf->h};
    quitText = NULL;
    quitText = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), quitSurf);
    cropQuitText.x = 0;
    cropQuitText.y = 0;
    SDL_QueryTexture(quitText, NULL, NULL, &cropQuitText.w, &cropQuitText.h);
}

StartScreen::~StartScreen()
{
    delete sdl_setup;

    delete logo;

    delete cursor_sound;

    delete startScreen;

    TTF_CloseFont(font);
    delete font;

    SDL_FreeSurface(newGameSurf);
    SDL_FreeSurface(continueSurf);
    SDL_FreeSurface(quitSurf);

    SDL_DestroyTexture(cursor);
    SDL_DestroyTexture(newGameText);
    SDL_DestroyTexture(continueText);
    SDL_DestroyTexture(quitText);
}

void StartScreen::Update()
{
    bool cursor_sound_play = false;

    switch (sdl_setup->GetEvent()->type) {
    case SDL_KEYDOWN:
        switch (sdl_setup->GetEvent()->key.keysym.sym) {
        case SDLK_w:
            cursorRect.y -= 100;
            cursor_sound_play = true;
            break;

        case SDLK_s:
            cursorRect.y += 100;
            cursor_sound_play = true;
            break;

        default: break;
        }

    default: break;
    }

    if (cursorRect.y < 200) cursorRect.y = 250;
    if (cursorRect.y > 500) cursorRect.y = 450;

    if (cursorRect.y == newGameRect.y) state = NEW_GAME;
    else if (cursorRect.y == continueRect.y) state = CONTINUE;
    else if (cursorRect.y == quitRect.y) state = QUIT;

    if (cursor_sound_play) {
        cursor_sound->Play();
        cursor_sound_play = false;
    }
}

void StartScreen::ScreenDraw()
{
    startScreen->SpriteDraw();

    logo->SpriteDraw();

    SDL_RenderCopy(sdl_setup->GetRenderer(), cursor, &cropCursor, &cursorRect);
    SDL_RenderCopy(sdl_setup->GetRenderer(), newGameText, &cropNewGameText, &newGameRect);
    SDL_RenderCopy(sdl_setup->GetRenderer(), continueText, &cropContinueText, &continueRect);
    SDL_RenderCopy(sdl_setup->GetRenderer(), quitText, &cropQuitText, &quitRect);

    Update();
}

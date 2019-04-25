#include "../include/PeriodicTable.h"

PeriodicTable::PeriodicTable(SDL_Setup* _sdl_setup)
{
    sdl_setup = _sdl_setup;

    std::string FONT_FILE_PATH = "Fonts/pkmnfl.ttf";
    text_font = NULL;
    text_font = TTF_OpenFont(FONT_FILE_PATH.c_str(), 24);

    //TTF_SetFontStyle(text_font, TTF_STYLE_BOLD);

    text_colour = {255, 255, 255};

    /*
     * Periodic Table
     */
    ROW = 9;
    COLUMN = 18;
    NUMBER_OF_ELEMENT = 118;

    ELEMENT_TILE_WIDTH = 56;
    ELEMENT_TILE_HEIGHT = 56;

    foundElement = std::vector< std::vector< ib > > (ROW, std::vector< ib >(COLUMN, std::make_pair(-1, false)));
    currentCursor = std::vector<bool> (118);

    LoadTable();

    std::vector<std::string> ELEMENT_IMAGE_FILE_PATH;
    for (int i = 0; i <= NUMBER_OF_ELEMENT; ++i) {
        ELEMENT_IMAGE_FILE_PATH.push_back("Sprites/Periodic Table/Elements/128x128/Element[" + std::to_string(i) + "].png");

        element_image.push_back( new Sprite(sdl_setup->GetRenderer(), ELEMENT_IMAGE_FILE_PATH.at(i),
                                            0, 0, ELEMENT_TILE_WIDTH, ELEMENT_TILE_HEIGHT) );
    }

    periodic_table_bg = new Sprite(sdl_setup->GetRenderer(), "Sprites/Periodic Table/Elements/PeriodicTable_BG.jpg", 0, 0, 1024, 576);

    std::string CURSOR_FILE_PATH = "Sprites/Periodic Table/cursor_1.png";
    cursor = new Sprite(sdl_setup->GetRenderer(), CURSOR_FILE_PATH, 0, 50, 70, 69);

    currentCursorIndex = 0;

    currentCursor.at(currentCursorIndex) = true;

    isChosen = false;

    escape = new Sprite(sdl_setup->GetRenderer(), "Sprites/Icons/esc_button.png",
                        8, 8, 40, 40);
    return_to_game_surface = TTF_RenderText_Blended(text_font, "Return to Game", text_colour);
    return_to_game_rect = {60, (escape->get_h() - return_to_game_surface->h) / 2 + escape->get_y(),
                           return_to_game_surface->w, return_to_game_surface->h};
    return_to_game_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), return_to_game_surface);

    enter = new Sprite(sdl_setup->GetRenderer(), "Sprites/Icons/enter_button.png",
                       128, 64, 40, 40);
    read_info_surface = TTF_RenderText_Blended(text_font, "Read Info", text_colour);
    read_info_rect = {200, (enter->get_h() - read_info_surface->h) / 2 + enter->get_y(),
                      read_info_surface->w, read_info_surface->h};
    read_info_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), read_info_surface);

    cursor_sound = new Sound("Audio/SE/PTCursor.wav"); cursor_sound->SetVolume(24);
    choose_sound = new Sound("Audio/SE/PTChoose.wav"); choose_sound->SetVolume(16);

    /*
     * Element info
     */
    ELEMENT_INFO_WIDTH = 128;
    ELEMENT_INFO_HEIGHT = 128;

    std::vector<std::string> ELEMENT_INFO_FILE_PATH;
    for (int i = 0; i <= NUMBER_OF_ELEMENT; ++i) {
        ELEMENT_INFO_FILE_PATH.push_back("Data/Elements Info/Info[" + std::to_string(i) + "].chem");

        element_image_info.push_back( new Sprite(sdl_setup->GetRenderer(), ELEMENT_IMAGE_FILE_PATH.at(i),
                                      0, 0, ELEMENT_INFO_WIDTH, ELEMENT_INFO_HEIGHT) );
    }

    element_info = std::vector<std::string> (119);

    for (int i = 0; i <= NUMBER_OF_ELEMENT; ++i) {
        std::ifstream info_input(ELEMENT_INFO_FILE_PATH.at(i));

        std::string line;
        while (getline(info_input, line))
            element_info.at(i) = element_info.at(i) + line + "\n\n";

        info_input.close();
    }

    info = std::vector<bool> (118, false);

    element_info_bg = new Sprite(sdl_setup->GetRenderer(), "Sprites/Periodic Table/Elements/BlackHole_3.jpg", 0, 0, 1024, 576);

    info_text_surface = NULL;
    info_text_texture = NULL;

    is_in_info = false;

    backspace = new Sprite(sdl_setup->GetRenderer(), "Sprites/Icons/backspace_button.png",
                           8, 8, 40, 40);
    return_to_pt_surface = TTF_RenderText_Blended(text_font, "Return to Periodic Table", text_colour);
    return_to_pt_rect = {60, (backspace->get_h() - return_to_pt_surface->h) / 2 + backspace->get_y(),
                         return_to_pt_surface->w, return_to_pt_surface->h};
    return_to_pt_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), return_to_pt_surface);

    a_button = new Sprite(sdl_setup->GetRenderer(), "Sprites/Icons/letter_A.png",
                          75, 76, 40, 40);
    prev_element_surface = TTF_RenderText_Blended(text_font, "Prev Element", text_colour);
    prev_element_rect = {120, (a_button->get_h() - prev_element_surface->h) / 2 + a_button->get_y(),
                         prev_element_surface->w, prev_element_surface->h};
    prev_element_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), prev_element_surface);

    d_button = new Sprite(sdl_setup->GetRenderer(), "Sprites/Icons/letter_D.png",
                          1024 - a_button->get_x() - a_button->get_w(), 76, 40, 40);
    next_element_surface = TTF_RenderText_Blended(text_font, "Next Element", text_colour);
    next_element_rect = {d_button->get_x() - 131, (d_button->get_h() - next_element_surface->h) / 2 + d_button->get_y(),
                         next_element_surface->w, next_element_surface->h};
    next_element_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), next_element_surface);

    /*
     * General
     */
    LoadElementName();
}

PeriodicTable::~PeriodicTable()
{
    delete sdl_setup;
    for (int i = 0; i <= NUMBER_OF_ELEMENT; ++i) {
        delete element_image.at(i);
        delete element_image_info.at(i);
    }

    delete periodic_table_bg;

    delete cursor;

    delete element_info_bg;

    TTF_CloseFont(text_font);

    SDL_FreeSurface(info_text_surface);
    SDL_DestroyTexture(info_text_texture);

    delete cursor_sound;
    delete choose_sound;

    delete escape;
    delete enter;
    delete backspace;
    delete a_button;
    delete d_button;

    SDL_FreeSurface(return_to_game_surface);
    SDL_DestroyTexture(return_to_game_texture);

    SDL_FreeSurface(read_info_surface);
    SDL_DestroyTexture(read_info_texture);

    SDL_FreeSurface(return_to_pt_surface);
    SDL_DestroyTexture(return_to_pt_texture);

    SDL_FreeSurface(next_element_surface);
    SDL_DestroyTexture(next_element_texture);

    SDL_FreeSurface(prev_element_surface);
    SDL_DestroyTexture(prev_element_texture);
}

void PeriodicTable::SetDefault()
{
    foundElement = std::vector< std::vector< ib > > (ROW, std::vector< ib >(COLUMN, std::make_pair(-1, false)));
    currentCursor = std::vector<bool> (118);

    info = std::vector<bool> (118, false);

    SaveTable();
    LoadTable();

    currentCursorIndex = 0;

    currentCursor.at(currentCursorIndex) = true;

    isChosen = false;
}

void PeriodicTable::FoundElement(const int& _Z)
{
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COLUMN; ++j)
            if (foundElement.at(i).at(j).first == _Z) {
                foundElement.at(i).at(j).second = true;
                break;
            }

    SaveTable();
}

void PeriodicTable::SaveTable()
{
    std::string TABLE_STATE_FILE_PATH = "Data/Periodic Table/PeriodicTableState.chem";
    std::ofstream table_state_output(TABLE_STATE_FILE_PATH);
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            table_state_output << (int) foundElement.at(i).at(j).second << ' ';
        }
        table_state_output << std::endl;
    }
    table_state_output.close();
}

void PeriodicTable::LoadTable()
{
    std::string TABLE_LAYOUT_FILE_PATH = "Data/Periodic Table/PeriodicTableLayout.chem";
    std::string TABLE_STATE_FILE_PATH = "Data/Periodic Table/PeriodicTableState.chem";

    int Z;
    int state;

    std::ifstream table_layout_input(TABLE_LAYOUT_FILE_PATH);
    std::ifstream table_state_input(TABLE_STATE_FILE_PATH);

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            Z = -1;
            table_layout_input >> Z;
            table_state_input >> state;

            foundElement.at(i).at(j) = std::make_pair(Z, (bool) state);
            if (Z > 0) currentCursor.at(Z - 1) = false;
        }
    }

    table_layout_input.close();
    table_state_input.close();
}

void PeriodicTable::LoadElementName()
{
    std::string NAME_FILE_PATH = "Data/Periodic Table/ElementName.chem";

    std::ifstream name_input(NAME_FILE_PATH);

    for (int i = 1; i < NUMBER_OF_ELEMENT; ++i) {
        std::string name;

        getline(name_input, name);

        element[i] = name;
    }

    name_input.close();
}

void PeriodicTable::UpdateTable()
{
    bool left = false;
    bool right = false;

    bool cursor_sound_play = false;
    bool choose_sound_play = false;

    switch (sdl_setup->GetEvent()->type) {
    case SDL_KEYDOWN:
        switch (sdl_setup->GetEvent()->key.keysym.sym) {
        case SDLK_a:
            left = true;
            cursor_sound_play = true;
            break;

        case SDLK_d:
            right = true;
            cursor_sound_play = true;
            break;

        case SDLK_RETURN:
            isChosen = true;
            choose_sound_play = true;
            break;

        default: break;
        }
        break;

    case SDL_KEYUP:
        switch (sdl_setup->GetEvent()->key.keysym.sym)
        {
        case SDLK_a:
            left = false;
            cursor_sound_play = false;
            break;

        case SDLK_d:
            right = false;
            cursor_sound_play = false;
            break;

        default: break;
        }
        break;

    default: break;
    }

    if (left) {
        if (currentCursorIndex - 1 >= 0) {
            currentCursor.at(currentCursorIndex) = false;
            currentCursorIndex--;
            currentCursor.at(currentCursorIndex) = true;
        } else {
            currentCursor.at(currentCursorIndex) = false;
            currentCursorIndex = currentCursorIndex + 118 - 1;
            currentCursor.at(currentCursorIndex) = true;
        }
    } else if (right) {
        currentCursor.at(currentCursorIndex) = false;
        currentCursorIndex = (currentCursorIndex + 1) % 118;
        currentCursor.at(currentCursorIndex) = true;
    }

    if (cursor_sound_play) cursor_sound->Play();
    if (choose_sound_play) {
        choose_sound->Play();
        choose_sound_play = false;
    }
}

void PeriodicTable::RenderPeriodicTable()
{
    int atomicNumber;
    bool checkFound;

    UpdateTable();

    if (!isChosen) {
        is_in_info = false;

        periodic_table_bg->SpriteDraw();

        escape->SpriteDraw();
        SDL_RenderCopy(sdl_setup->GetRenderer(), return_to_game_texture, NULL, &return_to_game_rect);

        enter->SpriteDraw();
        SDL_RenderCopy(sdl_setup->GetRenderer(), read_info_texture, NULL, &read_info_rect);

        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COLUMN; ++j) {
                atomicNumber = foundElement.at(i).at(j).first;
                checkFound = foundElement.at(i).at(j).second;

                if (atomicNumber > 0) {
                    if (checkFound) {
                        info.at(atomicNumber - 1) = true;

                        element_image.at(atomicNumber)->DrawSeperate(j * ELEMENT_TILE_WIDTH + 8, (i + 1) * ELEMENT_TILE_HEIGHT);
                    } else {
                        info.at(atomicNumber - 1) = false;

                        element_image.at(0)->DrawSeperate(j * ELEMENT_TILE_WIDTH + 8, (i + 1) * ELEMENT_TILE_HEIGHT);
                    }
                    if (currentCursor.at(atomicNumber - 1))
                        cursor->DrawSeperate(j * ELEMENT_TILE_WIDTH + 1, (i + 1) * ELEMENT_TILE_HEIGHT - 6);
                }
            }
        }
    } else {
        is_in_info = true;

        element_info_bg->SpriteDraw();

        if (info.at(currentCursorIndex)) {
            element_image_info.at(currentCursorIndex + 1)->DrawSeperate( (1024 - ELEMENT_INFO_WIDTH) / 2, 32);

            RenderInfo(currentCursorIndex + 1);
        } else {
            element_image_info.at(0)->DrawSeperate( (1024 - ELEMENT_INFO_WIDTH) / 2, 32);

            RenderInfo(0);
        }

        switch (sdl_setup->GetEvent()->type) {
        case SDL_KEYDOWN:
            switch (sdl_setup->GetEvent()->key.keysym.sym) {
            case SDLK_BACKSPACE:
                choose_sound->Play();

                info.at(currentCursorIndex) = false;
                isChosen = false;

                break;

            default: break;
            }

        default: break;
        }
    }
}

void PeriodicTable::RenderInfo(const int& _Z)
{
    std::string current_info = GetInfo(_Z);

    info_text_surface = TTF_RenderText_Blended_Wrapped(text_font, current_info.c_str(), text_colour, 874);
    info_text_rect = {75, 192, info_text_surface->w, info_text_surface->h};
    info_text_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), info_text_surface);

    SDL_RenderCopy(sdl_setup->GetRenderer(), info_text_texture, NULL, &info_text_rect);

    SDL_FreeSurface(info_text_surface); info_text_surface = NULL;
    SDL_DestroyTexture(info_text_texture); info_text_texture = NULL;

    backspace->SpriteDraw();
    SDL_RenderCopy(sdl_setup->GetRenderer(), return_to_pt_texture, NULL, &return_to_pt_rect);

    a_button->SpriteDraw();
    SDL_RenderCopy(sdl_setup->GetRenderer(), prev_element_texture, NULL, &prev_element_rect);

    d_button->SpriteDraw();
    SDL_RenderCopy(sdl_setup->GetRenderer(), next_element_texture, NULL, &next_element_rect);
}

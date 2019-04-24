#include "../include/Map.h"

Map::Map(SDL_Setup* _sdl_setup, const int& _SCREEN_WIDTH, const int& _SCREEN_HEIGHT,
         MainCharacter* _main_char, PeriodicTable* _periodicTable, PopUp* _pop_up)
{
    sdl_setup = _sdl_setup;

    main_char = _main_char;

    periodicTable = _periodicTable;

    pop_up = _pop_up;

    SCREEN_WIDTH = _SCREEN_WIDTH;
    SCREEN_HEIGHT = _SCREEN_HEIGHT;

    TILE_WIDTH = 32;
    TILE_HEIGHT = 32;

    ROW = SCREEN_HEIGHT / TILE_HEIGHT;
    COLUMN = SCREEN_WIDTH / TILE_WIDTH;

    std::string MAP_BACKGROUND_FILE_PATH = "Sprites/Maps/Background.png";
    map_background = new Sprite(sdl_setup->GetRenderer(), MAP_BACKGROUND_FILE_PATH,
                                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    AMOUNT_OF_MAPS = 12;

    for (int i = 0; i < AMOUNT_OF_MAPS; ++i) {
        MAP_LAYOUT_FILE_PATH.push_back("Data/Maps/Map[" + std::to_string(i) + "].map");

        current_map.push_back( std::vector< std::vector<int> > (ROW, std::vector<int>(COLUMN)) );
    }

    Load();

    wall = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/Wall.png", -32, -32, 32, 32);

    element_ball = std::vector<Sprite*> (5, NULL);

    element_ball.at(BLUE) = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/blue.png", -32, -32, 16, 16);
    element_ball.at(GREEN) = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/green.png", -32, -32, 16, 16);
    element_ball.at(PURPLE) = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/purple.png", -32, -32, 16, 16);
    element_ball.at(RED) = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/red.png", -32, -32, 16, 16);
    element_ball.at(YELLOW) = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/yellow.png", -32, -32, 16, 16);

    element_ball_shadow = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/shadow.png", -32, -32, 16, 16);

    portal_to_previous_stage = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/prev_portal.png", -32, -32, 32, 32);
    portal_to_next_stage = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/next_portal.png", -32, -32, 32, 32);
    portal_to_next_stage->SetupAnimation(4, 1);

    found_element = false;
    got_element = false;

    element_found = -1;

    found_element_sound = new Sound("Audio/SE/FoundElement.ogg"); found_element_sound->SetVolume(16);
    got_element_sound = new Sound("Audio/SE/GotElement.ogg"); got_element_sound->SetVolume(16);
    found_element_sound_play = false;

    std::string FONT_FILE_PATH = "Fonts/pkmnfl.ttf";
    text_font = NULL;
    text_font = TTF_OpenFont(FONT_FILE_PATH.c_str(), 24);
    text_colour = {255, 255, 255};

    e_button = new Sprite(sdl_setup->GetRenderer(), "Sprites/Maps/letter_E.png",
                          0, 0, 32, 32);
    open_pt_surface = TTF_RenderText_Blended(text_font, "Open Periodic Table", text_colour);
    open_pt_rect = {40, (e_button->get_h() - open_pt_surface->h) / 2 + e_button->get_y() + 1,
                         open_pt_surface->w, open_pt_surface->h};
    open_pt_texture = SDL_CreateTextureFromSurface(sdl_setup->GetRenderer(), open_pt_surface);
}

Map::~Map()
{
    delete sdl_setup;

    delete map_background;

    delete portal_to_previous_stage;
    delete portal_to_next_stage;

    delete e_button;
    SDL_FreeSurface(open_pt_surface);
    SDL_DestroyTexture(open_pt_texture);

    for (int i = 0; i < 5; ++i)
        delete element_ball.at(i);
    delete element_ball_shadow;

    delete wall;

    delete found_element_sound;
    delete got_element_sound;

    delete main_char;
    delete periodicTable;
    delete pop_up;
}

void Map::SetDefault()
{
    current_map_index = 0;

    for (int i = 0; i < AMOUNT_OF_MAPS; ++i) {
        std::ifstream default_map_input("Data/Maps/Default/DefaultMap[" + std::to_string(i) + "].chem");

        for (int j = 0; j < ROW; ++j)
            for (int k = 0; k < COLUMN; ++k)
                default_map_input >> current_map.at(i).at(j).at(k);

        default_map_input.close();
    }

    Save();
    Load();
}

void Map::Load()
{
    /*
     * Load current map index
     */
    std::ifstream current_map_index_input("Data/Save/CurrentMapIndex.chem");
    current_map_index_input >> current_map_index;
    current_map_index_input.close();

    /*
     * Load maps' layout
     */
    for (int i = 0; i < AMOUNT_OF_MAPS; ++i) {
        std::ifstream map_input(MAP_LAYOUT_FILE_PATH.at(i));

        for (int j = 0; j < ROW; ++j) {
            for (int k = 0; k < COLUMN; ++k) {
                int type = -1;
                map_input >> type;

                if (type >= 0) current_map.at(i).at(j).at(k) = type;
            }
        }

        map_input.close();
    }
}

void Map::Save()
{
    /*
     * Save current map index
     */
    std::ofstream current_map_index_output("Data/Save/CurrentMapIndex.chem");
    current_map_index_output << current_map_index;
    current_map_index_output.close();

    /*
     * Save maps' layout
     */
    for (int i = 0; i < AMOUNT_OF_MAPS; ++i) {
        std::ofstream map_output(MAP_LAYOUT_FILE_PATH.at(i));

        for (int j = 0; j < ROW; ++j) {
            for (int k = 0; k < COLUMN; ++k) {
                map_output.width(4);
                map_output << current_map.at(i).at(j).at(k);
            }
            map_output << std::endl;
        }

        map_output.close();
    }
}

void Map::UpdateMap(Sprite* _portal)
{
    if (_portal == portal_to_next_stage) {
        current_map_index++;
        if (current_map_index >= AMOUNT_OF_MAPS - 1) current_map_index = AMOUNT_OF_MAPS - 1;
    } else if (_portal == portal_to_previous_stage) {
        current_map_index--;
        if (current_map_index <= 0) current_map_index = 0;
    }
}

void Map::RenderMap()
{
    int tileType = 0;

    map_background->SpriteDraw();

    main_char->CharacterDraw();

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            tileType = current_map.at(current_map_index).at(i).at(j);

            switch (tileType) {
            // Metalloids (Map[7])
            case 5: case 14: case 32: case 33: case 34: case 51: case 52:
                element_ball.at(BLUE)->DrawSeperate(j * TILE_WIDTH + element_ball.at(BLUE)->get_w() / 2,
                                                    i * TILE_HEIGHT + element_ball.at(BLUE)->get_h() / 2);
                element_ball_shadow->DrawSeperate(j * TILE_WIDTH + element_ball_shadow->get_w() / 2,
                                                  i * TILE_HEIGHT + element_ball_shadow->get_h() / 2 + 3);
                break;

            // Non-Metal (Map[5])
            case 6: case 7: case 8: case 9: case 15: case 16: case 17: case 35: case 53:
                element_ball.at(GREEN)->DrawSeperate(j * TILE_WIDTH + element_ball.at(GREEN)->get_w() / 2,
                                                     i * TILE_HEIGHT + element_ball.at(GREEN)->get_h() / 2);
                element_ball_shadow->DrawSeperate(j * TILE_WIDTH + element_ball_shadow->get_w() / 2,
                                                  i * TILE_HEIGHT + element_ball_shadow->get_h() / 2 + 3);
                break;

            // Noble (Map[8])
            case 2: case 10: case 18: case 36: case 54: case 86:
                element_ball.at(PURPLE)->DrawSeperate(j * TILE_WIDTH + element_ball.at(PURPLE)->get_w() / 2,
                                                      i * TILE_HEIGHT + element_ball.at(PURPLE)->get_h() / 2);
                element_ball_shadow->DrawSeperate(j * TILE_WIDTH + element_ball_shadow->get_w() / 2,
                                                  i * TILE_HEIGHT + element_ball_shadow->get_h() / 2 + 3);
                break;

            // Akali (Map[1])
            case 3: case 4: case 11: case 12: case 19: case 20: case 37: case 38: case 55: case 56:
                element_ball.at(RED)->DrawSeperate(j * TILE_WIDTH + element_ball.at(RED)->get_w() / 2,
                                                   i * TILE_HEIGHT + element_ball.at(RED)->get_h() / 2);
                element_ball_shadow->DrawSeperate(j * TILE_WIDTH + element_ball_shadow->get_w() / 2,
                                                  i * TILE_HEIGHT + element_ball_shadow->get_h() / 2 + 3);
                break;

            // Post (Map[3])
            case 13: case 31: case 49: case 50: case 81: case 82: case 83: case 84:
            // Trans_1 (Map[2])
            case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
            // Trans_2 (Map[4])
            case 39: case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48:
            // Trans_3 (Map[6])
            case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79: case 80:
            // Trans_4 - Lanthanides (Map[9])
            case 57: case 58: case 59: case 60: case 61: case 62: case 63: case 64: case 65: case 66: case 67: case 68: case 69: case 70: case 71:
            // Trans_5 - Actinides (Map[10])
            case 89: case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101: case 102: case 103:
            // ShortLife (Map[11])
            case 87: case 88: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118:
                element_ball.at(YELLOW)->DrawSeperate(j * TILE_WIDTH + element_ball.at(YELLOW)->get_w() / 2,
                                                      i * TILE_HEIGHT + element_ball.at(YELLOW)->get_h() / 2);
                element_ball_shadow->DrawSeperate(j * TILE_WIDTH + element_ball_shadow->get_w() / 2,
                                                  i * TILE_HEIGHT + element_ball_shadow->get_h() / 2 + 3);
                break;

            case 198:
                wall->DrawSeperate(j * TILE_WIDTH, i * TILE_HEIGHT);
                break;

            case 199:
                portal_to_previous_stage->DrawSeperate(j * TILE_WIDTH, i * TILE_HEIGHT);
                break;


            case 200:
                portal_to_next_stage->DrawSeperate(j * TILE_WIDTH, i * TILE_HEIGHT);
                portal_to_next_stage->Animation(0, 3, 0, 200);
                break;

            default: break;
            }

            Collision();
        }
    }

    e_button->SpriteDraw();
    SDL_RenderCopy(sdl_setup->GetRenderer(), open_pt_texture, NULL, &open_pt_rect);

    if (found_element) {
        //found_element_sound_play = true;

        if (found_element_sound_play) {
            found_element_sound->Play();
            found_element_sound_play = false;
        }

        if (element_found > 0) {
            main_char->start_moving = false;
            got_element = false;

            pop_up->RenderPopUp(element_found);
        } else {
            main_char->start_moving = true;
            found_element = false;
        }

        const Uint8* current_key_state = SDL_GetKeyboardState(NULL);
        if (current_key_state[SDL_SCANCODE_RETURN]) {
            found_element = false;
            got_element = true;
            main_char->start_moving = true;
            element_found = 0;
        }

        current_key_state = nullptr;
        delete current_key_state;
    }

    Save();
}

/*
 * Rectangle collision
 */
void Map::Collision()
{
    //SDL_Rect char_rect = main_char->GetChar()->GetImageRect();

    for (int i = 0; i < 5; ++i)
        ElementBallCollision(main_char, element_ball.at(i));

    PortalCollision(main_char);

    WallCollision(main_char);
}

/*
 * To handle collision with element balls
 */
void Map::ElementBallCollision(MainCharacter* _main_char, Sprite* _element_ball)
{
    SDL_Rect char_rect = _main_char->GetChar()->GetImageRect();

    SDL_Rect element_ball_rect = _element_ball->GetImageRect();

    if (SDL_HasIntersection(&char_rect, &element_ball_rect)) {
        found_element = true;

        /*if (found_element_sound_play) {
            found_element_sound->Play();
            found_element_sound_play = false;
        }
        //found_element_sound->Play();*/

        element_found = current_map.at(current_map_index).at(element_ball_rect.y / TILE_HEIGHT).at(element_ball_rect.x / TILE_WIDTH);

        if (got_element) {
            got_element_sound->Play();

            current_map.at(current_map_index).at(element_ball_rect.y / TILE_HEIGHT).at(element_ball_rect.x / TILE_WIDTH) = 0;
            got_element = false;
        }

        periodicTable->FoundElement(element_found);
    }
}

/*
 * To handle collision with portals
 */
void Map::PortalCollision(MainCharacter* _main_char)
{
    SDL_Rect char_rect = _main_char->GetChar()->GetImageRect();

    SDL_Rect next_portal_rect = portal_to_next_stage->GetImageRect();
    SDL_Rect previous_portal_rect = portal_to_previous_stage->GetImageRect();

    if (SDL_HasIntersection(&char_rect, &next_portal_rect)) {
        SDL_Delay(500);
        UpdateMap(portal_to_next_stage);
        if (char_rect.x + char_rect.w >= next_portal_rect.x)
            main_char->GetChar()->set_x(546);
        if (char_rect.y + char_rect.h >= next_portal_rect.y)
            main_char->GetChar()->set_y(510);
    }

    if (SDL_HasIntersection(&char_rect, &previous_portal_rect)) {
        SDL_Delay(500);
        UpdateMap(portal_to_previous_stage);
        if (char_rect.x + char_rect.w >= previous_portal_rect.x)
            main_char->GetChar()->set_x(546);
        if (char_rect.y + char_rect.h >= previous_portal_rect.y)
            main_char->GetChar()->set_y(31);
    }
}

void Map::WallCollision(MainCharacter* _main_char)
{
    SDL_Rect char_rect = _main_char->GetChar()->GetImageRect();

    SDL_Rect wall_rect = wall->GetImageRect();

    if (SDL_HasIntersection(&char_rect, &wall_rect))
        HandleCollision(char_rect, wall_rect);
}

/*
 * To check if there is collision then handle it
 */
void Map::HandleCollision(const SDL_Rect& _char_rect, const SDL_Rect& _object_rect)
{
    if (SDL_HasIntersection(&_char_rect, &_object_rect)) {
        if (_char_rect.x + _char_rect.w > _object_rect.x && _char_rect.x < _object_rect.x)
            main_char->GetChar()->set_x(main_char->GetChar()->get_x() - (int) (float) main_char->GetStep() * 1.5);
        if (_char_rect.y + _char_rect.h > _object_rect.y && _char_rect.y < _object_rect.y)
            main_char->GetChar()->set_y(main_char->GetChar()->get_y() - (int) (float) main_char->GetStep() * 1.5);
        if (_char_rect.x < _object_rect.x + _object_rect.w && _char_rect.x > _object_rect.x)
            main_char->GetChar()->set_x(main_char->GetChar()->get_x() + (int) (float) main_char->GetStep() * 1.5);
        if (_char_rect.y < _object_rect.y + _object_rect.h && _char_rect.y > _object_rect.y)
            main_char->GetChar()->set_y(main_char->GetChar()->get_y() + (int) (float) main_char->GetStep() * 1.5);
    }
}

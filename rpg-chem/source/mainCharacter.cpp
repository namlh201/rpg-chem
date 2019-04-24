#include "../include/mainCharacter.h"

MainCharacter::MainCharacter(SDL_Setup* _sdl_setup)
{
    sdl_setup = _sdl_setup;

    LoadPosition();

    character = new Sprite(sdl_setup->GetRenderer(), "Sprites/Game/Character/Mendeleev.png", pos_x, pos_y, 28, 28);
    character->SetupAnimation(4, 4);
    character->Animation(0, 0, 0, 0);                // Initial character animation

    shadow = new Sprite(sdl_setup->GetRenderer(), "Sprites/Game/Character/shadow.png", pos_x, pos_y + 4, 28, 28);

    time_check = SDL_GetTicks();

    start_moving = true;

    step = 3;                                   // Initialise
    move_up = false;
    move_left = false;
    move_down = false;
    move_right = false;
    sprint = false;
}

MainCharacter::~MainCharacter()
{
    delete character;
    delete shadow;
    delete sdl_setup;
}

void MainCharacter::SetDefault()
{
    pos_x = 514;
    pos_y = 512;

    SavePosition();
}

void MainCharacter::Update()                // Update character after every keyboard event
{
    if (start_moving) {
        const Uint8* current_key_state = SDL_GetKeyboardState(NULL);
        if (current_key_state[SDL_SCANCODE_W]) move_up = true;
        else move_up = false;
        if (current_key_state[SDL_SCANCODE_A]) move_left = true;
        else move_left = false;
        if (current_key_state[SDL_SCANCODE_S]) move_down = true;
        else move_down = false;
        if (current_key_state[SDL_SCANCODE_D]) move_right = true;
        else move_right = false;
        if (current_key_state[SDL_SCANCODE_LSHIFT]) sprint = true;
        else sprint = false;

        current_key_state = nullptr;
        delete current_key_state;
    } else {
        move_up = false;
        move_left = false;
        move_down = false;
        move_right = false;
        sprint = false;
    }

    if (time_check + 3 < SDL_GetTicks()) {
        if (sprint) step = 6;               // Increase speed when sprint
        else step = 3;

        if (move_up) {
            character->Animation(0, 3, 3, 150);  // 4th row
            character->set_y( character->get_y() - step );
        }
        if (move_left) {
            character->Animation(0, 3, 1, 150);  // 2nd row
            character->set_x( character->get_x() - step );
        }
        if (move_down) {
            character->Animation(0, 3, 0, 150);  // 1st row
            character->set_y( character->get_y() + step );
        }
        if (move_right) {
            character->Animation(0, 3, 2, 150);  // 3rd row
            character->set_x( character->get_x() + step );
        }

        if( character->get_x() <= 0)
            character->set_x(0);
        if( character->get_y() <= 0)
            character->set_y(0);
        if( character->get_x() >= 1024 - character->get_w())
            character->set_x(1024 - character->get_w());
        if( character->get_y() >= 576 - character->get_h())
            character->set_y(576 - character->get_h());

        time_check = SDL_GetTicks();
    }

    shadow->set_x( character->get_x() );
    shadow->set_y( character->get_y() + 4 );
}

void MainCharacter::SavePosition()
{
    std::ofstream position_output("Data/Save/CurrentPosition.chem");
    position_output << character->get_x() << ' ' << character->get_y();
    position_output.close();
}

void MainCharacter::LoadPosition()
{
    std::ifstream position_input("Data/Save/CurrentPosition.chem");
    position_input >> pos_x >> pos_y;
    position_input.close();
}

void MainCharacter::CharacterDraw()
{
    Update();
    character->SpriteDraw();
    shadow->SpriteDraw();

    SavePosition();
}

void MainCharacter::CharacterDraw(const int& _x, const int& _y)         // Draw character after every update
{
    Update();
    character->DrawSeperate(_x, _y);
    shadow->DrawSeperate(_x, _y);
}

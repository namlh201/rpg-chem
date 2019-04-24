#include "../include/Main.h"

Main::Main(const int& _MAIN_PROGRAM_WIDTH, const int& _MAIN_PROGRAM_HEIGHT)
{                           // ctor
    quit = false;

    std::string PROGRAM_TITLE = "A-maze-ing Chemistry";
    sdl_setup = new SDL_Setup(&quit, _MAIN_PROGRAM_WIDTH, _MAIN_PROGRAM_HEIGHT, PROGRAM_TITLE);

    main_char = new MainCharacter(sdl_setup);

    start_screen = new StartScreen(sdl_setup);
    ss_choose_sound = new Sound("Audio/SE/SSChoose.wav"); ss_choose_sound->SetVolume(32);

    periodic_table = new PeriodicTable(sdl_setup);
    enter_periodic_table_sound = new Sound("Audio/SE/EnterPeriodicTable.ogg");
    enter_periodic_table_sound->SetVolume(32);
    escape_periodic_table_sound = new Sound("Audio/SE/EscapePeriodicTable.ogg");
    escape_periodic_table_sound->SetVolume(32);

    pop_up = new PopUp(sdl_setup, periodic_table);

    anotherMap = new Map(sdl_setup, _MAIN_PROGRAM_WIDTH, _MAIN_PROGRAM_HEIGHT,
                         main_char, periodic_table, pop_up);

    music = new Music("Audio/ME/Soundtrack.mp3");
}

Main::~Main()               // dtor
{
    delete sdl_setup;
    delete main_char;
    delete start_screen;
    delete ss_choose_sound;
    delete anotherMap;
    delete periodic_table;
    delete pop_up;
    delete music;
}

void Main::GameLoop()       // Setup game loop
{
    //Frame per sec value
    const int FPS = 60;
    // delay time per frame
    const int frameDelay = 1000 / FPS;
    //start time when the loop start aka start time of frame
    Uint32 frameStart;
    int frameTime;

    music->Play();

    bool is_start_screen = true;
    bool in_game = false;
    bool NewGame = false;
    bool is_periodic_table = false;

    // Start screen
    while (!quit && is_start_screen && sdl_setup->GetEvent()->type != SDL_QUIT) {
        sdl_setup->Begin();

        start_screen->ScreenDraw();

        const Uint8* current_key_state = SDL_GetKeyboardState(NULL);
        if (current_key_state[SDL_SCANCODE_RETURN]) {
            ss_choose_sound->Play();

            if (start_screen->GetState() == 1) {
                NewGame = true;
                in_game = true;
            } else if (start_screen->GetState() == 2) {
                in_game = true;
            } else if (start_screen->GetState() == 3) {
                quit = true;
            }
            is_start_screen = false;
        }

        current_key_state = nullptr;
        delete current_key_state;

        sdl_setup->End();
    }

    // In game
    while (!quit && in_game && sdl_setup->GetEvent()->type != SDL_QUIT) {
        if (NewGame) {
            SetDefault();
            NewGame = false;
        }

        frameStart = SDL_GetTicks();

        sdl_setup->Begin();

        if (!is_periodic_table) {
            anotherMap->RenderMap();

            const Uint8* current_key_state = SDL_GetKeyboardState(NULL);
            if (current_key_state[SDL_SCANCODE_E]) {
                enter_periodic_table_sound->Play();
                is_periodic_table = true;
            }
            current_key_state = nullptr;
            delete current_key_state;
        } else {
            periodic_table->RenderPeriodicTable();

            if (!periodic_table->IsInInfo()) {
                const Uint8* current_key_state = SDL_GetKeyboardState(NULL);
                if (current_key_state[SDL_SCANCODE_ESCAPE]) {
                    escape_periodic_table_sound->Play();
                    is_periodic_table = false;
                }
                current_key_state = nullptr;
                delete current_key_state;
            }
        }

        sdl_setup->End();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)   //the time the frame took to execute
           SDL_Delay(frameDelay - frameTime);   //if the time of frame lower than time per frame, delay it a period of time
    }
}

void Main::SetDefault()
{
    anotherMap->SetDefault();
    periodic_table->SetDefault();
    main_char->SetDefault();
}

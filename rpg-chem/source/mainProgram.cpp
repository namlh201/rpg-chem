#include "../include/stdafx.h"
#include "../include/SDL_Setup.h"
#include "../include/Main.h"

int main(int argc, char** argv) {
    srand(time(0));

    Main* main_program = new Main(1024, 576);

    main_program->GameLoop();

    return 0;
}

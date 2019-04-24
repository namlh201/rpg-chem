#include "../include/Music.h"

Music::Music(const std::string& _MUSIC_FILE_PATH): Audio()
{
    music = NULL;
    music = Mix_LoadMUS(_MUSIC_FILE_PATH.c_str());
}

Music::~Music()
{
    Mix_FreeMusic(music);
    music = NULL;
}

void Music::Play()
{
    Mix_PlayMusic(music, -1);
}

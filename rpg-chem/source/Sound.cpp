#include "../include/Sound.h"

Sound::Sound(const std::string& _SOUND_FILE_PATH): Audio()
{
    chunk = NULL;
    chunk = Mix_LoadWAV(_SOUND_FILE_PATH.c_str());
}

Sound::~Sound()
{
    Mix_FreeChunk(chunk);
    chunk = NULL;
}

void Sound::Play()
{
    Mix_PlayChannel(-1, chunk, 0);
}

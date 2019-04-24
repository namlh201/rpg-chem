#include "../include/Audio.h"

Audio::Audio()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
}

Audio::~Audio()
{
    Mix_CloseAudio();

    Mix_Quit();
}

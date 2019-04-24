#ifndef SOUND_H
#define SOUND_H

#include "stdafx.h"
#include "Audio.h"

class Sound: public Audio
{
protected:
    Mix_Chunk* chunk;

public:
    Sound(const std::string& _SOUND_FILE_PATH);
    ~Sound();

    void Play();

    void SetVolume(const int& _volume) { Mix_VolumeChunk(chunk, _volume); };
};

#endif // SOUND_H

#ifndef MUSIC_H
#define MUSIC_H

#include "stdafx.h"
#include "Audio.h"

class Music: public Audio
{
protected:
    Mix_Music* music;

public:
    Music(const std::string& _MUSIC_FILE_PATH);
    ~Music();

    void Play();

    void SetVolume(const int& _volume) { Mix_VolumeMusic(_volume); };
    int GetVolume() { return Mix_VolumeMusic(-1); };
};
#endif // MUSIC_H

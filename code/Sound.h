#pragma once

#include <SDL_mixer.h>

class Sound
{
private:
    Mix_Chunk* bonk = NULL;
    Mix_Chunk* breath = NULL;
public:

    void Intialize();
    void PlayBreath();
    void PlayBonk();

};

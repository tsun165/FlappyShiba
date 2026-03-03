#pragma once

#include <SDL_mixer.h>
#include <SDL.h>

class Sound
{
public:
    void Intialize();
    void PlayBreath();
    void PlayBonk();

private:
    Mix_Chunk* bonk;
    Mix_Chunk* breath;
};

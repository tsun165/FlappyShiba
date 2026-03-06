#pragma once

#include <SDL_mixer.h>
#include <SDL.h>

class Sound
{
public:
    void intialize();
    void playBreath();
    void playBonk();
    void playPlus();

private:
    Mix_Chunk* bonk;
    Mix_Chunk* breath;
    Mix_Chunk* plus;
};

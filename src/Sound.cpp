#include "Sound.h"

void Sound::intialize()
{
    bonk = Mix_LoadWAV("asset\\sound\\sfx_bonk.wav");
    breath = Mix_LoadWAV("asset\\sound\\sfx_breath.wav");
    plus = Mix_LoadWAV("asset\\sound\\score.wav");
}

void Sound::playBreath()
{
    if (Mix_PlayChannel(1, breath, 0) == -1)
    {
        SDL_Log("Failed to play breath sound: %s", Mix_GetError());
    }
}

void Sound::playBonk()
{
    if (Mix_PlayChannel(2, bonk, 0) == -1)
    {
        SDL_Log("Failed to play bonk sound: %s", Mix_GetError());
    }
}

void Sound::playPlus()
{
    if (Mix_PlayChannel(2, plus, 0) == -1)
    {
        SDL_Log("Failed to play bonk sound: %s", Mix_GetError());
    }
}


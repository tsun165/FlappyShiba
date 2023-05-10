#include "Sound.h"
#include <SDL.h>


void Sound::Intialize()
{
    bonk = Mix_LoadWAV("..\\res\\sound\\sfx_bonk.wav");
    breath = Mix_LoadWAV("..\\res\\sound\\sfx_breath.wav");
}

void Sound::PlayBreath()
{
    if (Mix_PlayChannel(1, breath, 0) == -1)
    {
        SDL_Log(Mix_GetError());
        throw 1;
    }
}
void Sound::PlayBonk()
{
    if (Mix_PlayChannel(2, bonk, 0) == -1)
    {
        SDL_Log(Mix_GetError());
        throw 1;
    }
}


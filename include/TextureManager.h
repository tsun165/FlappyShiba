#pragma once

#include <SDL_image.h>
#include <SDL.h>

class TextureManager
{
public:
    static SDL_Texture* Texture(const char* filelocation, SDL_Renderer* ren);

};

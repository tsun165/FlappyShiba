#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

class Object {
public:
    //Constructor
    Object();
    virtual ~Object();

    //API
    SDL_Rect& getSrc();
    SDL_Rect& getDest();
    SDL_Texture* getTexture();
    void setSrc(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);
    void setTexture(const char* address, SDL_Renderer* ren);
    virtual void render(SDL_Renderer* ren);

private:
    SDL_Rect src, dest;
    SDL_Texture* tex;

};

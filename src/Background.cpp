#include "Background.h"

void Background::render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), NULL, NULL);
}

#include "Object.h"

Object::Object()
    : src{ 0, 0, 0, 0 },
    dest{ 0, 0, 0, 0 },
    tex(nullptr)
{
}

Object::~Object()
{
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}


SDL_Rect& Object::getSrc()
{
    return src;
}

SDL_Rect& Object::getDest()
{
    return dest;
}

SDL_Texture* Object::getTexture()
{
    return tex;
}

void Object::setSrc(int x, int y, int w, int h)
{
    this->src.x = x;
    this->src.y = y;
    this->src.w = w;
    this->src.h = h;
}

void Object::setDest(int x, int y, int w, int h)
{
    this->dest.x = x;
    this->dest.y = y;
    this->dest.w = w;
    this->dest.h = h;
}

void Object::setTexture(const char* address, SDL_Renderer* ren)
{
    tex = TextureManager::Texture(address, ren);
}

void Object::render(SDL_Renderer* ren)
{
}

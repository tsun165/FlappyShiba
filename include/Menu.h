#pragma once

#include "Object.h"

class Menu : public Object
{


public:
    int MENUWIDTH;
    int MENUHEIGHT;
    void render(SDL_Renderer* ren);
    void stay(int MENUWIDTH, int MENUHEIGHT);
    bool isClicked(int x, int y);

};

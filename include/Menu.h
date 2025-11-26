#pragma once
#include "Object.h"


class Menu : public Object
{


public:
    int MENUWIDTH;
    int MENUHEIGHT;
    void Render(SDL_Renderer* ren);
    void Stay(int MENUWIDTH, int MENUHEIGHT);
    bool IsClicked(int x, int y);

};

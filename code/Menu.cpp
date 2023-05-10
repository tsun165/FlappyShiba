#include "Menu.h"


void Menu::Render(SDL_Renderer* ren)
{
    if(SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest()) == -1)
    {
        SDL_Log(SDL_GetError());
        throw 1;
    }

}
void Menu::Stay(int MENUWIDTH, int MENUHEIGHT)
{
    setSource(0, 0, MENUWIDTH, MENUHEIGHT);
    setDest(62, 140, MENUWIDTH, MENUHEIGHT);

}

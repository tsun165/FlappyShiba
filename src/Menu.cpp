#include "Menu.h"


void Menu::Render(SDL_Renderer* ren)
{
    if(SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest()) == -1)
    {
        SDL_Log(SDL_GetError());
    }

}
void Menu::Stay(int MENUWIDTH, int MENUHEIGHT)
{
    setSource(0, 0, MENUWIDTH, MENUHEIGHT);
    setDest(62, 140, MENUWIDTH, MENUHEIGHT);

}

bool Menu::IsClicked(int x, int y)
{
    SDL_Rect& rect = getDest();
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

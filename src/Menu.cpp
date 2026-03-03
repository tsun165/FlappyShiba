#include "Menu.h"


void Menu::render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Menu::stay(int MENUWIDTH, int MENUHEIGHT)
{
    setSrc(0, 0, MENUWIDTH, MENUHEIGHT);
    setDest(62, 140, MENUWIDTH, MENUHEIGHT);

}

bool Menu::isClicked(int x, int y)
{
    SDL_Rect& rect = getDest();
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

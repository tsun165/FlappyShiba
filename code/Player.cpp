#include "Player.h"

void Player::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}
void Player::Gravity()
{
    Yvelocity += gravity;
    Ypos += Yvelocity;
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(Xpos, Ypos, PLAYERWIDTH, PLAYERHEIGHT);
}
void Player::Jump()
{
    Yvelocity += jumpHeight;
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(Xpos, Ypos, PLAYERWIDTH, PLAYERHEIGHT);
}

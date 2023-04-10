#include "Player.h"

void Player::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}
void Player::Gravity()
{
    Ypos += gravity;
    setSource(0, 0, 50, 35);
    setDest(25, Ypos, 50, 35);
}
void Player::Jump()
{
    Ypos += jumpHeight;
    setSource(0, 0, 50, 35);
    setDest(25, Ypos, 50, 35);
    SDL_Delay(25);


}

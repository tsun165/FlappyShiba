#include "Player.h"

void Player::Intialize()
{
    gravity = 0.7;
    yVelocity = 0;
    yPos = 240;
    xPos = 25;
    jumpHeight = -13;
    Stay();
}
void Player::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}
void Player::Gravity()
{
    yVelocity += gravity;
    yPos += yVelocity;
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}
void Player::Jump()
{
    yVelocity  += jumpHeight;

    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}
void Player::Stay()
{
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}

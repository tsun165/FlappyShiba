#include "Player.h"

void Player::Intialize()
{
    // Physics constants tuned for Flappy Shiba feel (chậm hơn)
    gravity = 0.45;          // Gia tốc rơi chậm hơn
    yVelocity = 0;           // Vận tốc hiện tại
    maxFallSpeed = 7.0;      // Giới hạn tốc độ rơi
    jumpVelocity = -9.5;     // Nhảy yếu hơn một chút
    
    // Vị trí bắt đầu
    yPos = 240;
    xPos = 25;
    
    Stay();
}

void Player::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Player::Update()
{
    // Apply gravity (accelerate downward)
    yVelocity += gravity;
    
    // Clamp fall speed to maximum
    if(yVelocity > maxFallSpeed)
    {
        yVelocity = maxFallSpeed;
    }
    
    // Update position
    yPos += yVelocity;
    
    // Prevent going above screen
    if(yPos < 0)
    {
        yPos = 0;
        yVelocity = 0;
    }
    
    // Prevent going below screen (ground collision)
    if(yPos > 450)  // 485 - 35 (PLAYERHEIGHT)
    {
        yPos = 450;
        yVelocity = 0;
    }
    
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}

void Player::Jump()
{
    // Set velocity to jump speed (not add to it!)
    // This gives consistent jump height regardless of current velocity
    yVelocity = jumpVelocity;
    
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}

void Player::Stay()
{
    setSource(0, 0, PLAYERWIDTH, PLAYERHEIGHT);
    setDest(xPos, yPos, PLAYERWIDTH, PLAYERHEIGHT);
}

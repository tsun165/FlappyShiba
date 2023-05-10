#pragma once

#include "Object.h"

class Player : public Object
{


public:

    double gravity;
    double yVelocity;
    double yPos;
    double xPos;
    double jumpHeight;
    const int PLAYERWIDTH = 50;
    const int PLAYERHEIGHT = 35;

    void Intialize();
    void Render(SDL_Renderer* ren);
    void Jump();
    bool JumpState();
    void Gravity();
    void Stay();
};



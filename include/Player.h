#pragma once

#include "Object.h"

class Player : public Object
{


public:

    double gravity;
    double yVelocity;
    double yPos;
    double xPos;
    double jumpVelocity;
    double maxFallSpeed;
    const int PLAYERWIDTH = 50;
    const int PLAYERHEIGHT = 35;

    void Intialize();
    void Render(SDL_Renderer* ren);
    void Jump();
    bool JumpState();
    void Update();
    void Stay();
};



#pragma once

#include <iostream>

#include "Object.h"

class Player : public Object
{



public:

    double gravity = 0.3;
    double Yvelocity = 0;
    double Ypos = 256;
    double Xpos = 25;
    double jumpHeight = -8;
    const int PLAYERWIDTH = 50;
    const int PLAYERHEIGHT = 35;

    void Render(SDL_Renderer* ren);
    void Jump();
    bool JumpState();
    void Gravity();
};

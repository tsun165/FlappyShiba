#pragma once

#include <iostream>

#include "Object.h"

class Player : public Object
{
private:
    double gravity = 0.4;
    double Ypos = 256;
    double jumpHeight = -40;


public:
    void Render(SDL_Renderer* ren);
    void Jump();
    bool JumpState();
    void Gravity();
};

#pragma once

#include "Object.h"

class Player : public Object {
public:
    void Intialize();
    void render(SDL_Renderer* ren);
    void Jump();
    //bool JumpState();
    void Update();
    void Stay();

//private: 
    const int PLAYERWIDTH = 50;
    const int PLAYERHEIGHT = 35;

    double gravity;
    double yVelocity;
    double yPos;
    double xPos;
    double jumpVelocity;
    double maxFallSpeed;
    
};



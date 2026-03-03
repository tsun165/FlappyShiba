#pragma once

#include "Object.h"

class Pipe : public Object
{
public:
    void Intialize();
    void render(SDL_Renderer* ren);
    void PipeMoveUp();
    void PipeMoveDown();

//private:

    const int PIPEWIDTH = 65;
    const int PIPEDISTANCE = 150;
    const int listPipeHeight[5] = {160, 70, 190, 290, 230};

    int xVelocity;
    int xPos;
    int indexPipeHeight;
    int score;
    int pipeHeight;

};

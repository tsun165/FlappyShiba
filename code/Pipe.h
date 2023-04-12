#pragma once

#include "Object.h"

class Pipe : public Object
{




public:

    int PIPEDISTANCE = 220;
    double Xvelocity = -3;
    double Xpos = 320;
    const int PIPEWIDTH = 65;
    int PIPEHEIGHT = 180;
    double SCORE = 0;

    void Render(SDL_Renderer* ren);
    void PipeMoveUp();
    void PipeMoveDown();


};

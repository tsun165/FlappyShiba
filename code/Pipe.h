#pragma once

#include "Object.h"

class Pipe : public Object
{
private:



public:


    const int PIPEWIDTH = 65;
    const int PIPEDISTANCE = 150;

    double xVelocity ;
    double xPos ;
    double indexPipeHeight;
    double SCORE;

    int listPipeHeight[5] = {160, 70, 190, 290, 230};
    int PIPEHEIGHT;


    void Intialize();
    void Render(SDL_Renderer* ren);
    void PipeMoveUp();
    void PipeMoveDown();


};

#include "Pipe.h"



void Pipe::Intialize()
{
    xVelocity = -4;
    SCORE = 0;

}
void Pipe::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Pipe::PipeMoveUp()
{
    if(xPos < -PIPEWIDTH)
    {
        xPos = 320 + PIPEWIDTH;
        PIPEHEIGHT = listPipeHeight[int(indexPipeHeight)];
        if((indexPipeHeight + 2) >= 5)
            indexPipeHeight -= 3;
        else
            indexPipeHeight += 2;

        SCORE += 0.5;
    }
    xPos += xVelocity;
    setSource(0, 373 - PIPEHEIGHT, PIPEWIDTH, PIPEHEIGHT);
    setDest(xPos, 0, PIPEWIDTH, PIPEHEIGHT);
}

void Pipe::PipeMoveDown()
{
    if(xPos < -PIPEWIDTH)
    {
        xPos = 320 + PIPEWIDTH;
        PIPEHEIGHT = listPipeHeight[int(indexPipeHeight)];
        if((indexPipeHeight +2) >= 5)
            indexPipeHeight -= 3;
        else
            indexPipeHeight += 2;

        SCORE += 0.5;
    }
    xPos += xVelocity ;
    setSource(0, 0, PIPEWIDTH, 485 - PIPEDISTANCE - PIPEHEIGHT);
    setDest(xPos, PIPEHEIGHT + PIPEDISTANCE, PIPEWIDTH,485 - PIPEDISTANCE - PIPEHEIGHT);
}

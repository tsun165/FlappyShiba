#include "Pipe.h"

void Pipe::Intialize()
{
    xVelocity = -3;  // Pipe chậm hơn, đồng bộ với tốc độ rơi mới
    score = 0;
}

void Pipe::render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Pipe::PipeMoveUp()
{
    if(xPos < -PIPEWIDTH)
    {
        xPos = 320 + PIPEWIDTH;
        pipeHeight = listPipeHeight[int(indexPipeHeight)];
        if((indexPipeHeight + 2) >= 5)
            indexPipeHeight -= 3;
        else
            indexPipeHeight += 2;

        score += 0.5;
    }
    xPos += xVelocity;
    setSrc(0, 373 - pipeHeight, PIPEWIDTH, pipeHeight);
    setDest(xPos, 0, PIPEWIDTH, pipeHeight);
}

void Pipe::PipeMoveDown()
{
    if(xPos < -PIPEWIDTH)
    {
        xPos = 320 + PIPEWIDTH;
        pipeHeight = listPipeHeight[int(indexPipeHeight)];
        if((indexPipeHeight +2) >= 5)
            indexPipeHeight -= 3;
        else
            indexPipeHeight += 2;

        score += 0.5;
    }
    xPos += xVelocity ;
    setSrc(0, 0, PIPEWIDTH, 485 - PIPEDISTANCE - pipeHeight);
    setDest(xPos, pipeHeight + PIPEDISTANCE, PIPEWIDTH,485 - PIPEDISTANCE - pipeHeight);
}

#include "Pipe.h"



void Pipe::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}
void Pipe::PipeMoveUp()
{
    if(Xpos < -65)
    {
        Xpos = 385;
        SCORE += 0.5;
    }
    Xpos += Xvelocity;
    setSource(0, 253, PIPEWIDTH, PIPEHEIGHT);
    setDest(Xpos, 0, PIPEWIDTH, PIPEHEIGHT);
}
void Pipe::PipeMoveDown()
{
    if(Xpos < -PIPEWIDTH)
    {
        Xpos = 385;
        SCORE += 0.5;
    }
    Xpos += Xvelocity;
    setSource(0, 0, PIPEWIDTH, PIPEHEIGHT);
    setDest(Xpos, 485- PIPEHEIGHT, PIPEWIDTH, PIPEHEIGHT);
}

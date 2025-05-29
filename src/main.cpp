#include "GameLoop.h"

GameLoop* g = new GameLoop();

int main(int argc, char* argv[])
{
    g->Intialize();

    while(g->getGameState())
    {
        switch(g->state)
        {
            case 1:
                g->RenderStart();
                break;
            case 2:
                g->RenderPlay();
                break;
            case 3:
                g->RenderEnd();
                break;
        }
        g->Event();
    }
    g->Clear();


    return 0;
}

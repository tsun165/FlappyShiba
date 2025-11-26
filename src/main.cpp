#include "GameLoop.h"

int main(int argc, char* argv[])
{
    GameLoop* g = new GameLoop();
    g->Intialize();

    while(g->getGameState())
    {
        g->HandleEvents();
        g->Update();
        
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
    }
    g->Clear();
    delete g;  // Clean up allocated memory

    return 0;
}

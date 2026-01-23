#include "GameLoop.h"

int main(int argc, char* argv[])
{
    GameLoop* g = new GameLoop();
    g->initalize();

    while(g->getGameState())
    {
        g->handleEvents();
        g->update();
        
        switch(g->getState())
        {
            case 1:
                g->renderStart();
                break;
            case 2:
                g->renderPlay();
                break;
            case 3:
                g->renderEnd();
                break;
            case 4:
                g->renderPause();
                break;
        }
    }
    g->clear();
    delete g;  // Clean up allocated memory

    return 0;
}

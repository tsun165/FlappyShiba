#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    // Source Dimension:
    p.setSource(0,0,50,35);
    //Destination Dimension
    p.setDest(10,20,50,35);

}

bool GameLoop::getGameState()
{
    return GameState;
}

void GameLoop::Intialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("FlappyShiba",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            cout << "Succeeded" << endl;
            GameState = true;
            p.CreateTexture("..\\..\\res\\image\\shiba.png", renderer, p.getTexture());
            background = TextureManager::Texture("..\\..\\res\\image\\background.png",renderer);

        }
        else
        {
            cout << "Not succeeded" << endl;
        }

    }
    else
    {
        cout << "window not created" << endl;
    }
}

void GameLoop::Event()
{
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT)
    {
        GameState = false;
    }
    if(event1.type == SDL_KEYDOWN)
    {
        if(event1.key.keysym.sym == SDLK_UP)
        {
            cout << "Pressed" << endl;
        }

    }

}

void GameLoop::Update()
{

}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, NULL);
    p.Render(renderer, p.getTexture(), p.getSrc(), p.getDest());
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}



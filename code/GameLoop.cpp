#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;

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
            p.CreateTexture("..\\..\\res\\image\\shiba.png", renderer);
            b.CreateTexture("..\\..\\res\\image\\background.png",renderer);

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

            p.Jump();
            p.Jump();
            p.Jump();
            p.Jump();

    }
    else
    {
        p.Gravity();
        SDL_Delay(1);
    }

}

void GameLoop::Update()
{

}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);

    b.Render(renderer);
    p.Render(renderer);

    SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}



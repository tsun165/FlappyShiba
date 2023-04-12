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
            GameState = true;
            p.CreateTexture("..\\..\\res\\image\\shiba.png", renderer);
            b.CreateTexture("..\\..\\res\\image\\background.png", renderer);
            piUp.CreateTexture("..\\..\\res\\image\\pipeUp.png", renderer);
            piDown.CreateTexture("..\\..\\res\\image\\pipeDown.png", renderer);

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

    }
    else
    {
        p.Gravity();
        SDL_Delay(1);
    }
    piUp.PipeMoveUp();
    piDown.PipeMoveDown();
    if((p.Xpos + p.PLAYERWIDTH) > piUp.Xpos && p.Xpos <(piUp.Xpos + piUp.PIPEWIDTH))
    {
        if(p.Ypos < piUp.PIPEHEIGHT)
        {
            GameState = false;
            SCORE = piUp.SCORE + piDown.SCORE;
            cout << SCORE;
        }
    }
    if((p.Xpos + p.PLAYERWIDTH) > piDown.Xpos && p.Xpos <(piDown.Xpos + piDown.PIPEWIDTH))
    {
        if((p.Ypos + p.PLAYERHEIGHT) > (485 - piDown.PIPEHEIGHT))
        {
            GameState = false;
            SCORE = piUp.SCORE + piDown.SCORE;
            cout << SCORE;
        }
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
    piUp.Render(renderer);
    piDown.Render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(25);
}

void GameLoop::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}



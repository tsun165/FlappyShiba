#include "GameLoop.h"


GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;

    GameState = true;
    state = 1;

    p.Intialize();

    pi1Up.Intialize();
    pi1Down.Intialize();
    pi1Up.xPos = pi1Down.xPos = 320;
    pi1Up.PIPEHEIGHT = pi1Down.PIPEHEIGHT = pi1Up.listPipeHeight[0];
    pi1Up.indexPipeHeight = pi1Down.indexPipeHeight = 2;

    pi2Up.Intialize();
    pi2Down.Intialize();
    pi2Up.xPos = pi2Down.xPos = 320 + 210;
    pi2Up.PIPEHEIGHT = pi2Down.PIPEHEIGHT = pi2Up.listPipeHeight[0];
    pi2Up.indexPipeHeight = pi2Down.indexPipeHeight = 3;


}

bool GameLoop::getGameState()
{

    return GameState;
}

void GameLoop::Intialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();
    font = TTF_OpenFont("..\\res\\data\\Flappy-Bird.TTF",25);
    if(font == NULL)
    {
        throw 1;
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << Mix_GetError() << endl;
        throw 1; // EXIT THE PROGRAM
    }
    snd.Intialize();

    window = SDL_CreateWindow("FlappyShiba",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

    if(window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer)
        {
            GameState = true;

            b.CreateTexture("..\\res\\image\\background.png", renderer);

            p.CreateTexture("..\\res\\image\\shiba.png", renderer);

            pi1Up.CreateTexture("..\\res\\image\\pipeUp.png", renderer);
            pi1Down.CreateTexture("..\\res\\image\\pipeDown.png", renderer);

            pi2Up.CreateTexture("..\\res\\image\\pipeUp.png", renderer);
            pi2Down.CreateTexture("..\\res\\image\\pipeDown.png", renderer);

            menuStart.Stay(225, 204);
            menuStart.CreateTexture("..\\res\\image\\message.png", renderer);


            menuEnd.Stay(225, 188);
            menuEnd.CreateTexture("..\\res\\image\\gameOver.png", renderer);



        }
        else
        {
            cout << "render not created" << endl;
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
    if(event1.type == SDL_KEYDOWN && event1.key.keysym.sym == SDLK_SPACE && state == 1)
    {
            State(2);

    }

    if(state == 2)
    {
        if(event1.type == SDL_KEYDOWN && event1.key.keysym.sym == SDLK_SPACE)
        {
            p.Jump();
            snd.PlayBreath();
        }
        else
        {
            p.Gravity();
            SDL_Delay(1);
        }

        pi1Up.PipeMoveUp();
        pi1Down.PipeMoveDown();
        pi2Up.PipeMoveUp();
        pi2Down.PipeMoveDown();

        if((p.xPos + p.PLAYERWIDTH) > pi1Up.xPos && p.xPos <(pi1Up.xPos + pi1Up.PIPEWIDTH))
        {
            if(p.yPos < pi1Up.PIPEHEIGHT || (p.yPos + p.PLAYERHEIGHT) > (pi1Down.PIPEHEIGHT + pi1Down.PIPEDISTANCE))
            {
                snd.PlayBonk();
                SCORE = pi1Up.SCORE + pi1Down.SCORE + pi2Up.SCORE + pi2Down.SCORE;
                cout << SCORE << endl;
                State(3);
            }
        }


        if((p.xPos + p.PLAYERWIDTH) > pi2Up.xPos && p.xPos <(pi2Up.xPos + pi2Up.PIPEWIDTH))
        {
            if(p.yPos < pi2Up.PIPEHEIGHT || (p.yPos + p.PLAYERHEIGHT) > (pi2Down.PIPEHEIGHT + pi2Down.PIPEDISTANCE))
            {
                snd.PlayBonk();
                SCORE = pi1Up.SCORE + pi1Down.SCORE + pi2Up.SCORE + pi2Down.SCORE;
                cout << SCORE  << endl;
                State(3);
            }
        }
    }

    if(event1.type == SDL_KEYDOWN && event1.key.keysym.sym == SDLK_SPACE && state == 3)
    {
        State(1);
    }



}


void GameLoop::RenderPlay()
{
    SDL_RenderClear(renderer);

    b.Render(renderer);
    p.Render(renderer);

    pi1Up.Render(renderer);
    pi1Down.Render(renderer);

    pi2Up.Render(renderer);
    pi2Down.Render(renderer);

    SCORE = pi1Up.SCORE + pi1Down.SCORE + pi2Up.SCORE + pi2Down.SCORE;
    SDL_Color fg = {255, 255, 255, 255};
    SDL_Surface* fontsf = TTF_RenderText_Solid(font, to_string(SCORE).c_str(), fg);
    SDL_Rect destPlaying = {170, 30, fontsf->w, fontsf->h};
    SDL_Texture* fonttex = SDL_CreateTextureFromSurface(renderer, fontsf);
    SDL_RenderCopy(renderer, fonttex, NULL, &destPlaying);



    SDL_RenderPresent(renderer);

    SDL_Delay(25);
}
void GameLoop::RenderStart()
{

    SDL_RenderClear(renderer);

    b.Render(renderer);
    p.Render(renderer);

    menuStart.Render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(25);

}
void GameLoop::RenderEnd()
{
    SDL_RenderClear(renderer);

    b.Render(renderer);
    p.Render(renderer);

    pi1Up.Render(renderer);
    pi1Down.Render(renderer);

    pi2Up.Render(renderer);
    pi2Down.Render(renderer);

    menuEnd.Render(renderer);

    SCORE = pi1Up.SCORE + pi1Down.SCORE + pi2Up.SCORE + pi2Down.SCORE;
    SDL_Color fg = {255, 255, 255, 255};
    SDL_Surface* fontsf = TTF_RenderText_Solid(font, to_string(SCORE).c_str(), fg);
    SDL_Rect destEnd = {235, 245, fontsf->w, fontsf->h};
    SDL_Texture* fonttex = SDL_CreateTextureFromSurface(renderer, fontsf);
    SDL_RenderCopy(renderer, fonttex, NULL, &destEnd);

    SDL_RenderPresent(renderer);

    SDL_Delay(25);

}

void GameLoop::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}
void GameLoop::State(const short n)
{
    state = n;
    if(state == 1)
    {
        p.Intialize();

        pi1Up.Intialize();
        pi1Down.Intialize();
        pi1Up.xPos = pi1Down.xPos = 320;
        pi1Up.PIPEHEIGHT = pi1Down.PIPEHEIGHT = pi1Up.listPipeHeight[0];
        pi1Up.indexPipeHeight = pi1Down.indexPipeHeight = 2;

        pi2Up.Intialize();
        pi2Down.Intialize();
        pi2Up.xPos = pi2Down.xPos = 320 + 210;
        pi2Up.PIPEHEIGHT = pi2Down.PIPEHEIGHT = pi2Up.listPipeHeight[0];
        pi2Up.indexPipeHeight = pi2Down.indexPipeHeight = 3;
    }
}





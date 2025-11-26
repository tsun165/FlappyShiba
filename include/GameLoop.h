#pragma once


#include <iostream>

#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Pipe.h"
#include "Sound.h"
#include "Menu.h"
#include <SDL_ttf.h>

using namespace std;
class GameLoop
{
private:
    Player p;
    Background b;
    Pipe pi1Up, pi1Down, pi2Up, pi2Down;
    Sound snd;
    Menu menuStart, menuEnd;
    TTF_Font* font ;


    //state 1 Start
    //state 2 Playing
    //state 3 End


    const int HEIGHT = 485;
    const int WIDTH = 350;
    const int TARGET_FPS = 60;
    const int FRAME_DELAY = 1000 / TARGET_FPS;
    
    int SCORE = 0;
    Uint32 frameStart;
    int frameTime;

    bool GameState;

    SDL_Event event1;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;

public:

    int state ;
    GameLoop();
    bool getGameState();
    void Intialize();
    void HandleEvents();
    void Update();
    void RenderPlay();
    void RenderStart();
    void RenderEnd();
    void Clear();
    void State(const short n);
    void ResetGame();
    int CalculateScore();


};

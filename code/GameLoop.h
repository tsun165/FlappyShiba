#pragma once


#include <iostream>

#include "TextureManager.h"
#include "Player.h"
#include "Background.h"

using namespace std;
class GameLoop
{
private:
    Player p;
    Background b;
    const int HEIGHT = 485;
    const int WIDTH = 350;
    bool GameState;
    SDL_Event event1;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;

public:
    GameLoop();
    bool getGameState();
    void Update();
    void Intialize();
    void Event();
    void Render();
    void Clear();

};

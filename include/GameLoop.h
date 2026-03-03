#pragma once

#include <iostream>
#include <string>
#include <SDL_ttf.h>

#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Pipe.h"
#include "Sound.h"
#include "Menu.h"


using namespace std;
class GameLoop {
public:
    //Constructor
    GameLoop();

    // Main game loop API
    bool getGameState();
    void initalize();
    void handleEvents();
    void update();

    // Rendering
    void renderPlay();
    void renderStart();
    void renderEnd();
    void renderPause();

    // State control
    int getState();
    void clear();
    void setState(const short n);
    void resetGame();


private:
    // Helpers
    int calculateScore();
    bool checkPipeCollision(Pipe& pipeUp, Pipe& pipeDown);

    // Constants
    const int HEIGHT = 485;
    const int WIDTH = 350;
    const int TARGET_FPS = 60;
    const int FRAME_DELAY = 1000 / TARGET_FPS;

    // Game state data
    Player p;
    Background b;
    Pipe pi1Up, pi1Down, pi2Up, pi2Down;
    Sound snd;

    Menu menuStart, menuEnd;
    Menu menuPauseTab;
    Menu btnPauseIcon;
    Menu btnResume;
    Menu btnReplay;      // replay button in pause menu
    Menu btnReplayEnd;   // replay button on game-over board
    Menu btnSound;

    TTF_Font* font;
    
    int score = 0;
    bool gameState, sound;
    int state = 1;

    //state 1 Start
    //state 2 Playing
    //state 3 End
    //state 4 Pause

    Uint32 frameStart;
    int frameTime;

    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* player;
    SDL_Texture* background;

};

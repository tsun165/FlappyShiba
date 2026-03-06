#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>

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
    void renderStart();
    void renderPlay();
    void renderPause();
    void renderEnd();

    // State control
    int getState();
    void clear();
    void setState(const short n);
    void resetGame();


private:
    // Helpers
    int calculateScore();
    bool checkPipeCollision(Pipe& pipe);
    void updateScoreForPipe(int pipeIndex);
    // Vẽ điểm bằng ảnh số
    void renderScore(int value, int centerX, int y, bool useLarge);
    //Vẽ huy chương
    void renderMedal(int score);

    // Constants
    static const int SCREEN_HEIGHT = 485;
    static const int SCREEN_WIDTH = 350;
    static const int TARGET_FPS = 60;
    static const int FRAME_DELAY = 1000 / TARGET_FPS;

    // Game state data
    Player p;
    Background b, bNight;
    Pipe pipes[2];
    Sound snd;

    Menu menuStart, menuEnd;
    Menu menuPauseTab;
    Menu iconPause;
    Menu iconResume;
    Menu iconSoundOn, iconSoundOff;

    TTF_Font* font;

    // Ảnh số 0-9: small (khi chơi/pause), large (game over)
    SDL_Texture* digitSmall[10];
    SDL_Texture* digitLarge[10];
    static const int DIGIT_W_SMALL = 16;   // chiều rộng 1 số small (chỉnh theo ảnh của bạn)
    static const int DIGIT_H_SMALL = 24;   // chiều cao
    static const int DIGIT_W_LARGE = 32;   // large
    static const int DIGIT_H_LARGE = 48;
    
    int score;
    bool canScore[2];
    bool gameState, sound;
    int state;

    //state 1 Start
    //state 2 Playing
    //state 3 End
    //state 4 Pause

    Uint32 frameStart;
    int frameTime;

    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Medal cho màn game over
    SDL_Texture* medalBronze;
    SDL_Texture* medalSilver;
    SDL_Texture* medalGold;

};

#include "GameLoop.h"

// Constructor
GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    font = nullptr;
    for (int i = 0; i < 10; i++) {
        digitSmall[i] = nullptr;
        digitLarge[i] = nullptr;
    }

    score = 0;
    gameState = true;
    sound = true;
    state = 1;
    frameStart = 0;
    frameTime = 0;
    
    srand(static_cast<unsigned>(time(NULL)));

    resetGame();
}

// Main game loop API
bool GameLoop::getGameState()
{
    return gameState;
}

void GameLoop::initalize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();
    font = TTF_OpenFont("asset\\font\\Flappy-Bird.TTF", 25);
    if (font == NULL)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        gameState = false;
        return;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("Failed to open audio: %s", Mix_GetError());
        gameState = false;
        return;
    }
    snd.intialize();

    window = SDL_CreateWindow("FlappyShiba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            gameState = true;

            b.setTexture("asset\\image\\background.png", renderer);
            bNight.setTexture("asset\\image\\background-night.png", renderer);

            p.setTexture("asset\\image\\shiba.png", renderer);

            pipes[0].setTexture("asset\\image\\pipeUp.png", "asset\\image\\pipeDown.png", renderer);
            pipes[0].initialize();
            pipes[1].setTexture("asset\\image\\pipeUp.png", "asset\\image\\pipeDown.png", renderer);
            pipes[1].initialize();

            // Start menu banner
            menuStart.stay(225, 204);
            menuStart.setTexture("asset\\image\\message.png", renderer);    

            // Game over banner
            menuEnd.stay(225, 188);
            menuEnd.setTexture("asset\\image\\gameOver.png", renderer);

            // Pause tab overlay
            menuPauseTab.stay(250, 200);
            menuPauseTab.setTexture("asset\\image\\pauseTab.png", renderer);

            // Pause icon (top-right during play)
            iconPause.setTexture("asset\\image\\pause.png", renderer);
            iconPause.setSrc(0, 0, 40, 40);
            iconPause.setDest(SCREEN_WIDTH - 50, 10, 40, 40);

            // Resume icon
            iconResume.setTexture("asset\\image\\resume.png", renderer);
            iconResume.setSrc(0, 0, 40, 40);
            iconResume.setDest(SCREEN_WIDTH - 50, 10, 40, 40);

            // Sound icon
            iconSoundOn.setTexture("asset\\image\\sound.png", renderer);
            iconSoundOn.setSrc(0, 0, 32, 24);
            iconSoundOn.setDest(115, 205, 32, 24);
            iconSoundOff.setTexture("asset\\image\\sound.png", renderer);
            iconSoundOff.setSrc(0, 24, 32, 24);
            iconSoundOff.setDest(115, 205, 32, 24);

            // Load ảnh số 0-9 (small và large)
            for (int i = 0; i < 10; i++) {
                string pathSmall = "asset\\number\\small\\" + to_string(i) + ".png";
                string pathLarge = "asset\\number\\large\\" + to_string(i) + ".png";
                digitSmall[i] = TextureManager::Texture(pathSmall.c_str(), renderer);
                digitLarge[i] = TextureManager::Texture(pathLarge.c_str(), renderer);
            }

            //Medal
            medalBronze = TextureManager::Texture("asset\\medal\\honor.png", renderer);
            medalSilver = TextureManager::Texture("asset\\medal\\silver.png", renderer);
            medalGold = TextureManager::Texture("asset\\medal\\gold.png", renderer);
        }
        else
        {
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            gameState = false;
        }

    }
    else
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        gameState = false;
    }
}

void GameLoop::handleEvents()
{
    SDL_PollEvent(&event);

    // Handle quit event
    if (event.type == SDL_QUIT)
    {
        gameState = false;
    }

    if (event.type == SDL_KEYDOWN)
    {
        // Space: start / jump / restart
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            if (state == 1)
            {
                setState(2);  // Start game
            }
            else if (state == 2)
            {
                p.Jump();
                if (sound == true)
                {
                    snd.playBreath();
                }
                
            }
            else if (state == 3)
            {
                setState(1);  // Restart game from start screen
            }
        }

        // ESC: toggle pause when playing or paused
        if (event.key.keysym.sym == SDLK_LCTRL)
        {
            if (state == 2)
            {
                state = 4; // Pause
            }
            else if (state == 4)
            {
                state = 2; // Resume

                //Xử lý đếm
            }
        }
        if (state == 4 && event.key.keysym.sym == SDLK_s) { sound = !sound;}
    }

    //// Mouse input for menu buttons
    //if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    //{
    //    int mx = event.button.x;
    //    int my = event.button.y;

    //    if (state == 4)
    //    {
    //        // Pause menu: resume / replay / sound
    //        if (iconResume.isClicked(mx, my))
    //        {
    //            state = 2;
    //        }
    //        else if (iconReplay.isClicked(mx, my))
    //        {
    //            resetGame();
    //            state = 2;
    //        }
    //        else if (iconSound.isClicked(mx, my))
    //        {
    //            sound = !sound;
    //            Mix_Volume(-1, sound ? MIX_MAX_VOLUME : 0);
    //        }
    //    }
    //}
}

void GameLoop::update()
{
    if (state == 2)
    {
        p.Update();

        for (int i = 0; i < 2; ++i)
        {
            pipes[i].update();

            if (pipes[i].isOutOfScreen())
            {
                int other = 1 - i;
                int startX = pipes[other].getX() + 210; // khoảng cách giữa 2 cặp
                pipes[i].reset(startX);
                canScore[i] = true; // cho phép cộng điểm lại sau khi respawn
            }

            updateScoreForPipe(i);
        }

        if (checkPipeCollision(pipes[0]) || checkPipeCollision(pipes[1]))
        {
            if (sound == true)
            {
                snd.playBonk();
            }
            setState(3);
        }

        if (p.yPos <= 0 || p.yPos >= SCREEN_HEIGHT)
        {
            if (sound == true)
            {
                snd.playBonk();
            }
            setState(3);
        }
    }
}


// Rendering
void GameLoop::renderStart()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    b.render(renderer);
    p.render(renderer);
    menuStart.render(renderer);

    SDL_RenderPresent(renderer);

    // Cap frame rate
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void GameLoop::renderPlay()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    score = calculateScore();
    if (score % 20 < 10) 
    {
        b.render(renderer);
    }
    else {
        bNight.render(renderer);
    }

    p.render(renderer);
    pipes[0].render(renderer);
    pipes[1].render(renderer);

    
    renderScore(score, SCREEN_WIDTH / 2, 30, true);

    iconPause.render(renderer);
    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void GameLoop::renderPause()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    // Draw current game state (background, pipes, player)
    score = calculateScore();
    if (score % 20 < 10)
    {
        b.render(renderer);
    }
    else {
        bNight.render(renderer);
    }

    p.render(renderer);

    pipes[0].render(renderer);
    pipes[1].render(renderer);

    // Pause overlay and buttons
    menuPauseTab.render(renderer);
    iconResume.render(renderer);
    if (sound == true) 
    {
        iconSoundOn.render(renderer);
    }
    else {
        iconSoundOff.render(renderer);
    }

    int bestScore = 0;
    {
        std::ifstream fin("asset\\data\\bestScore.txt");
        if (fin.good()) {
            fin >> bestScore;
        }
        fin.close();
    }

    renderScore(score, 265, 200, false);
    renderScore(bestScore, 265, 275, false);

    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void GameLoop::renderEnd()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    score = calculateScore();
    if (score % 20 < 10) 
    {
        b.render(renderer);
    }
    else {
        bNight.render(renderer);
    }

    p.render(renderer);

    pipes[0].render(renderer);
    pipes[1].render(renderer);

    menuEnd.render(renderer);

    int bestScore = 0;
    {
        std::ifstream fin("asset\\data\\bestScore.txt");
        if (fin.good()) {
            fin >> bestScore;
        }
        fin.close();
    }

    if (score > bestScore) {
        bestScore = score;
        std::ofstream fout("asset\\data\\bestScore.txt", std::ios::trunc);
        fout << bestScore;
        fout.close();
    }

    renderScore(score, 245, 245, false);
    renderScore(bestScore, 245, 290, false);
    renderMedal(score);

    // Replay button on game over screen
    //iconReplayEnd.render(renderer);

    SDL_RenderPresent(renderer);

    // Cap frame rate
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}



// State control
int GameLoop::getState()
{
    return state;
}

void GameLoop::clear()
{
    for (int i = 0; i < 10; i++) {
        if (digitSmall[i]) { SDL_DestroyTexture(digitSmall[i]); digitSmall[i] = nullptr; }
        if (digitLarge[i]) { SDL_DestroyTexture(digitLarge[i]); digitLarge[i] = nullptr; }
    }
    if (medalBronze) { SDL_DestroyTexture(medalBronze); medalBronze = nullptr; }
    if (medalSilver) { SDL_DestroyTexture(medalSilver); medalSilver = nullptr; }
    if (medalGold) { SDL_DestroyTexture(medalGold);   medalGold = nullptr; }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void GameLoop::setState(const short n)
{
    state = n;
    if (state == 1)
    {
        resetGame();
    }
}

void GameLoop::resetGame()
{
    p.Intialize();

    pipes[0].initialize();
    pipes[0].reset(320);

    pipes[1].initialize();
    pipes[1].reset(320 + 210);

    score = 0;
    canScore[0] = true;
    canScore[1] = true;
}


// Helpers
int GameLoop::calculateScore()
{
    // Each pipe pair contributes 1 point when passed
    // Since we have 2 pairs (pi1 and pi2), and each pipe adds 0.5
    return score;
}

bool GameLoop::checkPipeCollision(Pipe& pipe)
{
    int pipeX = pipe.getX();
    int pipeRight = pipeX + Pipe::PIPEWIDTH;
    int gapTop = pipe.getPipeHeight();
    int gapBottom = gapTop + Pipe::GAP;

    // Check trùng theo trục X
    if ((p.xPos + p.PLAYERWIDTH) > pipeX && p.xPos < pipeRight)
    {
        // Đụng ống trên
        if (p.yPos < gapTop)
            return true;

        // Đụng ống dưới
        if ((p.yPos + p.PLAYERHEIGHT) > gapBottom)
            return true;
    }
    return false;
}

void GameLoop::renderScore(int value, int centerX, int y, bool useLarge)
{
    SDL_Texture** digits = useLarge ? digitLarge : digitSmall;
    int w = useLarge ? DIGIT_W_LARGE : DIGIT_W_SMALL;
    int h = useLarge ? DIGIT_H_LARGE : DIGIT_H_SMALL;

    string s = to_string(value);
    int totalW = (int)s.length() * w;
    int startX = centerX - totalW / 2;

    for (size_t i = 0; i < s.length(); i++) {
        int idx = s[i] - '0';
        if (idx < 0 || idx > 9 || digits[idx] == nullptr) continue;

        SDL_Rect dest = { startX + (int)i * w, y, w, h };
        SDL_RenderCopy(renderer, digits[idx], NULL, &dest);
    }
}

void GameLoop::renderMedal(int score)
{
    SDL_Texture* medal = nullptr;
    if (score <= 2) {
        medal = medalBronze;
    }
    else if (score <= 4) {
        medal = medalSilver;
    }
    else {
        medal = medalGold;
    }

    SDL_Rect dest = { 85, 250, 48, 48 };
    SDL_RenderCopy(renderer, medal, NULL, &dest);
}

void GameLoop::updateScoreForPipe(int pipeIndex)
{
    Pipe& pipe = pipes[pipeIndex];
    if (!canScore[pipeIndex]) return;

    int pipeRight = pipe.getX() + Pipe::PIPEWIDTH;

    // Cộng đúng 1 lần khi player vượt qua mép phải cặp ống
    if (p.xPos > pipeRight)
    {
        score++;
        if (sound == true)
        {
            snd.playPlus();
        }
        canScore[pipeIndex] = false;
    }
}



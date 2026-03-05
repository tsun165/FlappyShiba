#include "GameLoop.h"

// Constructor
GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    font = nullptr;

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
    snd.Intialize();

    window = SDL_CreateWindow("FlappyShiba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            gameState = true;

            b.setTexture("asset\\image\\background.png", renderer);

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
            btnPauseIcon.setTexture("asset\\image\\pause.png", renderer);
            btnPauseIcon.setSrc(0, 0, 40, 40);
            btnPauseIcon.setDest(SCREEN_WIDTH - 50, 10, 40, 40);

            // Resume button
            btnResume.setTexture("asset\\image\\resume.png", renderer);
            btnResume.setSrc(0, 0, 40, 40);
            btnResume.setDest(105, 190, 40, 40);

            // Replay button
            btnReplay.setTexture("asset\\image\\replay.png", renderer);
            btnReplay.setSrc(0, 0, 40, 40);
            btnReplay.setDest(155, 190, 40, 40);

            // Replay button for game-over screen (center-bottom of board)
            btnReplayEnd.setTexture("asset\\image\\replay.png", renderer);
            btnReplayEnd.setSrc(0, 0, 40, 40);

            // gameOver board is at (62,140) size (225x188)
            // place button centered horizontally, near bottom with small margin
            int endBtnX = 62 + (225 - 40) / 2;
            int endBtnY = 140 + 188 - 40 - 10;
            btnReplayEnd.setDest(endBtnX, endBtnY, 40, 40);

            // Sound toggle button
            btnSound.setTexture("asset\\image\\sound.png", renderer);
            btnSound.setSrc(0, 0, 40, 40);
            btnSound.setDest(205, 190, 40, 40);
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
                snd.PlayBreath();
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
    }

    // Mouse input for menu buttons
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int mx = event.button.x;
        int my = event.button.y;

        // Pause icon during play
        if (state == 2)
        {
            if (btnPauseIcon.isClicked(mx, my))
            {
                state = 4; // Pause
            }
        }
        else if (state == 4)
        {
            // Pause menu: resume / replay / sound
            if (btnResume.isClicked(mx, my))
            {
                state = 2;
            }
            else if (btnReplay.isClicked(mx, my))
            {
                resetGame();
                state = 2;
            }
            else if (btnSound.isClicked(mx, my))
            {
                sound = !sound;
                Mix_Volume(-1, sound ? MIX_MAX_VOLUME : 0);
            }
        }
        else if (state == 3)
        {
            // Game over: allow replay by clicking replay button on board
            if (btnReplayEnd.isClicked(mx, my))
            {
                resetGame();
                state = 2;
            }
        }
    }
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
            snd.PlayBonk();
            SDL_Log("Game Over! Score: %d", score);
            setState(3);
        }

        if (p.yPos <= 0 || p.yPos >= 450)
        {
            snd.PlayBonk();
            SDL_Log("Game Over! Score: %d", score);
            setState(3);
        }
    }
}


// Rendering
void GameLoop::renderPlay()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    b.render(renderer);
    p.render(renderer);

    pipes[0].render(renderer);
    pipes[1].render(renderer);

    score = calculateScore();
    SDL_Color fg = { 255, 255, 255, 255 };
    SDL_Surface* fontsf = TTF_RenderText_Solid(font, to_string(score).c_str(), fg);
    SDL_Rect destPlaying = { 170, 30, fontsf->w, fontsf->h };
    SDL_Texture* fonttex = SDL_CreateTextureFromSurface(renderer, fontsf);
    SDL_RenderCopy(renderer, fonttex, NULL, &destPlaying);

    // Clean up to prevent memory leak
    SDL_DestroyTexture(fonttex);
    SDL_FreeSurface(fontsf);

    SDL_RenderPresent(renderer);

    // Cap frame rate
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

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

void GameLoop::renderEnd()
{
    frameStart = SDL_GetTicks();

    SDL_RenderClear(renderer);

    b.render(renderer);
    p.render(renderer);

    pipes[0].render(renderer);
    pipes[1].render(renderer);

    menuEnd.render(renderer);

    score = calculateScore();
    SDL_Color fg = { 255, 255, 255, 255 };
    SDL_Surface* fontsf = TTF_RenderText_Solid(font, to_string(score).c_str(), fg);
    SDL_Rect destEnd = { 235, 245, fontsf->w, fontsf->h };
    SDL_Texture* fonttex = SDL_CreateTextureFromSurface(renderer, fontsf);
    SDL_RenderCopy(renderer, fonttex, NULL, &destEnd);

    // Clean up to prevent memory leak
    SDL_DestroyTexture(fonttex);
    SDL_FreeSurface(fontsf);

    // Replay button on game over screen
    btnReplayEnd.render(renderer);

    SDL_RenderPresent(renderer);

    // Cap frame rate
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
    b.render(renderer);
    p.render(renderer);

    pipes[0].render(renderer);
    pipes[1].render(renderer);

    // Draw score
    score = calculateScore();
    SDL_Color fg = { 255, 255, 255, 255 };
    SDL_Surface* fontsf = TTF_RenderText_Solid(font, to_string(score).c_str(), fg);
    SDL_Rect destPlaying = { 170, 30, fontsf->w, fontsf->h };
    SDL_Texture* fonttex = SDL_CreateTextureFromSurface(renderer, fontsf);
    SDL_RenderCopy(renderer, fonttex, NULL, &destPlaying);

    SDL_DestroyTexture(fonttex);
    SDL_FreeSurface(fontsf);

    // Pause overlay and buttons
    menuPauseTab.render(renderer);
    btnResume.render(renderer);
    btnReplay.render(renderer);
    btnSound.render(renderer);

    SDL_RenderPresent(renderer);

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

void GameLoop::updateScoreForPipe(int pipeIndex)
{
    Pipe& pipe = pipes[pipeIndex];
    if (!canScore[pipeIndex]) return;

    int pipeRight = pipe.getX() + Pipe::PIPEWIDTH;

    // Cộng đúng 1 lần khi player vượt qua mép phải cặp ống
    if (p.xPos > pipeRight)
    {
        score++;
        canScore[pipeIndex] = false;
    }
}



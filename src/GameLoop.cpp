#include "GameLoop.h"
#include <string>

// Constructor
GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    gameState = true;
    state = 1;
    
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

    window = SDL_CreateWindow("FlappyShiba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

    if (window)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            gameState = true;

            b.CreateTexture("asset\\image\\background.png", renderer);

            p.CreateTexture("asset\\image\\shiba.png", renderer);

            pi1Up.CreateTexture("asset\\image\\pipeUp.png", renderer);
            pi1Down.CreateTexture("asset\\image\\pipeDown.png", renderer);

            pi2Up.CreateTexture("asset\\image\\pipeUp.png", renderer);
            pi2Down.CreateTexture("asset\\image\\pipeDown.png", renderer);

            // Start menu banner
            menuStart.Stay(225, 204);
            menuStart.CreateTexture("asset\\image\\message.png", renderer);

            // Game over banner
            menuEnd.Stay(225, 188);
            menuEnd.CreateTexture("asset\\image\\gameOver.png", renderer);

            // Pause tab overlay
            menuPauseTab.Stay(250, 200);
            menuPauseTab.CreateTexture("asset\\image\\pauseTab.png", renderer);

            // Pause icon (top-right during play)
            btnPauseIcon.CreateTexture("asset\\image\\pause.png", renderer);
            btnPauseIcon.setSource(0, 0, 40, 40);
            btnPauseIcon.setDest(WIDTH - 50, 10, 40, 40);

            // Resume button
            btnResume.CreateTexture("asset\\image\\resume.png", renderer);
            btnResume.setSource(0, 0, 40, 40);
            btnResume.setDest(105, 190, 40, 40);

            // Replay button
            btnReplay.CreateTexture("asset\\image\\replay.png", renderer);
            btnReplay.setSource(0, 0, 40, 40);
            btnReplay.setDest(155, 190, 40, 40);

            // Replay button for game-over screen (center-bottom of board)
            btnReplayEnd.CreateTexture("asset\\image\\replay.png", renderer);
            btnReplayEnd.setSource(0, 0, 40, 40);
            // gameOver board is at (62,140) size (225x188)
            // place button centered horizontally, near bottom with small margin
            int endBtnX = 62 + (225 - 40) / 2;
            int endBtnY = 140 + 188 - 40 - 10;
            btnReplayEnd.setDest(endBtnX, endBtnY, 40, 40);

            // Sound toggle button
            btnSound.CreateTexture("asset\\image\\sound.png", renderer);
            btnSound.setSource(0, 0, 40, 40);
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
    SDL_PollEvent(&event1);

    // Handle quit event
    if (event1.type == SDL_QUIT)
    {
        gameState = false;
    }

    if (event1.type == SDL_KEYDOWN)
    {
        // Space: start / jump / restart
        if (event1.key.keysym.sym == SDLK_SPACE)
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
        if (event1.key.keysym.sym == SDLK_ESCAPE)
        {
            if (state == 2)
            {
                state = 4; // Pause
            }
            else if (state == 4)
            {
                state = 2; // Resume
            }
        }
    }

    // Mouse input for menu buttons
    if (event1.type == SDL_MOUSEBUTTONDOWN && event1.button.button == SDL_BUTTON_LEFT)
    {
        int mx = event1.button.x;
        int my = event1.button.y;

        // Pause icon during play
        if (state == 2)
        {
            if (btnPauseIcon.IsClicked(mx, my))
            {
                state = 4; // Pause
            }
        }
        else if (state == 4)
        {
            // Pause menu: resume / replay / sound
            if (btnResume.IsClicked(mx, my))
            {
                state = 2;
            }
            else if (btnReplay.IsClicked(mx, my))
            {
                resetGame();
                state = 2;
            }
            else if (btnSound.IsClicked(mx, my))
            {
                soundOn = !soundOn;
                Mix_Volume(-1, soundOn ? MIX_MAX_VOLUME : 0);
            }
        }
        else if (state == 3)
        {
            // Game over: allow replay by clicking replay button on board
            if (btnReplayEnd.IsClicked(mx, my))
            {
                resetGame();
                state = 2;
            }
        }
    }
}

void GameLoop::update()
{
    // Only update game logic during play state
    if (state == 2)
    {
        // Update player physics (gravity + movement)
        p.Update();

        // Move pipes
        pi1Up.PipeMoveUp();
        pi1Down.PipeMoveDown();
        pi2Up.PipeMoveUp();
        pi2Down.PipeMoveDown();

        // Check collisions with both pipe pairs
        if (checkPipeCollision(pi1Up, pi1Down) || checkPipeCollision(pi2Up, pi2Down))
        {
            snd.PlayBonk();
            score = calculateScore();
            SDL_Log("Game Over! Score: %d", score);
            setState(3);
        }

        // Check ground/ceiling collision
        if (p.yPos <= 0 || p.yPos >= 450)
        {
            snd.PlayBonk();
            score = calculateScore();
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

    b.Render(renderer);
    p.Render(renderer);

    pi1Up.Render(renderer);
    pi1Down.Render(renderer);

    pi2Up.Render(renderer);
    pi2Down.Render(renderer);

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

    b.Render(renderer);
    p.Render(renderer);

    menuStart.Render(renderer);

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

    b.Render(renderer);
    p.Render(renderer);

    pi1Up.Render(renderer);
    pi1Down.Render(renderer);

    pi2Up.Render(renderer);
    pi2Down.Render(renderer);

    menuEnd.Render(renderer);

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
    btnReplayEnd.Render(renderer);

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
    b.Render(renderer);
    p.Render(renderer);

    pi1Up.Render(renderer);
    pi1Down.Render(renderer);

    pi2Up.Render(renderer);
    pi2Down.Render(renderer);

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
    menuPauseTab.Render(renderer);
    btnResume.Render(renderer);
    btnReplay.Render(renderer);
    btnSound.Render(renderer);

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

// Helpers
int GameLoop::calculateScore()
{
    // Each pipe pair contributes 1 point when passed
    // Since we have 2 pairs (pi1 and pi2), and each pipe adds 0.5
    return static_cast<int>(pi1Up.SCORE + pi1Down.SCORE + pi2Up.SCORE + pi2Down.SCORE);
}

bool GameLoop::checkPipeCollision(Pipe& pipeUp, Pipe& pipeDown)
{
    // Check if player is horizontally aligned with pipe
    if((p.xPos + p.PLAYERWIDTH) > pipeUp.xPos && p.xPos < (pipeUp.xPos + pipeUp.PIPEWIDTH))
    {
        // Check if player hits top pipe or bottom pipe
        if(p.yPos < pipeUp.PIPEHEIGHT || 
           (p.yPos + p.PLAYERHEIGHT) > (pipeDown.PIPEHEIGHT + pipeDown.PIPEDISTANCE))
        {
            return true;
        }
    }
    return false;
}





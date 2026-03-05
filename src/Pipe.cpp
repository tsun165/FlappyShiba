#include "Pipe.h"

void Pipe::initialize()
{
    // Chỉ thiết lập tốc độ, không đụng tới vị trí/chiều cao
    // Vị trí (xPos) và pipeHeight sẽ được set trong reset()
    xVelocity = -3;
}

void Pipe::setTexture(const char* upPath, const char* downPath, SDL_Renderer* ren)
{
    up.setTexture(upPath, ren);
    down.setTexture(downPath, ren);
}

void Pipe::reset(int startX)
{
    xPos = startX;

    // Random chiều cao phần ống trên
    pipeHeight = minHeight + rand() % (maxHeight - minHeight + 1);

    // Cập nhật src/dest cho ống trên
    up.setSrc(0, 373 - pipeHeight, PIPEWIDTH, pipeHeight);
    up.setDest(xPos, 0, PIPEWIDTH, pipeHeight);

    // Chiều cao phần ống dưới
    int downHeight = SCREEN_HEIGHT - GAP - pipeHeight;
    if (downHeight < 0) downHeight = 0;

    // Cập nhật src/dest cho ống dưới
    down.setSrc(0, 0, PIPEWIDTH, downHeight);
    down.setDest(xPos, pipeHeight + GAP, PIPEWIDTH, downHeight);
}

void Pipe::update()
{
    // Di chuyển sang trái
    xPos += xVelocity;

    // Cập nhật lại dest cho cả 2 ống theo xPos mới
    // (src giữ nguyên)
    SDL_Rect& upDest = up.getDest();
    SDL_Rect& downDest = down.getDest();

    upDest.x = xPos;
    downDest.x = xPos;
}

void Pipe::render(SDL_Renderer* ren)
{
    up.render(ren);
    down.render(ren);
}
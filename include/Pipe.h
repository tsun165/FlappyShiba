#pragma once

#include <cstdlib>
#include "Object.h"

class Pipe {
public:
    static const int PIPEWIDTH = 65;
    static const int GAP = 170;   // khoảng trống giữa 2 ống
    static const int SCREEN_HEIGHT = 485;

    void initialize();
    void setTexture(const char* upPath, const char* downPath, SDL_Renderer* ren);
    void reset(int startX);   // random lại chiều cao, đặt vị trí ban đầu
    void update();            // cập nhật xPos và dest
    void render(SDL_Renderer* ren);
    int  getX()         const { return xPos; }
    int  getPipeHeight()const { return pipeHeight; }

    bool isOutOfScreen() const { return xPos < -PIPEWIDTH; }

    // cho GameLoop truy cập nếu cần
    int  minHeight = 140;
    int  maxHeight = 210;

private:
    Object up;
    Object down;

    int xPos;
    int pipeHeight;
    int xVelocity;
};
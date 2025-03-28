#include "object.h"
#include "Initclose.h"

object::object(int _x, int _y, int _width, int _height, int _speed){
    x=_x;
    y=_y;
    width=_width;
    height=_height;
    speed=_speed;
}

SDL_Rect object::rect() {
    return SDL_Rect{x, y, width, height};
}



void object::falling() {
    y += speed;
    if (y > SCREEN_HEIGHT - height) {
        y = SCREEN_HEIGHT - height;
    }
}


object banana(rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64), -50, 50, 44, 3);
object img10pts(-100, -100, 40, 40, 0);
object losebanner(SCREEN_WIDTH / 8, SCREEN_HEIGHT + 10, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4, 10);
object monkey((SCREEN_WIDTH - 100) / 2, SCREEN_HEIGHT - 375, 100, 100, 5);
object platform[7] = {
    object((SCREEN_WIDTH-400)/2, SCREEN_HEIGHT-275, 400, 40, 0),
    object(0, SCREEN_HEIGHT-425, 400, 40, 0),
    object(SCREEN_WIDTH-400, SCREEN_HEIGHT-425, 400, 40, 0),
    object(75, SCREEN_HEIGHT-575, 250, 40, 0),
    object(SCREEN_WIDTH-325, SCREEN_HEIGHT-575, 250, 40, 0),
    object(100, SCREEN_HEIGHT-125, 150, 40, 0),
    object(SCREEN_WIDTH-250, SCREEN_HEIGHT-125, 150, 40, 0)
};


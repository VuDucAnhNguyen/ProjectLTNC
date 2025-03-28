#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL.h>

struct object {
    int x, y, width, height, speed;

    object(int _x, int _y, int _width, int _height, int _speed);

    SDL_Rect rect();
    void falling();
};


extern object banana;
extern object platform[7];
extern object img10pts;
extern object losebanner;
extern object monkey;


#endif


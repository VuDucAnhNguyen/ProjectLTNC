#ifndef TEXT__H_
#define TEXT__H_

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

using namespace std;

extern int score;

struct textDisplay{
    string display;
    int x, y, textWidth=0, textHeight=0, speed;

    textDisplay(string _display, int _x, int _y, int _speed);

    void textSize(TTF_Font* font);

    void showText (TTF_Font*font,Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
};

extern textDisplay textScore;
extern textDisplay textGameOver;
extern textDisplay textScoreEnd;
extern textDisplay textSystem[7];
extern textDisplay textChooseMap;


#endif


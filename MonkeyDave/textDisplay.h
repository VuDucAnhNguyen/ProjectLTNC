#ifndef TEXT__H_
#define TEXT__H_

#include "Initclose.h"
#include <iostream>
using namespace std;

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
extern textDisplay textSystem[9];
extern textDisplay textChooseMap;
extern textDisplay textHighscores;
extern textDisplay textSetting;
extern textDisplay textGamePause;
extern textDisplay textCountDown;
extern textDisplay textNewHighScore;
extern textDisplay textEdgeforest;
extern textDisplay textDarkforest;
extern textDisplay textMagicforest;


#endif

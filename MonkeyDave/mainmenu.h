#ifndef MAINMENU__H_
#define MAINMENU__H_

#include "mainmenu.h"
#include <iostream>
using namespace std;

extern bool buttonClicked;
extern bool playClicked;
extern bool settingClicked;
extern bool highscoresClicked;
extern bool bannerChooseMap;
extern bool bannerHighScores;
extern bool bannerSetting;
extern bool turnonMusic;
extern string mapChoose;

void setting();
void resetmenu ();
void mainmenumain();

#endif

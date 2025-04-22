#ifndef MAINMENU__H_
#define MAINMENU__H_

#include <map>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "loadAudio.h"
#include "object.h"
#include "textDIsplay.h"
#include "mainmenu.h"

extern bool buttonClicked;
extern bool playClicked;
extern bool settingClicked;
extern bool highscoresClicked;
extern bool bannerChooseMap;
extern bool bannerHighScores;
extern bool bannerSetting;
extern bool turnonMusic;

extern string mapChoose;
extern map <string, int> highscores;

void setting();
void resetmenu ();
void mainmenumain();

#endif

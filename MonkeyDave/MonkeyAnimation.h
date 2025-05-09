#ifndef MONKEY_ANIMATION__H_
#define MONKEY_ANIMATION__H_

#include "Initclose.h"
#include <iostream>
using namespace std;

extern SDL_Rect defaultMonkeyRight;
extern SDL_Rect defaultMonkeyLeft;

extern SDL_Rect* currentClip;
extern Uint32 lastInputTime;
extern bool isBlinking;
extern bool isJump;
extern bool isrunning;
extern bool isFall;
extern bool isleft;
extern Uint32 currentTime;
extern Uint32 blinkStartTime;
extern Uint32 runStartTime;
extern int defaultfallvelocity;

void Monkeyblink(SDL_Rect*& currentClip, Uint32& blinkStartTime, bool& isBlinking,bool isleft);
void Monkeyrun(SDL_Rect*& currentClip, Uint32& runStartTime, bool isleft);
void MonkeyJump (SDL_Rect*& currentClip, int&y, bool& isJump, bool& isleft);
void MonkeyFall (SDL_Rect*& currentClip, int &y, bool &isOnPlatform,bool& isJump, bool& isleft, string mapChoose);
void Monkeymain(bool &isBlinking, string mapChoose);



#endif

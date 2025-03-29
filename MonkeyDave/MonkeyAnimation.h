#ifndef MONKEY_ANIMATION_H
#define MONKEY_ANIMATION_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "loadTexture.h"
#include "object.h"

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

void Monkeyblink(SDL_Rect*& currentClip, Uint32& blinkStartTime, bool& isBlinking,bool isleft);
void Monkeyrun(SDL_Rect*& currentClip, Uint32& runStartTime, bool isleft);
void MonkeyJump (SDL_Rect*& currentClip, int&y, bool& isJump, bool& isleft);
void MonkeyFall (SDL_Rect*& currentClip, int &y, bool &isOnPlatform,bool& isJump, bool& isleft);
void Monkeymain(bool &isBlinking);
void renderMonkey(SDL_Renderer* renderer,SDL_Texture* monkeyTexture, SDL_Rect* currentClip);


#endif

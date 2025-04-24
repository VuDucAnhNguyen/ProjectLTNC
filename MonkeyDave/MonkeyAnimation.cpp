#include "MonkeyAnimation.h"

#include "loadAudio.h"
#include "object.h"



SDL_Rect defaultMonkeyRight = {0, 0 , 232, 269 };
SDL_Rect BlinkEyeRight1 = { 232, 0, 229, 269 };
SDL_Rect BlinkEyeRight2 = { 461, 0, 230, 269 };
SDL_Rect BlinkEyeLeft2 = { 0, 0, 229, 269 };
SDL_Rect BlinkEyeLeft1 = { 229, 0, 231, 269 };
SDL_Rect defaultMonkeyLeft = { 460, 0, 231, 269 };
SDL_Rect Runningright1 = { 0, 0, 260, 293};
SDL_Rect Runningright2 = { 260, 0, 230, 293};
SDL_Rect Runningright3 = { 490, 0, 205, 293};
SDL_Rect Runningright4 = { 695, 0, 200, 293};
SDL_Rect Runningright5 = { 895, 0, 230, 293};
SDL_Rect Runningleft5 = { 0, 0, 239, 293};
SDL_Rect Runningleft4 = { 239, 0, 203, 293};
SDL_Rect Runningleft3 = { 442, 0, 186, 293};
SDL_Rect Runningleft2 = { 628, 0, 227, 293};
SDL_Rect Runningleft1 = { 855, 0, 273, 293};
SDL_Rect Jumpright = { 0, 0, 283, 269};
SDL_Rect Fallright = {283, 0,233,269};
SDL_Rect Jumpleft = { 240 , 0, 240, 269};
SDL_Rect Fallleft = {0, 0,235,269};
SDL_Rect* currentClip = &defaultMonkeyRight;
Uint32 lastInputTime = SDL_GetTicks();
bool isBlinking=false;
bool isrunning =false;
bool isJump=false;
bool isFall=false;
bool isleft=false;
bool fallthrough=false;
Uint32 blinkStartTime = 0;
Uint32 runStartTime=0;
int jumpvelocity = 16;
int defaultfallvelocity =4;
int fallvelocity =defaultfallvelocity;


void MonkeyJump (SDL_Rect*& currentClip, int &y, bool& isJump, bool& isleft){
    if(isleft){
        if (isJump) {
            currentClip=&Jumpleft;
            if(jumpvelocity>0){
                y-=jumpvelocity;
                jumpvelocity--;
            } else {
                isJump= false;
                jumpvelocity=16;
            }
        }
    } else{
        if (isJump) {
            currentClip=&Jumpright;
            if(jumpvelocity>0){
                y-=jumpvelocity;
                jumpvelocity--;
            } else {
                isJump= false;
                jumpvelocity=16;
            }
        }
    }
}

void MonkeyFall (SDL_Rect*& currentClip, int &y,bool &isOnPlatform, bool& isJump, bool& isleft, string mapChoose){
    if(mapChoose=="darkforest"){
        for (int i = 0; i < 7; i++) {
            if (monkey.isStandingOn(platformDarkForest[i])&&!fallthrough) {
            isOnPlatform = true;
            break;
            }
        }
    }
    if (mapChoose=="edgeforest"){
        for (int i = 0; i < 5; i++) {
            if (monkey.isStandingOn(platformEdgeForest[i])&&!fallthrough) {
            isOnPlatform = true;
            break;
            }
        }
    }
    if (mapChoose=="magicforest"){
        for (int i = 0; i < 7; i++) {
            if (monkey.isStandingOn(platformMagicForest[i])&&!fallthrough) {
            if(!isrunning){
            monkey.x+=platformMagicForest[i].speed;
            }
            isOnPlatform = true;
            break;
            }
        }
    }
    fallthrough=false;
    if(isleft){
        if (!isOnPlatform&&!isJump) {
            currentClip = &Fallleft;
            isFall=true;
            fallvelocity += 1;
            if (fallvelocity > 8){
                fallvelocity = 8;
            }
            monkey.y += fallvelocity;
        } else {
            fallvelocity =defaultfallvelocity;
            isFall=false;
        }
    } else {
        if (!isOnPlatform&&!isJump) {
            currentClip = &Fallright;
            isFall=true;
            fallvelocity += 1;
            if (fallvelocity > 8){
                fallvelocity = 8;

            }
            monkey.y += fallvelocity;
        } else {
            fallvelocity =defaultfallvelocity;
            isFall=false;
        }
    }
}

void Monkeyblink(SDL_Rect*& currentClip, Uint32& blinkStartTime, bool& isBlinking, bool isleft) {
    Uint32 elapsedTime = SDL_GetTicks() - blinkStartTime;
    if (isleft){
        if (elapsedTime < 50) {
            currentClip = &defaultMonkeyLeft;
        } else if (elapsedTime < 100) {
            currentClip = &BlinkEyeLeft1;
        } else if (elapsedTime < 150) {
            currentClip = &BlinkEyeLeft2;
        } else {
            currentClip = &defaultMonkeyLeft;
            isBlinking = false;
        }
    } else{
        if (elapsedTime < 50) {
            currentClip = &defaultMonkeyRight;
        } else if (elapsedTime < 100) {
            currentClip = &BlinkEyeRight1;
        } else if (elapsedTime < 150) {
            currentClip = &BlinkEyeRight2;
        } else {
            currentClip = &defaultMonkeyRight;
            isBlinking = false;
        }
    }
}

void Monkeyrun(SDL_Rect*& currentClip, Uint32& runStartTime, bool isleft) {
    if (isleft){
        Uint32 elapsedTime = SDL_GetTicks() - runStartTime;
        if (elapsedTime < 100) {
            currentClip = &Runningleft1;
        } else if (elapsedTime < 200) {
            currentClip = &Runningleft2;
        } else if (elapsedTime < 300) {
            currentClip = &Runningleft3;
        } else if (elapsedTime < 400) {
            currentClip = &Runningleft4;
        } else if (elapsedTime < 500) {
            currentClip = &Runningleft5;
        } else {
            currentClip = &Runningleft1;
            runStartTime = SDL_GetTicks();
        }
        monkey.x -= monkey.speed;
    } else {
        Uint32 elapsedTime = SDL_GetTicks() - runStartTime;
        if (elapsedTime < 100) {
            currentClip = &Runningright1;
        } else if (elapsedTime < 200) {
            currentClip = &Runningright2;
        } else if (elapsedTime < 300) {
            currentClip = &Runningright3;
        } else if (elapsedTime < 400) {
            currentClip = &Runningright4;
        } else if (elapsedTime < 500) {
            currentClip = &Runningright5;
        } else {
            currentClip = &Runningright1;
            runStartTime = SDL_GetTicks();
        }
        monkey.x += monkey.speed;
    }
}

void Monkeymain (bool& isBlinking, string mapChoose){
    Uint32 currentTime = SDL_GetTicks();
    if (isleft){
        currentClip=&defaultMonkeyLeft;
    } else {
        currentClip=&defaultMonkeyRight;
    }

    bool isOnPlatform = false;
    MonkeyFall(currentClip, monkey.y,isOnPlatform, isJump, isleft, mapChoose);

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP]&&isOnPlatform){
        isJump=true;
        Mix_HaltChannel(1);
        Mix_HaltChannel(2);
        Mix_PlayChannel(1, jumpSound, 0);
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && isOnPlatform){
        fallthrough=true;
    } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        if (isJump||isFall){
            monkey.x -= monkey.speed;
            isrunning=false;
            isleft = true;
            Mix_HaltChannel(2);
        } else {
            if (!isrunning) {
                runStartTime = SDL_GetTicks();
                Mix_HaltChannel(1);
                if (mapChoose=="edgeforest"){
                    Mix_PlayChannel(2, runwoodSound, -1);
                } else {
                    Mix_PlayChannel(2, rungrassSound, -1);
                }
            }
            isrunning = true;
            isleft = true;
            Monkeyrun(currentClip, runStartTime, isleft);
        }
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        if (isJump||isFall){
            monkey.x += monkey.speed;
            isrunning=false;
            isleft = false;
        } else {
            if (!isrunning) {
                runStartTime = SDL_GetTicks();
                Mix_HaltChannel(1);
                if (mapChoose=="edgeforest"){
                    Mix_PlayChannel(2, runwoodSound, -1);
                } else {
                    Mix_PlayChannel(2, rungrassSound, -1);
                }
            }
            isrunning = true;
            isleft = false;
            Monkeyrun(currentClip, runStartTime, isleft);
        }
    } else {
        isrunning = false;
        Mix_HaltChannel(2);
    }
    if (monkey.x < 0) monkey.x = 0;
    if (monkey.x > SCREEN_WIDTH - 100) monkey.x = SCREEN_WIDTH - 100;

    if(isJump){
        MonkeyJump(currentClip, monkey.y, isJump, isleft);
    }

    if (!isBlinking && currentTime - lastInputTime > 2000) {
        isBlinking = true;
        blinkStartTime = SDL_GetTicks();
    }
    if (isBlinking) {
        Monkeyblink(currentClip, blinkStartTime, isBlinking, isleft);
        lastInputTime=currentTime;
        }
}




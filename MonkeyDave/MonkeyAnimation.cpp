#include "MonkeyAnimation.h"
#include "Initclose.h"


SDL_Rect defaultMonkeyRight = { 0, 0, 230, 255 };
SDL_Rect BlinkEyeRight1 = { 230, 0, 230, 255 };
SDL_Rect BlinkEyeRight2 = { 460, 0, 400, 255 };
SDL_Rect BlinkEyeLeft2 = { 0, 0, 230, 255 };
SDL_Rect BlinkEyeLeft1 = { 230, 0, 230, 255 };
SDL_Rect defaultMonkeyLeft = { 460, 0, 400, 255 };
SDL_Rect Runningright1 = { 0, 0, 260, 500};
SDL_Rect Runningright2 = { 260, 0, 230, 500};
SDL_Rect Runningright3 = { 490, 0, 205, 500};
SDL_Rect Runningright4 = { 695, 0, 200, 500};
SDL_Rect Runningright5 = { 895, 0, 230, 500};
SDL_Rect Runningleft5 = { 0, 0, 250, 500};
SDL_Rect Runningleft4 = { 250, 0, 200, 500};
SDL_Rect Runningleft3 = { 450, 0, 200, 500};
SDL_Rect Runningleft2 = { 650, 0, 230, 500};
SDL_Rect Runningleft1 = { 880, 0, 270, 500};
SDL_Rect Jumpright = { 0, 0, 275, 500};
SDL_Rect Fallright = {275, 0,270,500};
SDL_Rect Jumpleft = { 240, 0, 240, 500};
SDL_Rect Fallleft = {0, 0,235,500};
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
int fallvelocity =4;

bool isStandingOn(SDL_Rect rectA,SDL_Rect rectB) {
    bool verticalOverlap = (rectA.y + rectA.h >= rectB.y-3)&& (rectA.y + rectA.h <= rectB.y + 5);
    bool horizontalOverlap = (rectA.x + rectA.w > rectB.x) && (rectA.x < rectB.x + rectB.w);

    return verticalOverlap && horizontalOverlap;
}

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
            if (isStandingOn(monkey.rect(), platformDarkForest[i].rect())&&!fallthrough) {
            isOnPlatform = true;
            break;
            }
        }
    }
    if (mapChoose=="edgeforest"){
        for (int i = 0; i < 5; i++) {
            if (isStandingOn(monkey.rect(), platformEdgeForest[i].rect())&&!fallthrough) {
            isOnPlatform = true;
            break;
            }
        }
    }
    if (mapChoose=="magicforest"){
        for (int i = 0; i < 7; i++) {
            if (isStandingOn(monkey.rect(), platformMagicForest[i].rect())&&!fallthrough) {
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
            fallvelocity =4;
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
            fallvelocity =4;
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
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && isOnPlatform){
        fallthrough=true;
    } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        if (isJump||isFall){
            monkey.x -= monkey.speed;
            isleft = true;
        } else {
            if (!isrunning) {
                runStartTime = SDL_GetTicks();
            }
            isrunning = true;
            isleft = true;
            Monkeyrun(currentClip, runStartTime, isleft);
        }
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        if (isJump||isFall){
            monkey.x += monkey.speed;
            isleft = false;
        } else {
            if (!isrunning) {
                runStartTime = SDL_GetTicks();
            }
            isrunning = true;
            isleft = false;
            Monkeyrun(currentClip, runStartTime, isleft);
        }
    } else {
        isrunning = false;
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

void renderMonkey(SDL_Renderer* renderer, SDL_Texture* monkeyTexture, SDL_Rect* currentClip) {
        SDL_Rect monkeyRect=monkey.rect();
        SDL_RenderCopy(renderer, monkeyTexture,  currentClip, &monkeyRect);
}



#include <cstdlib>
#include <ctime>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "object.h"
#include "MonkeyAnimation.h"
#include "textDIsplay.h"


Uint32 startTime = SDL_GetTicks();
Uint32 beehiveTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;

bool playinggame = false;

bool bannerGameOver = false;
bool loseCondition = false;
bool img10appear = false;
bool beehivefall = false;
bool warningappear = false;

string map1 = "edgeforest";
string map2 = "darkforest";
string map3 = "magicforest";
string mapChoose = " ";
bool playClicked = false;
bool bannerChooseMap = false;


void retry (){
    bannerGameOver =false;
    loseCondition = false;
    img10appear = false;
    warningappear = false;
    banana.x = rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64);
    banana.y = -50;
    for (int i=0;i<2;i++){
        beehive[i].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64);
        beehive[i].y = -70;
    }
    banner[0].x = SCREEN_WIDTH / 6;
    banner[0].y = SCREEN_HEIGHT + 10;
    monkey.x = (SCREEN_WIDTH - 100) / 2;
    monkey.y = SCREEN_HEIGHT - 335;
    SDL_SetTextureColorMod(gbackgroundedgeforestTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gbackgrounddarkforestTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gbackgroundmagicforestTexture, 255, 255, 255);

    SDL_SetTextureColorMod(gplatformedgeforestTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gplatformdarkforestTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gplatformmagicforestTexture, 255, 255, 255);

    SDL_SetTextureColorMod(gbananaTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gbeehiveTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gwarningTexture, 255, 255, 255);

    SDL_SetTextureColorMod(gmonkeystaystandrightTexture, 255, 255 ,255);
    SDL_SetTextureColorMod(gmonkeystaystandleftTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gmonkeyjumpandfallleftTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gmonkeyjumpandfallrightTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gmonkeyrunningleftTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gmonkeyrunningrightTexture, 255, 255, 255);

    SDL_SetTextureColorMod(gbuttonTexture, 255, 255, 255);
    startTime = SDL_GetTicks();
    beehiveTime = SDL_GetTicks();
    score = 0;
    textScore.display = "Score: " + to_string(score);
    textGameOver.y = SCREEN_HEIGHT+50;
    textScoreEnd.y = SCREEN_HEIGHT+150;
}

void mainmenu (){
    mapChoose = " ";
    playClicked = false;
    bannerChooseMap = false;
    SDL_SetTextureColorMod(gbackgroundstartTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gbuttonTexture, 255, 255, 255);
    banner[1].y = SCREEN_HEIGHT+10;
    textChooseMap.y = SCREEN_HEIGHT+50;

}














bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x) &&
           (a.x < b.x + b.w) &&
           (a.y + a.h > b.y) &&
           (a.y < b.y + b.h);
}

int main( int argc, char* args[] ){

    srand(time(0));
    if( !init() ){
        cout<<"Failed to initialize!\n";
    }
    else{
        if( !(loadFonts()&&loadTextures(gRenderer))){
            cout<<"Failed to load media!\n";
        }
        else{
            bool quit = false;

            SDL_Event e;

            while( !quit ){
                Uint32 frameStart = SDL_GetTicks();
                Uint32 currentTime = SDL_GetTicks();


                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT ){
                        quit = true;
                    }
                    if (e.type == SDL_KEYDOWN || e.type==SDL_MOUSEBUTTONDOWN) {
                        lastInputTime = currentTime;
                        isBlinking = false;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (!playinggame){
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;
                            if (button[2].clicked(mouseX, mouseY)&&!playClicked) {
                                playClicked = true;
                            }
                            if (bannerChooseMap&&playClicked){
                                    if (previewEdgeForest.clicked(mouseX, mouseY)){
                                        playinggame=true;
                                        mapChoose=map1;
                                        retry();
                                    }
                                    if (previewDarkForest.clicked(mouseX, mouseY)){
                                        playinggame=true;
                                        mapChoose=map2;
                                        retry();
                                    }
                                    if (previewMagicForest.clicked(mouseX, mouseY)){
                                        playinggame=true;
                                        mapChoose=map3;
                                        retry();
                                    }
                                    if (buttonback.clicked(mouseX, mouseY)){
                                        mainmenu();
                                    }

                                }

                            if (button[5].clicked(mouseX, mouseY)){
                                quit=true;
                            }
                        } else {
                            if (bannerGameOver){
                                int mouseX = e.button.x;
                                int mouseY = e.button.y;
                                if (button[0].clicked(mouseX, mouseY)) {
                                    retry();
                                } else if (button[1].clicked(mouseX, mouseY)){
                                    playinggame=false;
                                    mainmenu();
                                }
                            }
                        }
                    }
                }
                if (!playinggame){
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderCopy(gRenderer, gbackgroundstartTexture, NULL, NULL);
                    for (int i=2;i<6;i++){
                        SDL_Rect buttonRect=button[i].rect();
                        SDL_RenderCopy(gRenderer, gbuttonTexture, NULL, &buttonRect);
                        textSystem[i].textSize(Boldonsefont14);
                        textSystem[i].x = button[i].x+(button[i].width-textSystem[i].textWidth)/2;
                        textSystem[i].y = button[i].y+(button[i].height-textSystem[i].textHeight)/2;
                        if (playClicked){
                            textSystem[i].showText(Boldonsefont14, 71, 40, 11,255);
                        } else {
                            textSystem[i].showText(Boldonsefont14, 181, 101, 29,255);
                        }
                    }


                    if (playClicked){
                            SDL_SetTextureColorMod(gbackgroundstartTexture, 100, 100, 100);
                            SDL_SetTextureColorMod(gbuttonTexture, 100, 100, 100);

                        if (!bannerChooseMap) {
                            banner[1].y -= banner[1].speed;
                            textChooseMap.y -= textChooseMap.speed;
                            if (banner[1].y <= SCREEN_HEIGHT /6) {
                                bannerChooseMap = true;
                            }
                        }
                        SDL_Rect banner1Rect=banner[1].rect();
                        SDL_RenderCopy(gRenderer, gbannerTexture, NULL, &banner1Rect);
                        if (bannerChooseMap){
                            SDL_Rect previewEdgeForestRect=previewEdgeForest.rect();
                            SDL_RenderCopy(gRenderer, gpreviewedgeforestTexture, NULL, &previewEdgeForestRect);
                            SDL_Rect previewDarkForestRect=previewDarkForest.rect();
                            SDL_RenderCopy(gRenderer, gpreviewdarkforestTexture, NULL, &previewDarkForestRect);
                            SDL_Rect previewMagicForestRect=previewMagicForest.rect();
                            SDL_RenderCopy(gRenderer, gpreviewmagicforestTexture, NULL, &previewMagicForestRect);
                            SDL_Rect buttonbackRect = buttonback.rect();
                            SDL_RenderCopy(gRenderer, gbuttonbackTexture, NULL, &buttonbackRect);
                            textSystem[6].textSize(Boldonsefont14);
                            textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
                            textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
                            textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
                        }
                        textChooseMap.textSize(HanaleiFillfont64);
                        textChooseMap.x = (SCREEN_WIDTH-textChooseMap.textWidth)/2;
                        textChooseMap.showText(HanaleiFillfont64,255, 70, 0, 255);
                    }

                } else {
                if (banana.y+banana.height >= SCREEN_HEIGHT||monkey.y+monkey.height>=SCREEN_HEIGHT){
                    loseCondition = true;
                }

                if (!loseCondition){
                    Monkeymain(isBlinking, mapChoose);
                    if (SDL_GetTicks()-startTime>3000){
                        banana.falling();
                    }
                    if (mapChoose==map2||mapChoose==map3){
                        if(SDL_GetTicks()-beehiveTime>7000&&SDL_GetTicks()-beehiveTime<=10000){
                            warningappear=true;
                        } else if(SDL_GetTicks()-beehiveTime>10000){
                            warningappear=false;
                            beehivefall=true;
                        }
                    }
                }

                if(beehivefall){
                    for(int i=0;i<2;i++){
                        beehive[i].falling();
                        if(checkCollision(beehive[i].rect(), monkey.rect())){
                            loseCondition=true;
                            beehivefall=false;
                        } else if(beehive[i].y+beehive[i].height==SCREEN_HEIGHT){
                            beehiveTime=SDL_GetTicks();
                            beehive[i].x = rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64);
                            beehive[i].y = -70;
                            beehivefall=false;
                        }
                    }
                }

                if (checkCollision(monkey.rect(), banana.rect())) {
                    img10pts.x = banana.x;
                    img10pts.y = banana.y;

                    banana.y = -50;
                    banana.x = rand() % (SCREEN_WIDTH*62/64-50)+(SCREEN_WIDTH /64);
                    score +=10;

                    textScore.display="Score: "+to_string(score);

                    img10appear = true;
                    img10collision = SDL_GetTicks();
                }

                if(img10appear&&SDL_GetTicks()-img10collision >400){
                    img10pts.x = -100;
                    img10pts.y = -100;
                    img10appear = false;
                }

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                if (loseCondition) {
                    SDL_SetTextureColorMod(gbackgroundedgeforestTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbackgrounddarkforestTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbackgroundmagicforestTexture, 100, 100, 100);

                    SDL_SetTextureColorMod(gplatformedgeforestTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gplatformdarkforestTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gplatformmagicforestTexture, 100, 100, 100);

                    SDL_SetTextureColorMod(gbananaTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbeehiveTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gwarningTexture, 100, 100, 100);

                    SDL_SetTextureColorMod(gmonkeystaystandrightTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeystaystandleftTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeyjumpandfallleftTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeyjumpandfallrightTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeyrunningleftTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeyrunningrightTexture, 100, 100, 100);
                }
                if (mapChoose==map1){
                    banana.speed = 4;
                    SDL_RenderCopy(gRenderer, gbackgroundedgeforestTexture, NULL, NULL);
                    for (int i=0;i<5;i++){
                        SDL_Rect platformedgeforestRect=platformEdgeForest[i].rect();
                        SDL_RenderCopy(gRenderer, gplatformedgeforestTexture, NULL, &platformedgeforestRect);
                    }
                } else if (mapChoose==map2){
                    SDL_RenderCopy(gRenderer, gbackgrounddarkforestTexture, NULL, NULL);
                    for (int i=0;i<7;i++){
                        SDL_Rect platformdarkforestRect=platformDarkForest[i].rect();
                        SDL_RenderCopy(gRenderer, gplatformdarkforestTexture, NULL, &platformdarkforestRect);
                    }
                } else if (mapChoose==map3){
                    SDL_RenderCopy(gRenderer, gbackgroundmagicforestTexture, NULL, NULL);
                    platformMagicForest[3].moving(0,180);
                    platformMagicForest[4].moving(SCREEN_WIDTH/2+150,SCREEN_WIDTH-platformMagicForest[4].width);
                    platformMagicForest[5].moving(0,180);
                    platformMagicForest[6].moving(SCREEN_WIDTH-330,SCREEN_WIDTH-platformMagicForest[6].width);

                    for (int i=0;i<7;i++){
                        SDL_Rect platformmagicforestRect=platformMagicForest[i].rect();
                        SDL_RenderCopy(gRenderer, gplatformmagicforestTexture, NULL, &platformmagicforestRect);
                    }
                }

                SDL_Rect bananaRect=banana.rect();
                SDL_RenderCopy(gRenderer, gbananaTexture, NULL, &bananaRect);
                SDL_Rect img10ptsRect=img10pts.rect();
                SDL_RenderCopy(gRenderer, g10ptsTexture, NULL, &img10ptsRect);
                for (int i=0;i<2;i++){
                    SDL_Rect beehiveRect=beehive[i].rect();
                    SDL_RenderCopy(gRenderer, gbeehiveTexture, NULL, &beehiveRect);
                }

                if (warningappear==true){
                    for(int i=0;i<2;i++){
                        warning[i].x=beehive[i].x;
                        SDL_Rect warningRect=warning[i].rect();
                        SDL_RenderCopy(gRenderer, gwarningTexture, NULL, &warningRect);
                    }
                }

                if (isJump){
                    if (isleft){
                        renderMonkey(gRenderer, gmonkeyjumpandfallleftTexture, currentClip);
                    } else {
                        renderMonkey(gRenderer, gmonkeyjumpandfallrightTexture, currentClip);
                    }
                } else if (isFall){
                    if (isleft){
                        renderMonkey(gRenderer, gmonkeyjumpandfallleftTexture, currentClip);
                    } else {
                        renderMonkey(gRenderer, gmonkeyjumpandfallrightTexture, currentClip);
                    }
                } else if (isrunning){
                    if (isleft){
                        renderMonkey(gRenderer, gmonkeyrunningleftTexture, currentClip);
                    } else {
                        renderMonkey(gRenderer, gmonkeyrunningrightTexture, currentClip);
                    }
                } else{
                    if (isleft){
                        renderMonkey(gRenderer, gmonkeystaystandleftTexture, currentClip);
                    } else {
                        renderMonkey(gRenderer, gmonkeystaystandrightTexture, currentClip);
                    }
                }

                if (loseCondition) {
                    if (!bannerGameOver) {
                        banner[0].y -= banner[0].speed;
                        textGameOver.y -= textGameOver.speed;
                        if (banner[0].y <= SCREEN_HEIGHT /4) {
                            textScoreEnd.display=textScore.display;
                            textScoreEnd.textSize(Boldonsefont24);
                            textScoreEnd.x = (SCREEN_WIDTH-textScoreEnd.textWidth)/2;
                            textScoreEnd.y = SCREEN_HEIGHT-410;


                            bannerGameOver = true;
                        }
                    }
                    SDL_Rect banner0Rect=banner[0].rect();
                    SDL_RenderCopy(gRenderer, gbannerTexture, NULL, &banner0Rect);
                    if(bannerGameOver){
                        for (int i=0;i<2;i++){
                            SDL_Rect buttonRect=button[i].rect();
                            SDL_RenderCopy(gRenderer, gbuttonTexture, NULL, &buttonRect);
                            textSystem[i].textSize(Boldonsefont14);
                            textSystem[i].x = button[i].x+(button[i].width-textSystem[i].textWidth)/2;
                            textSystem[i].y = button[i].y+(button[i].height-textSystem[i].textHeight)/2;
                            textSystem[i].showText(Boldonsefont14, 181, 101, 29,255);
                        }
                    }

                    textGameOver.textSize(HanaleiFillfont64);
                    textGameOver.x = (SCREEN_WIDTH-textGameOver.textWidth)/2;
                    textGameOver.showText(HanaleiFillfont64,255, 0, 0, 255);
                    textScoreEnd.showText(Boldonsefont24,255, 165,0,255);

                } else{
                    textScore.textSize(Boldonsefont14);
                    textScore.x= SCREEN_WIDTH-textScore.textWidth;
                    textScore.showText(Boldonsefont14,255, 165, 0 ,255);
                }
                }

                SDL_RenderPresent( gRenderer );

                int frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < FRAME_DELAY){
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
            }
        }
    }
    close();

	return 0;
}

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "loadAudio.h"
#include "object.h"
#include "MonkeyAnimation.h"
#include "textDIsplay.h"
#include "mainmenu.h"


Uint32 startTime = SDL_GetTicks();
Uint32 beehiveTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;
Uint32 resumetime= SDL_GetTicks();
Uint32 gamePausestart = SDL_GetTicks();



bool playinggame = false;

bool gamePause = false;
bool bannerGameOver = false;
bool loseCondition = false;
bool img10appear = false;
bool warningappear = false;
bool warningsound =false;
bool pointsound = false;
bool losesound = false;
bool bannergamepause = false;
bool resumegame = false;
bool newhighscoreappear = false;
int score = 0;

string map1 = "edgeforest";
string map2 = "darkforest";
string map3 = "magicforest";







void colorgamedefault (){
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
}

void retry (){
    bannerGameOver =false;
    loseCondition = false;
    img10appear = false;
    warningappear = false;
    isJump = false;
    losesound = false;
    gamePause = false;
    resumegame=false;
    newhighscoreappear=false;
    banana.x = rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64);
    banana.y = -50;
    beehive[0].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64);
    beehive[1].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70 -142) + (SCREEN_WIDTH / 64);
    if (beehive[1].x>=beehive[0].x-71){
        beehive[1].x+=142;
    }
    beehive[0].y=-70;
    beehive[1].y=-70;
    banner[0].y = SCREEN_HEIGHT + 10;
    monkey.x = (SCREEN_WIDTH - 100) / 2;
    monkey.y = SCREEN_HEIGHT - 335;
    monkey.speed=6;
    banana.speed=3;
    defaultfallvelocity=4;
    beehive[0].speed=7;
    beehive[1].speed=7;
    colorgamedefault();
    startTime = SDL_GetTicks();
    beehiveTime = SDL_GetTicks();
    score = 0;
    textScore.display = "Score: " + to_string(score);
    textGameOver.y = SCREEN_HEIGHT+50;
}

void colorgamelow (){
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










void countdown (Uint32 x){
    if (x<1000){
        textCountDown.display="3";
    } else if (x<2000){
        textCountDown.display="2";
    } else if (x<3000){
        textCountDown.display="1";
    }
}

void loadHighScores() {
    ifstream file("high_scores.txt");
    if (!file.is_open()) return;

    string mapgame;
    int score;
    while (file >> mapgame >> score) {
        highscores[mapgame] = score;
    }

    file.close();
}

void saveHighScores() {
    ofstream file("high_scores.txt");
    if (!file.is_open()) return;

    for (auto it = highscores.begin(); it != highscores.end(); ++it) {
    file << it->first << " " << it->second <<endl;
    }

    file.close();
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
        if( !(loadFonts()&&loadTextures(gRenderer)&&loadAudio())){
            cout<<"Failed to load media!\n";
        }
        else{
            bool quit = false;

            loadHighScores();
            SDL_Event e;

            while( !quit ){
                Uint32 frameStart = SDL_GetTicks();
                Uint32 currentTime = SDL_GetTicks();

                int volumemusic = 128*(musicthumb.x-musicbar.x)/(musicbar.width-musicthumb.width);
                int volumesound = 128*(soundthumb.x-soundbar.x)/(soundbar.width-soundthumb.width);
                Mix_VolumeMusic(volumemusic);

                for (int i=1;i<6;i++){
                    Mix_Volume(i, volumesound);
                }

                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT ){
                        quit = true;
                    }
                    if (e.type == SDL_KEYDOWN || e.type==SDL_MOUSEBUTTONDOWN) {
                        lastInputTime = currentTime;
                        isBlinking = false;
                    }
                    if (!playinggame) {
                        if (e.type == SDL_MOUSEBUTTONDOWN){
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;
                            if (button[2].clicked(mouseX, mouseY)&&!buttonClicked) {
                                buttonClicked = true;
                                playClicked = true;
                            }
                            if (button[3].clicked(mouseX, mouseY)&&!buttonClicked) {
                                buttonClicked = true;
                                highscoresClicked = true;
                            }
                            if (button[5].clicked(mouseX, mouseY)&&!buttonClicked) {
                                buttonClicked = true;
                                settingClicked = true;
                            }
                            if (bannerChooseMap||bannerSetting||bannerHighScores){
                                if (buttonback.clicked(mouseX, mouseY)){
                                    resetmenu();
                                }
                            }
                            if (bannerSetting){
                                if(musicbar.clicked(mouseX,mouseY)){
                                    musicthumb.x=mouseX-musicthumb.width/2;
                                    if (musicthumb.x<musicbar.x){
                                        musicthumb.x=musicbar.x;
                                    }
                                    if (musicthumb.x+musicthumb.width>musicbar.x+musicbar.width){
                                        musicthumb.x=musicbar.x+musicbar.width-musicthumb.width;
                                    }
                                }
                                if (soundbar.clicked(mouseX,mouseY)){
                                    soundthumb.x=mouseX-soundthumb.width/2;
                                    if (soundthumb.x<soundbar.x){
                                        soundthumb.x=soundbar.x;
                                    }
                                    if (soundthumb.x+soundthumb.width>soundbar.x+soundbar.width){
                                        soundthumb.x=soundbar.x+soundbar.width-soundthumb.width;
                                    }
                                }
                            }
                            if (bannerChooseMap){
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
                            }
                            if (bannerHighScores){
                                if(buttonreset[0].clicked(mouseX,mouseY)){
                                    highscores["edgeforest"]=0;
                                }
                                if(buttonreset[1].clicked(mouseX,mouseY)){
                                    highscores["darkforest"]=0;
                                }
                                if(buttonreset[2].clicked(mouseX,mouseY)){
                                    highscores["magicforest"]=0;
                                }
                                saveHighScores();
                            }

                            if (button[4].clicked(mouseX, mouseY)&&!buttonClicked){
                                quit=true;
                            }
                        }
                    } else {
                        if (e.type == SDL_KEYDOWN&&!resumegame&&!loseCondition){
                            if (e.key.keysym.sym== SDLK_ESCAPE&&!gamePause){
                                gamePause = true;
                                gamePausestart = SDL_GetTicks();
                            }
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN){
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;
                            if (bannergamepause){
                                if (button[7].clicked(mouseX, mouseY)&&!settingClicked) {
                                    retry();
                                }
                                if (button[8].clicked(mouseX, mouseY)&&!settingClicked){
                                    playinggame=false;
                                    resetmenu();
                                }
                                if (button[6].clicked(mouseX, mouseY)&&!settingClicked){
                                    resumetime=SDL_GetTicks();
                                    resumegame=true;
                                    gamePause=false;
                                }
                                if (button[5].clicked(mouseX, mouseY)){
                                    settingClicked = true;
                                }
                            }
                            if (bannerSetting){
                                if(musicbar.clicked(mouseX,mouseY)){
                                    musicthumb.x=mouseX-musicthumb.width/2;
                                    if (musicthumb.x<musicbar.x){
                                        musicthumb.x=musicbar.x;
                                    }
                                    if (musicthumb.x+musicthumb.width>musicbar.x+musicbar.width){
                                        musicthumb.x=musicbar.x+musicbar.width-musicthumb.width;
                                    }
                                }
                                if (soundbar.clicked(mouseX,mouseY)){
                                    soundthumb.x=mouseX-soundthumb.width/2;
                                    if (soundthumb.x<soundbar.x){
                                        soundthumb.x=soundbar.x;
                                    }
                                    if (soundthumb.x+soundthumb.width>soundbar.x+soundbar.width){
                                        soundthumb.x=soundbar.x+soundbar.width-soundthumb.width;
                                    }
                                }
                                if (buttonback.clicked(mouseX, mouseY)){
                                    settingClicked=false;
                                    bannerSetting=false;
                                    bannergamepause=true;
                                    banner[3].y = SCREEN_HEIGHT +10;
                                    textSetting.y = SCREEN_HEIGHT +50;
                                }
                            }
                            if (bannerGameOver){
                                if (button[0].clicked(mouseX, mouseY)) {
                                    retry();
                                }
                                if (button[1].clicked(mouseX, mouseY)){
                                    playinggame=false;
                                    resetmenu();
                                }
                            }
                        }
                    }
                }

                if (!playinggame){
                    mainmenumain();
                } else {
                    Mix_HaltMusic();
                    turnonMusic = false;

                    if (banana.y+banana.height >= SCREEN_HEIGHT||monkey.y+monkey.height>=SCREEN_HEIGHT){
                        loseCondition = true;
                    }

                    if (resumegame){
                        colorgamelow();
                        if(currentTime>resumetime){
                            countdown(currentTime-resumetime);
                            if (currentTime-resumetime>3000){
                                Uint32 pausedDuration = SDL_GetTicks() - gamePausestart;
                                beehiveTime += pausedDuration;
                                colorgamedefault();
                                banner[4].y=SCREEN_HEIGHT + 10;
                                textGamePause.y = SCREEN_HEIGHT +50;
                                bannergamepause=false;
                                for (int i=1;i<5;i++){
                                    Mix_Resume(i);
                                }
                                resumegame=false;
                            }
                        }
                    }
                    else if (!loseCondition&&!gamePause){
                        if (score>2000){
                            monkey.speed=8;
                            banana.speed=6;
                            defaultfallvelocity=7;
                            beehive[0].speed=10;
                            beehive[1].speed=10;
                        } else if (score>1000){
                            monkey.speed=7;
                            banana.speed=5;
                            defaultfallvelocity=6;
                            beehive[0].speed=9;
                            beehive[1].speed=9;
                        } else if (score>200){
                            monkey.speed=6;
                            banana.speed=4;
                            defaultfallvelocity=5;
                            beehive[0].speed=8;
                            beehive[1].speed=8;
                        }

                        Monkeymain(isBlinking, mapChoose);
                        if (SDL_GetTicks()-startTime>3000){
                            banana.falling();
                        }
                        if (mapChoose==map2||mapChoose==map3){
                            if(SDL_GetTicks()-beehiveTime>7000&&SDL_GetTicks()-beehiveTime<=10000){
                                warningappear=true;
                            } else if(SDL_GetTicks()-beehiveTime>10000){
                                warningappear=false;
                                warningsound=false;
                                for(int i=0;i<2;i++){
                                    beehive[i].falling();
                                    if(checkCollision(beehive[i].rect() ,monkey.rect())){
                                        loseCondition=true;
                                    }
                                    if(beehive[i].y+beehive[i].height==SCREEN_HEIGHT){
                                        beehiveTime=SDL_GetTicks();
                                        beehive[0].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64);
                                        beehive[1].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70 -142) + (SCREEN_WIDTH / 64);
                                        if (beehive[1].x>=beehive[0].x-71){
                                            beehive[1].x+=142;
                                        }
                                        beehive[i].y = -70;
                                    }
                                }
                            }
                        }
                    }


                    if (checkCollision(banana.rect(), monkey.rect())) {
                        img10pts.x = banana.x;
                        img10pts.y = banana.y;

                        banana.y = -100;
                        if (warningappear){
                            int firstbeehiveX=min(beehive[0].x,beehive[1].x);
                            banana.x = rand() % (SCREEN_WIDTH*62/64-50-102-142)+(SCREEN_WIDTH /64);
                            if (banana.x>=firstbeehiveX-51&&banana.x<firstbeehiveX+70-51){
                                banana.x+=122;
                            } else if (banana.x>=max(beehive[0].x,beehive[1].x)-51){
                                banana.x+=244;
                            }
                        } else {
                            banana.x = rand() % (SCREEN_WIDTH*62/64-50)+(SCREEN_WIDTH /64);
                        }

                        score +=10;
                        textScore.display="Score: "+to_string(score);

                        img10appear = true;
                        img10collision = SDL_GetTicks();
                        if (!pointsound){
                            Mix_HaltChannel(4);
                            Mix_PlayChannel(4 , pointSound, 0);
                            pointsound=true;
                        }
                    }

                    if(img10appear&&SDL_GetTicks()-img10collision >400){
                        img10pts.x = -100;
                        img10pts.y = -100;
                        img10appear = false;
                        pointsound = false;
                    }

                    if (loseCondition) {
                        if (highscores[mapChoose]<score){
                            highscores[mapChoose] = score;
                            newhighscoreappear=true;
                        }
                        for (int i=1;i<5;i++){
                            Mix_HaltChannel(i);
                        };
                        if (!losesound){
                            Mix_PlayChannel(5, loseSound, 0);
                            losesound=true;
                        }
                        colorgamelow();
                    }

                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    if (mapChoose==map1){
                        SDL_RenderCopy(gRenderer, gbackgroundedgeforestTexture, NULL, NULL);
                        for (int i=0;i<5;i++){
                            platformEdgeForest[i].renderobject(gRenderer, gplatformedgeforestTexture, NULL);
                        }
                    } else if (mapChoose==map2){
                        SDL_RenderCopy(gRenderer, gbackgrounddarkforestTexture, NULL, NULL);
                        for (int i=0;i<7;i++){
                            platformDarkForest[i].renderobject(gRenderer, gplatformdarkforestTexture, NULL);
                        }
                    } else if (mapChoose==map3){
                        SDL_RenderCopy(gRenderer, gbackgroundmagicforestTexture, NULL, NULL);
                        if (!gamePause&&!resumegame){
                            platformMagicForest[3].moving(0,180);
                            platformMagicForest[4].moving(SCREEN_WIDTH/2+150,SCREEN_WIDTH-platformMagicForest[4].width);
                            platformMagicForest[5].moving(0,180);
                            platformMagicForest[6].moving(SCREEN_WIDTH-330,SCREEN_WIDTH-platformMagicForest[6].width);
                        }

                        for (int i=0;i<7;i++){
                            platformMagicForest[i].renderobject(gRenderer, gplatformmagicforestTexture, NULL);
                        }
                    }

                    banana.renderobject(gRenderer, gbananaTexture, NULL);
                    img10pts.renderobject(gRenderer, g10ptsTexture, NULL);
                    for (int i=0;i<2;i++){
                        beehive[i].renderobject(gRenderer, gbeehiveTexture, NULL);
                    }

                    if (warningappear==true){
                        if (!warningsound){
                            Mix_PlayChannel(3, warningSound, 0);
                            warningsound=true;
                        }
                        for(int i=0;i<2;i++){
                            warning[i].x=beehive[i].x;
                            SDL_Rect warningRect=warning[i].rect();
                            SDL_RenderCopy(gRenderer, gwarningTexture, NULL, &warningRect);
                        }
                    }

                    if (isJump){
                        if (isleft){
                            monkey.renderobject(gRenderer, gmonkeyjumpandfallleftTexture, currentClip);
                        } else {
                            monkey.renderobject(gRenderer, gmonkeyjumpandfallrightTexture, currentClip);
                        }
                    } else if (isFall){
                        if (isleft){
                            monkey.renderobject(gRenderer, gmonkeyjumpandfallleftTexture, currentClip);
                        } else {
                            monkey.renderobject(gRenderer, gmonkeyjumpandfallrightTexture, currentClip);
                        }
                    } else if (isrunning){
                        if (isleft){
                            monkey.renderobject(gRenderer, gmonkeyrunningleftTexture, currentClip);
                        } else {
                            monkey.renderobject(gRenderer, gmonkeyrunningrightTexture, currentClip);
                        }
                    } else{
                        if (isleft){
                            monkey.renderobject(gRenderer, gmonkeystaystandleftTexture, currentClip);
                        } else {
                            monkey.renderobject(gRenderer, gmonkeystaystandrightTexture, currentClip);
                        }
                    }

                    if(resumegame){
                        textCountDown.textSize(HanaleiFillfont72);
                        textCountDown.x = (SCREEN_WIDTH-textCountDown.textWidth)/2;
                        textCountDown.showText(HanaleiFillfont72,255, 70, 0, 255);
                    }

                    if (gamePause){
                        for (int i=1;i<5;i++){
                            Mix_Pause(i);
                        }
                        colorgamelow();
                        if (settingClicked){
                            bannergamepause=false;
                            setting();
                        } else {
                            if (!bannergamepause) {
                                banner[4].y -= banner[4].speed;
                                textGamePause.y -= textGamePause.speed;
                                if (banner[4].y <= SCREEN_HEIGHT /6) {
                                    bannergamepause = true;
                                }
                            }
                            banner[4].renderobject(gRenderer, gbannerTexture, NULL);
                            if (bannergamepause){

                                for (int i=5;i<9;i++){
                                    button[i].renderobject(gRenderer, gbuttonTexture, NULL);
                                }

                                textSystem[8].textSize(Boldonsefont14);
                                textSystem[8].x = button[6].x+(button[6].width-textSystem[8].textWidth)/2;
                                textSystem[8].y = button[6].y+(button[6].height-textSystem[8].textHeight)/2;
                                textSystem[8].showText(Boldonsefont14, 181, 101, 29,255);
                                textSystem[0].textSize(Boldonsefont14);
                                textSystem[0].x = button[7].x+(button[7].width-textSystem[0].textWidth)/2;
                                textSystem[0].y = button[7].y+(button[7].height-textSystem[0].textHeight)/2;
                                textSystem[0].showText(Boldonsefont14, 181, 101, 29,255);
                                textSystem[1].textSize(Boldonsefont14);
                                textSystem[1].x = button[8].x+(button[8].width-textSystem[1].textWidth)/2;
                                textSystem[1].y = button[8].y+(button[8].height-textSystem[1].textHeight)/2;
                                textSystem[1].showText(Boldonsefont14, 181, 101, 29,255);
                                textSystem[5].textSize(Boldonsefont14);
                                textSystem[5].x = button[5].x+(button[5].width-textSystem[5].textWidth)/2;
                                textSystem[5].y = button[5].y+(button[5].height-textSystem[5].textHeight)/2;
                                textSystem[5].showText(Boldonsefont14, 181, 101, 29,255);
                            }
                            textGamePause.textSize(HanaleiFillfont64);
                            textGamePause.x = (SCREEN_WIDTH-textGamePause.textWidth)/2;
                            textGamePause.showText(HanaleiFillfont64,255, 70, 0, 255);
                        }
                    } else if (loseCondition) {
                        textScoreEnd.display=textScore.display;
                        textScoreEnd.textSize(Boldonsefont24);
                        textScoreEnd.x = (SCREEN_WIDTH-textScoreEnd.textWidth)/2;
                        if (!bannerGameOver) {
                            banner[0].y -= banner[0].speed;
                            textGameOver.y -= textGameOver.speed;
                            if (banner[0].y <= SCREEN_HEIGHT /4) {
                                bannerGameOver = true;
                            }
                        }
                        banner[0].renderobject(gRenderer, gbannerTexture, NULL);
                        if(bannerGameOver){
                            saveHighScores();
                            if(newhighscoreappear){
                                textNewHighScore.textSize(Boldonsefont24);
                                textNewHighScore.x = (SCREEN_WIDTH-textNewHighScore.textWidth)/2;
                                textNewHighScore.showText(Boldonsefont24, 255,0,0,0);
                            }
                            for (int i=0;i<2;i++){
                                button[i].renderobject(gRenderer, gbuttonTexture, NULL);
                                textSystem[i].textSize(Boldonsefont14);
                                textSystem[i].x = button[i].x+(button[i].width-textSystem[i].textWidth)/2;
                                textSystem[i].y = button[i].y+(button[i].height-textSystem[i].textHeight)/2;
                                textSystem[i].showText(Boldonsefont14, 181, 101, 29,255);
                            }
                            textScoreEnd.showText(Boldonsefont24,255, 165,0,255);
                        }

                        textGameOver.textSize(HanaleiFillfont64);
                        textGameOver.x = (SCREEN_WIDTH-textGameOver.textWidth)/2;
                        textGameOver.showText(HanaleiFillfont64,255, 0, 0, 255);


                    } else{
                        textScore.display = "Score: "+to_string(score);
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

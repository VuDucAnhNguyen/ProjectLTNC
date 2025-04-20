#include <cstdlib>
#include <ctime>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "loadAudio.h"
#include "object.h"
#include "MonkeyAnimation.h"
#include "textDIsplay.h"
#include <fstream>
#include <map>


Uint32 startTime = SDL_GetTicks();
Uint32 beehiveTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;
Uint32 resumetime= SDL_GetTicks();



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
int score = 0;

string map1 = "edgeforest";
string map2 = "darkforest";
string map3 = "magicforest";
string mapChoose = " ";
bool buttonClicked = false;
bool playClicked = false;
bool bannerChooseMap = false;
bool settingClicked = false;
bool bannerSetting = false;
bool highscoresClicked = false;
bool bannerHighScores = false;
bool turnonMusic = false;
map <string, int> highscores;

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
    banana.x = rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64);
    banana.y = -50;
    beehive[0].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64);
    beehive[1].x = rand() % (SCREEN_WIDTH * 62 / 64 - 70 -142) + (SCREEN_WIDTH / 64);
    if (beehive[1].x>=beehive[0].x-71){
        beehive[1].x+=142;
    }
    beehive[0].y=-70;
    beehive[1].y=-70;
    banner[0].x = SCREEN_WIDTH / 6;
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
    textScoreEnd.y = SCREEN_HEIGHT+150;
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



void mainmenu (){
    mapChoose = " ";
    buttonClicked = false;
    playClicked = false;
    bannerChooseMap = false;
    settingClicked = false;
    bannerSetting = false;
    highscoresClicked = false;
    bannerHighScores =false;
    SDL_SetTextureColorMod(gbackgroundstartTexture, 255, 255, 255);
    SDL_SetTextureColorMod(gbuttonTexture, 255, 255, 255);
    banner[1].y = SCREEN_HEIGHT+10;
    textChooseMap.y = SCREEN_HEIGHT+50;
    banner[2].y = SCREEN_HEIGHT +10;
    banner[3].y = SCREEN_HEIGHT +10;
    textSetting.y = SCREEN_HEIGHT +50;
    textHighscores.y = SCREEN_HEIGHT +50;

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

void setting (){
    if (!bannerSetting) {
        banner[3].y -= banner[3].speed;
        textSetting.y -= textSetting.speed;
        if (banner[3].y <= SCREEN_HEIGHT /6) {
            bannerSetting = true;
        }
    }
    SDL_Rect banner3Rect=banner[3].rect();
    SDL_RenderCopy(gRenderer, gbannerTexture, NULL, &banner3Rect);

                            if (bannerSetting){
                                buttonback.y = SCREEN_HEIGHT-360;
                                SDL_Rect speakericonRect = speakericon.rect();
                                SDL_RenderCopy(gRenderer, gspeakericonTexture, NULL, &speakericonRect);
                                SDL_Rect musiciconRect = musicicon.rect();
                                SDL_RenderCopy(gRenderer, gmusiciconTexture, NULL, &musiciconRect);
                                SDL_Rect soundbarRect = soundbar.rect();
                                SDL_RenderCopy(gRenderer, gbarTexture, NULL, &soundbarRect);
                                SDL_Rect soundthumbRect = soundthumb.rect();
                                SDL_RenderCopy(gRenderer, gthumbTexture, NULL, &soundthumbRect);
                                SDL_Rect musicbarRect = musicbar.rect();
                                SDL_RenderCopy(gRenderer, gbarTexture, NULL, &musicbarRect);
                                SDL_Rect musicthumbRect = musicthumb.rect();
                                SDL_RenderCopy(gRenderer, gthumbTexture, NULL, &musicthumbRect);
                                SDL_Rect buttonbackRect = buttonback.rect();
                                SDL_RenderCopy(gRenderer, gbuttonbackTexture, NULL, &buttonbackRect);
                                textSystem[6].textSize(Boldonsefont14);
                                textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
                                textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
                                textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
                            }
                            textSetting.textSize(HanaleiFillfont64);
                            textSetting.x = (SCREEN_WIDTH-textSetting.textWidth)/2;
                            textSetting.showText(HanaleiFillfont64,255, 70, 0, 255);
}

string filltext (string s){
    int n=s.length();
    int indexdot=0;
    for (;indexdot<n;indexdot++){
        if(s[indexdot]==':'){
            break;
        }
    }
    string first;
    string mid;
    string last;
    for(int i=0;i<=indexdot;i++){
        first+=s[i];
    }
    for (int i=indexdot+1;i<n;i++){
        last+=s[i];
    }
    for (int i=0; i<50-n;i++){
        mid+=".";
    }
    return first+mid+last;
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

void updateHighScore(string mapChoose, int score) {
    if (score > highscores[mapChoose]) {
        highscores[mapChoose] = score;
    }
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
                                    mainmenu();
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
                                        mainmenu();
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
                                        mainmenu();
                                    }
                                }
                            }
                        }

                }

                if (!playinggame){
                    if (!turnonMusic){
                        Mix_PlayMusic(backgroundMusic, -1);
                        turnonMusic = true;
                    }
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderCopy(gRenderer, gbackgroundstartTexture, NULL, NULL);
                    for (int i=2;i<6;i++){
                        SDL_Rect buttonRect=button[i].rect();
                        SDL_RenderCopy(gRenderer, gbuttonTexture, NULL, &buttonRect);
                        textSystem[i].textSize(Boldonsefont14);
                        textSystem[i].x = button[i].x+(button[i].width-textSystem[i].textWidth)/2;
                        textSystem[i].y = button[i].y+(button[i].height-textSystem[i].textHeight)/2;
                        if (buttonClicked){
                            textSystem[i].showText(Boldonsefont14, 71, 40, 11,255);
                        } else {
                            textSystem[i].showText(Boldonsefont14, 181, 101, 29,255);
                        }
                    }

                    if (buttonClicked){
                        SDL_SetTextureColorMod(gbackgroundstartTexture, 100, 100, 100);
                        SDL_SetTextureColorMod(gbuttonTexture, 100, 100, 100);

                        if (playClicked){
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
                                buttonback.y = SCREEN_HEIGHT-220;
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
                        if (settingClicked){
                            setting();
                        }
                        if (highscoresClicked){
                            string highscoreofEdgeforest = "Edge Forest:"+to_string(highscores["edgeforest"]);
                            textEdgeforest.display=filltext(highscoreofEdgeforest);
                            string highscoreofDarkforest = "Dark Forest:"+to_string(highscores["darkforest"]);
                            textDarkforest.display=filltext(highscoreofDarkforest);
                            string highscoreofMagicforest = "Magic Forest:"+to_string(highscores["magicforest"]);
                            textMagicforest.display=filltext(highscoreofMagicforest);


                            if (!bannerHighScores) {
                                banner[2].y -= banner[2].speed;
                                textHighscores.y -= textHighscores.speed;
                                if (banner[2].y <= SCREEN_HEIGHT /6) {
                                    bannerHighScores = true;
                                }
                            }
                            SDL_Rect banner2Rect=banner[2].rect();
                            SDL_RenderCopy(gRenderer, gbannerTexture, NULL, &banner2Rect);

                            if (bannerHighScores){
                                textEdgeforest.showText(Boldonsefont14,164, 77, 63, 255 );
                                textDarkforest.showText(Boldonsefont14, 87, 84, 56, 255 );
                                textMagicforest.showText(Boldonsefont14,119, 62, 158, 255 );
                                buttonback.y = SCREEN_HEIGHT-310;


                                for (int i=0;i<3;i++){
                                    SDL_Rect buttonresetRect = buttonreset[i].rect();
                                    SDL_RenderCopy(gRenderer, gbuttonbackTexture, NULL, &buttonresetRect);
                                    textSystem[7].textSize(Boldonsefont14);
                                    textSystem[7].x = buttonreset[i].x+(buttonreset[i].width-textSystem[7].textWidth)/2;
                                    textSystem[7].y = buttonreset[i].y+(buttonreset[i].height-textSystem[7].textHeight)/2;
                                    textSystem[7].showText(Boldonsefont14, 181, 101, 29, 255);
                                }

                                SDL_Rect buttonbackRect = buttonback.rect();
                                SDL_RenderCopy(gRenderer, gbuttonbackTexture, NULL, &buttonbackRect);
                                textSystem[6].textSize(Boldonsefont14);
                                textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
                                textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
                                textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
                            }
                            textHighscores.textSize(HanaleiFillfont64);
                            textHighscores.x = (SCREEN_WIDTH-textHighscores.textWidth)/2;
                            textHighscores.showText(HanaleiFillfont64,255, 70, 0, 255);
                        }
                    }
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
                    if (banana.y<0&&monkey.speed<8){
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

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );



                if (loseCondition) {
                    updateHighScore(mapChoose, score);
                    for (int i=1;i<5;i++){
                        Mix_HaltChannel(i);
                    };
                    if (!losesound){
                        Mix_PlayChannel(5, loseSound, 0);
                        losesound=true;
                    }
                    colorgamelow();
                }
                if (mapChoose==map1){
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
                        SDL_Rect banner4Rect=banner[4].rect();
                        SDL_RenderCopy(gRenderer, gbannerTexture, NULL, &banner4Rect);
                        if (bannergamepause){

                            for (int i=5;i<9;i++){
                                SDL_Rect buttonRect=button[i].rect();
                                SDL_RenderCopy(gRenderer, gbuttonTexture, NULL, &buttonRect);
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
                        saveHighScores();
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

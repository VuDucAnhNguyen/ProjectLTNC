#include "mainmenu.h"
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "loadAudio.h"
#include "object.h"
#include "textDIsplay.h"
#include "highscorefile.h"


bool buttonClicked = false;
bool playClicked = false;
bool settingClicked = false;
bool highscoresClicked = false;
bool bannerChooseMap = false;
bool bannerHighScores = false;
bool bannerSetting = false;
bool turnonMusic = false;
string mapChoose = " ";


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

void resetmenu (){
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

void mapchoose(){
    if (!bannerChooseMap) {
        banner[1].y -= banner[1].speed;
        textChooseMap.y -= textChooseMap.speed;
        if (banner[1].y <= SCREEN_HEIGHT /6) {
            bannerChooseMap = true;
        }
    }
    banner[1].renderobject(gRenderer, gbannerTexture, NULL);
    if (bannerChooseMap){
        buttonback.y = SCREEN_HEIGHT-220;
        previewEdgeForest.renderobject(gRenderer, gpreviewedgeforestTexture, NULL);
        previewDarkForest.renderobject(gRenderer, gpreviewdarkforestTexture, NULL);
        previewMagicForest.renderobject(gRenderer, gpreviewmagicforestTexture, NULL);
        buttonback.renderobject(gRenderer, gbuttonbackTexture, NULL);
        textSystem[6].textSize(Boldonsefont14);
        textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
        textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
        textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
    }
    textChooseMap.textSize(HanaleiFillfont64);
    textChooseMap.x = (SCREEN_WIDTH-textChooseMap.textWidth)/2;
    textChooseMap.showText(HanaleiFillfont64,255, 70, 0, 255);
}

void setting(){
    if (!bannerSetting) {
        banner[3].y -= banner[3].speed;
        textSetting.y -= textSetting.speed;
        if (banner[3].y <= SCREEN_HEIGHT /6) {
            bannerSetting = true;
        }
    }
    banner[3].renderobject(gRenderer, gbannerTexture, NULL);

    if (bannerSetting){
    buttonback.y = SCREEN_HEIGHT-360;
        speakericon.renderobject(gRenderer, gspeakericonTexture, NULL);
        musicicon.renderobject(gRenderer, gmusiciconTexture, NULL);
        soundbar.renderobject(gRenderer, gbarTexture, NULL);
        soundthumb.renderobject(gRenderer, gthumbTexture, NULL);
        musicbar.renderobject(gRenderer, gbarTexture, NULL);
        musicthumb.renderobject(gRenderer, gthumbTexture, NULL);
        buttonback.renderobject(gRenderer, gbuttonbackTexture, NULL);
        textSystem[6].textSize(Boldonsefont14);
        textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
        textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
        textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
    }
    textSetting.textSize(HanaleiFillfont64);
    textSetting.x = (SCREEN_WIDTH-textSetting.textWidth)/2;
    textSetting.showText(HanaleiFillfont64,255, 70, 0, 255);
}

void highscore (){
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
    banner[2].renderobject(gRenderer, gbannerTexture, NULL);

    if (bannerHighScores){
        textEdgeforest.showText(Boldonsefont14,164, 77, 63, 255 );
        textDarkforest.showText(Boldonsefont14, 87, 84, 56, 255 );
        textMagicforest.showText(Boldonsefont14,119, 62, 158, 255 );
        buttonback.y = SCREEN_HEIGHT-310;
        for (int i=0;i<3;i++){
            buttonreset[i].renderobject(gRenderer, gbuttonbackTexture, NULL);
            textSystem[7].textSize(Boldonsefont14);
            textSystem[7].x = buttonreset[i].x+(buttonreset[i].width-textSystem[7].textWidth)/2;
            textSystem[7].y = buttonreset[i].y+(buttonreset[i].height-textSystem[7].textHeight)/2;
            textSystem[7].showText(Boldonsefont14, 181, 101, 29, 255);
        }
        buttonback.renderobject(gRenderer, gbuttonbackTexture, NULL);
        textSystem[6].textSize(Boldonsefont14);
        textSystem[6].x = buttonback.x+(buttonback.width-textSystem[6].textWidth)/2;
        textSystem[6].y = buttonback.y+(buttonback.height-textSystem[6].textHeight)/2;
        textSystem[6].showText(Boldonsefont14, 181, 101, 29, 255);
    }
    textHighscores.textSize(HanaleiFillfont64);
    textHighscores.x = (SCREEN_WIDTH-textHighscores.textWidth)/2;
    textHighscores.showText(HanaleiFillfont64,255, 70, 0, 255);
}

void mainmenumain (){
    if (!turnonMusic){
        Mix_PlayMusic(backgroundMusic, -1);
        turnonMusic = true;
    }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    SDL_RenderCopy(gRenderer, gbackgroundstartTexture, NULL, NULL);
    for (int i=2;i<6;i++){
        button[i].renderobject(gRenderer, gbuttonTexture, NULL);
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
            mapchoose();
        }
        if (settingClicked){
            setting();
        }
        if (highscoresClicked){
            highscore();
        }
    }
}

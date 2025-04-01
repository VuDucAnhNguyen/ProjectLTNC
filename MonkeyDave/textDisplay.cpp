#include "textDIsplay.h"
#include "Initclose.h"

int score = 0;

void renderText(SDL_Renderer* renderer, TTF_Font* gfont, string text, SDL_Color color, int x, int y) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(gfont, text.c_str(), color);
    if (textSurface == NULL) {
        cout << "Unable to render text surface! TTF Error: "<< TTF_GetError()<<endl;
    } else {

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != NULL) {

            SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);


            SDL_DestroyTexture(textTexture);
        }

        SDL_FreeSurface(textSurface);
    }
}

textDisplay::textDisplay(string _display, int _x, int _y, int _speed){
        display=_display;
        x=_x;
        y=_y;
        speed=_speed;
}

void textDisplay::textSize(TTF_Font* font) {
        TTF_SizeText(font, display.c_str(), &textWidth, &textHeight);
}

void textDisplay::showText (TTF_Font* font, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha){
        SDL_Color textColor = { r, g, b, alpha };
        renderText(gRenderer, font, display, textColor, x, y);
}

textDisplay textSystem[7]={
    textDisplay ("RETRY", 0, 0, 0),
    textDisplay ("MAIN MENU",0,0,0),
    textDisplay ("PLAY",0, 0, 0),
    textDisplay ("HIGH SCORE",0,0,0),
    textDisplay ("SETTING",0,0,0),
    textDisplay ("EXIT",0,0,0),
    textDisplay ("BACK",0,0,0)
};

textDisplay textScore("Score: "+to_string(score), 0, 10, 0);
textDisplay textGameOver("GAME OVER!", 0, SCREEN_HEIGHT+50, 10);
textDisplay textScoreEnd("Score: "+to_string(score), 0, SCREEN_HEIGHT+150, 0);
textDisplay textChooseMap("CHOOSE MAP", 0, SCREEN_HEIGHT+50, 15);


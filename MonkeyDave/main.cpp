#include <cstdlib>
#include <ctime>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
#include "object.h"
#include "MonkeyAnimation.h"


Uint32 startTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;

bool img10appear = false;




void renderText(SDL_Renderer*, TTF_Font*, string, SDL_Color , int , int );




struct textDisplay{
    string display;
    TTF_Font* font;
    int x, y, textWidth=0, textHeight=0, font_size, speed;

    textDisplay(string _display, TTF_Font* _font, int _x, int _y, int _font_size, int _speed){
        display=_display;
        font=_font;
        x=_x;
        y=_y;
        font_size=_font_size;
        speed=_speed;
    }

    void showtext (Uint8 r, Uint8 g, Uint8 b, Uint8 alpha){
        SDL_Color textColor = { r, g, b, alpha };
        renderText(gRenderer, font, display, textColor, x, y);
    }
};




void renderText(SDL_Renderer* renderer, TTF_Font* gfont, string text, SDL_Color color, int x, int y) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(gfont, text.c_str(), color);
    if (textSurface == NULL) {
        cout << "Unable to render text surface! TTF Error: "<< TTF_GetError()<<endl;;
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



bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x) &&
           (a.x < b.x + b.w) &&
           (a.y + a.h > b.y) &&
           (a.y < b.y + b.h);
}

int main( int argc, char* args[] ){
    int score = 0;
    bool bannerMovingUp =true;
    bool collisionWithLine = false;

    srand(time(0));

	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	else{
		if( !(loadFonts()&&loadTextures(gRenderer))){
			printf( "Failed to load media!\n" );
		}
		else{
			bool quit = false;

			SDL_Event e;

			textDisplay textscore("Score: "+to_string(score), Boldonsefont14, 0, 10, 14, 0);
            textDisplay textYoulose("YOU LOSE!", HanaleiFillfont48, 0, SCREEN_HEIGHT+150, 48, 10);
            TTF_SizeText(HanaleiFillfont48,"YOU LOSE!", &textYoulose.textWidth, &textYoulose.textHeight);
            textYoulose.x = (SCREEN_WIDTH-textYoulose.textWidth)/2;

			while( !quit ){
                Uint32 frameStart = SDL_GetTicks();
                Uint32 currentTime = SDL_GetTicks();

                if (isleft){
                    currentClip=&defaultMonkeyLeft;
                } else {
                    currentClip=&defaultMonkeyRight;
                }

                bool isOnPlatform = false;
                MonkeyFall(currentClip, monkey.y,isOnPlatform, isJump, isleft);

				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
					if (e.type == SDL_KEYDOWN) {
                        lastInputTime = currentTime;
                        isBlinking = false;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        isleft = true;
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        isleft = false;
                    }
                    if (e.key.keysym.sym == SDLK_UP&&isOnPlatform) {
                        isJump = true;
                    }
                    if (e.key.keysym.sym == SDLK_DOWN&&isOnPlatform){
                        fallthrough = true;
                    }
				}
				if (!isBlinking && currentTime - lastInputTime > 2000) {
                    isBlinking = true;
                    blinkStartTime = SDL_GetTicks();
                }
                if (isBlinking) {
                    Monkeyblink(currentClip, blinkStartTime, isBlinking, isleft);
                    lastInputTime=currentTime;
                }

                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_LEFT]) {
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

                if (isJump) {
                    MonkeyJump(currentClip, monkey.y, isJump, isleft);
                }


				if (banana.y+banana.height >= SCREEN_HEIGHT||monkey.y+monkey.height>=SCREEN_HEIGHT){
                    collisionWithLine = true;
				}

                if (!collisionWithLine){
                    if (SDL_GetTicks()-startTime>3000){
                        banana.falling();
                    }
                }

                if (checkCollision(monkey.rect(), banana.rect())) {
                    img10pts.x = banana.x;
                    img10pts.y = banana.y;

                    banana.y = -50;
                    banana.x = rand() % (rand()%(SCREEN_WIDTH*62/64-50))+(SCREEN_WIDTH /64);
                    score +=10;

                    textscore.display="Score: "+to_string(score);

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

				if (collisionWithLine) {
                    SDL_SetTextureColorMod(gbackgroundjungleTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbananaTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gplatformTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gmonkeystaystandrightTexture, 100, 100, 100);
                } else {
                    SDL_SetTextureColorMod(gbackgroundjungleTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(gbananaTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(gplatformTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(gmonkeystaystandrightTexture, 255, 255 ,255);
                }

                SDL_RenderCopy(gRenderer, gbackgroundjungleTexture, NULL, NULL);
                for (int i=0;i<7;i++){
                    SDL_Rect platformRect=platform[i].rect();
                    SDL_RenderCopy(gRenderer, gplatformTexture, NULL, &platformRect);
                }
                SDL_Rect bananaRect=banana.rect();
                SDL_RenderCopy(gRenderer, gbananaTexture, NULL, &bananaRect);
                SDL_Rect img10ptsRect=img10pts.rect();
                SDL_RenderCopy(gRenderer, g10ptsTexture, NULL, &img10ptsRect);

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


                if (collisionWithLine) {
                    if (bannerMovingUp) {
                        losebanner.y -= losebanner.speed;
                        textYoulose.y -= textYoulose.speed;
                        if (losebanner.y <= SCREEN_HEIGHT /8) {
                            bannerMovingUp = false;
                        }
                    }
                    SDL_Rect losebannerRect=losebanner.rect();
                    SDL_RenderCopy(gRenderer, glosebannerTexture, NULL, &losebannerRect);

                    textYoulose.showtext(255, 0, 0, 255);

                } else{
                    TTF_SizeText(Boldonsefont14,("Score: "+to_string(score)).c_str(), &textscore.textWidth, &textscore.textHeight);
                    textscore.x= SCREEN_WIDTH-textscore.textWidth;
                    textscore.showtext(255, 165, 0 ,255);
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

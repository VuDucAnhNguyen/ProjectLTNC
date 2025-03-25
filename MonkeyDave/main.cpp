#include <cstdlib>
#include <ctime>
#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"


Uint32 startTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;
bool img10appear = false;

void renderText(SDL_Renderer*, TTF_Font*, string, SDL_Color , int , int );


struct object{
    int x, y, width, height, speed;

    object(int _x,int _y,int _width,int _height,int _speed){
        x=_x;
        y=_y;
        width=_width;
        height=_height;
        speed=_speed;
    }

    SDL_Rect rect() {
    return SDL_Rect{ x, y, width, height };
    }

    void moving(){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_LEFT]){
                x-= speed;
            }
            else if (currentKeyStates[SDL_SCANCODE_RIGHT]){
                x+= speed;
            }

        if (x < 0) x = 0;
        if (x > SCREEN_WIDTH - 100) x = SCREEN_WIDTH - 100;
    }

    void falling(){
        y += speed;
        if (y > SCREEN_HEIGHT - 30 - height){
            y = SCREEN_HEIGHT - 30 - height;
        }
    }
};

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

void clearAll (){
    destroyFonts();
	destroyTextures();
    close();
}



bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x) &&
           (a.x < b.x + b.w) &&
           (a.y + a.h > b.y) &&
           (a.y < b.y + b.h);
}

int main( int argc, char* args[] ){
    object basket((SCREEN_WIDTH - 100) / 2, (SCREEN_HEIGHT - 100), 90, 65, 8);
    object banana(rand()%(SCREEN_WIDTH*62/64-50)+(SCREEN_WIDTH /64), -50, 50, 44, 7);
    object img10pts (-100, -100, 40, 40, 0);
    object losebanner(SCREEN_WIDTH/8, SCREEN_HEIGHT+10, SCREEN_WIDTH*3/4, SCREEN_HEIGHT*3/4, 10);
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
            textDisplay textYoulose("YOU LOSE!", HanaleiFillfont48, 0, SCREEN_HEIGHT+100, 48, 10);
            TTF_SizeText(HanaleiFillfont48,"YOU LOSE!", &textYoulose.textWidth, &textYoulose.textHeight);
            textYoulose.x = (SCREEN_WIDTH-textYoulose.textWidth)/2;

			while( !quit ){
                Uint32 frameStart = SDL_GetTicks();

				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
				}

				if (banana.y+banana.height >= SCREEN_HEIGHT-30){
                    collisionWithLine = true;
				}

                if (!collisionWithLine){
                basket.moving();
                    if (SDL_GetTicks()-startTime>3000){
                        banana.falling();
                    }
                }

                if (checkCollision(basket.rect(), banana.rect())) {
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
                    SDL_SetTextureColorMod(gbackgroundTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbananaTexture, 100, 100, 100);
                    SDL_SetTextureColorMod(gbasketTexture, 100, 100, 100);
                } else {
                    SDL_SetTextureColorMod(gbackgroundTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(gbananaTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(gbasketTexture, 255, 255, 255);
                }

                SDL_RenderCopy(gRenderer, gbackgroundTexture, NULL, NULL);
                SDL_Rect basketRect=basket.rect();
                SDL_RenderCopy(gRenderer, gbasketTexture, NULL, &basketRect);
                SDL_Rect bananaRect=banana.rect();
                SDL_RenderCopy(gRenderer, gbananaTexture, NULL, &bananaRect);
                SDL_Rect img10ptsRect=img10pts.rect();
                SDL_RenderCopy(gRenderer, g10ptsTexture, NULL, &img10ptsRect);


                if (collisionWithLine) {
                    SDL_Rect fillRect = { SCREEN_WIDTH /64, SCREEN_HEIGHT -30, SCREEN_WIDTH *62/64, SCREEN_HEIGHT /64 };
                    SDL_SetRenderDrawColor( gRenderer, 128, 0x00, 0x00, 0xFF );
                    SDL_RenderFillRect( gRenderer, &fillRect );

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
                    SDL_Rect fillRect = { SCREEN_WIDTH /64, SCREEN_HEIGHT -30, SCREEN_WIDTH *62/64, SCREEN_HEIGHT /64 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                    SDL_RenderFillRect( gRenderer, &fillRect );

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
	clearAll();

	return 0;
}

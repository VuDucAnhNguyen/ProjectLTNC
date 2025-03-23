#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const string imgbackground = "image_project/background.png";
const string imgbasket = "image_project/basket.png";
const string imgbanana = "image_project/banana.png";
const string img10pts = "image_project/10pts.png";
const string imglosebanner = "image_project/losebanner.png";
const string fontBoldonse = "font_project/Boldonse-Regular.ttf";

Uint32 startTime = SDL_GetTicks();
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
Uint32 img10collision = 0;
bool img10appear = false;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( string path );


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gbasketTexture = NULL;
SDL_Texture* gbackgroundTexture = NULL;
SDL_Texture* gbananaTexture=NULL;
SDL_Texture* g10ptsTexture=NULL;
SDL_Texture* glosebannerTexture=NULL;
TTF_Font* gfont =NULL;




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






bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! TTF Error: %s\n", TTF_GetError());
            success = false;
        }

		gWindow = SDL_CreateWindow( "SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	gbackgroundTexture = loadTexture(imgbackground);
    if (gbackgroundTexture == NULL){
        printf("Failed to load background texture!\n");
        success = false;
    }

    gbasketTexture = loadTexture(imgbasket);
    if (gbasketTexture == NULL){
        printf("Failed to load basket texture!\n");
        success = false;
    }

    gbananaTexture = loadTexture(imgbanana);
    if (gbananaTexture == NULL){
        printf("Failed to load banana texture!\n");
        success = false;
    }

    g10ptsTexture = loadTexture(img10pts);
    if (g10ptsTexture == NULL){
        printf("Failed to load 10pts texture!\n");
        success = false;
    }

    glosebannerTexture = loadTexture(imglosebanner);
    if (glosebannerTexture == NULL){
        printf("Failed to load losebanner texture!\n");
        success = false;
    }

    gfont = TTF_OpenFont(fontBoldonse.c_str(), 14);
    if (gfont == NULL) {
        cout << "Failed to load font! TTF Error: " << TTF_GetError() << endl;
        success = false;
    }

	return success;
}

void close(){
	SDL_DestroyTexture(gbackgroundTexture);
    SDL_DestroyTexture(gbasketTexture);
    SDL_DestroyTexture(gbananaTexture);
    SDL_DestroyTexture(g10ptsTexture);
    SDL_DestroyTexture(glosebannerTexture);
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	TTF_CloseFont(gfont);
	gWindow = NULL;
	gRenderer = NULL;
	gfont = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

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

SDL_Texture* loadTexture( string path ){

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} else{
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ){
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
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
		if( !loadMedia()){
			printf( "Failed to load media!\n" );
		}
		else{
			bool quit = false;

			SDL_Event e;

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
                        if (losebanner.y <= SCREEN_HEIGHT /8) {
                            bannerMovingUp = false;
                        }
                    }
                    SDL_Rect losebannerRect=losebanner.rect();
                    SDL_RenderCopy(gRenderer, glosebannerTexture, NULL, &losebannerRect);

                } else{
                    SDL_Rect fillRect = { SCREEN_WIDTH /64, SCREEN_HEIGHT -30, SCREEN_WIDTH *62/64, SCREEN_HEIGHT /64 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                    SDL_RenderFillRect( gRenderer, &fillRect );

                    SDL_Color textColor = { 255, 165, 0, 255 };
                    renderText(gRenderer, gfont, "Score: " + to_string(score), textColor, SCREEN_WIDTH - 125, 10);
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

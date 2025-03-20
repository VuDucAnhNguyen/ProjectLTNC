#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const string imgbackground = "image_project/background.png";
const string imgbasket = "image_project/basket.png";
const string imgbanana = "image_project/banana.png";

const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( string path );


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gbasketTexture = NULL;
SDL_Texture* gbackgroundTexture = NULL;
SDL_Texture* gbananaTexture=NULL;




struct object{
    int x, y, width, height, velocity, speed;

    object(int _x,int _y,int _width,int _height,int _velocity,int _speed){
        x=_x;
        y=_y;
        width=_width;
        height=_height;
        velocity= _velocity;
        speed=_speed;
    }

    SDL_Rect rect() {
    return SDL_Rect{ x, y, width, height };
    }

    void moving(){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_LEFT]){
                    velocity = -speed;
                }
                else if (currentKeyStates[SDL_SCANCODE_RIGHT]){
                    velocity = speed;
                }
                else{
                    velocity = 0;
                }
				x += velocity;

        if (x < 0) x = 0;
        if (x > SCREEN_WIDTH - 100) x = SCREEN_WIDTH - 100;
    }

    void falling(){
        y += speed;
        if (y > SCREEN_HEIGHT - 30 - height){
            y = SCREEN_HEIGHT - 30 - height;
            velocity = 0;
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
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
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

	return success;
}

void close(){
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
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

			object basket((SCREEN_WIDTH - 100) / 2, (SCREEN_HEIGHT - 100), 90, 65, 0, 7);
			object banana(rand()%(SCREEN_WIDTH*62/64-50)+(SCREEN_WIDTH /64), -50, 50, 44, 0 ,2);


			while( !quit ){
                Uint32 frameStart = SDL_GetTicks();

				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
				}

                basket.moving();
                banana.falling();

                if (checkCollision(basket.rect(), banana.rect())) {
                    banana.y = -50;
                    banana.x = rand() % (rand()%(SCREEN_WIDTH*62/64-50))+(SCREEN_WIDTH /64);

                }

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                SDL_RenderCopy(gRenderer, gbackgroundTexture, NULL, NULL);
                SDL_Rect basketRect=basket.rect();
                SDL_RenderCopy(gRenderer, gbasketTexture, NULL, &basketRect);
                SDL_Rect bananaRect=banana.rect();
                SDL_RenderCopy(gRenderer, gbananaTexture, NULL, &bananaRect);


                SDL_Rect fillRect = { SCREEN_WIDTH /64, SCREEN_HEIGHT -30, SCREEN_WIDTH *62/64, SCREEN_HEIGHT /64 };
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect( gRenderer, &fillRect );

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

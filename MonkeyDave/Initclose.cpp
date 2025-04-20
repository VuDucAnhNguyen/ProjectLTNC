#include "Initclose.h"
#include "loadFont.h"
#include "loadTexture.h"
using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            cout << "Warning: Linear texture filtering not enabled!" << endl;
        }

        gWindow = SDL_CreateWindow("MonkeyDave_game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                if (TTF_Init() == -1) {
                    cout << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << endl;
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
                    cout << "SDL_mixer could not initialize! TTF Error: "<< Mix_GetError() << endl;
                }
            }
        }
    }

    return success;
}

void close() {
    destroyFonts();
	destroyTextures();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


#include "loadTexture.h"

SDL_Texture* gbasketTexture = NULL;
SDL_Texture* gbackgroundTexture = NULL;
SDL_Texture* gbananaTexture=NULL;
SDL_Texture* g10ptsTexture=NULL;
SDL_Texture* glosebannerTexture=NULL;

SDL_Texture* loadTexture(const string &path, SDL_Renderer* renderer ){

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} else{
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL ){
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool loadTextures(SDL_Renderer* renderer) {
    bool success = true;

    gbackgroundTexture = loadTexture("image_project/background.png", renderer);
    if (gbackgroundTexture == nullptr) success = false;

    gbasketTexture = loadTexture("image_project/basket.png", renderer);
    if (gbasketTexture == nullptr) success = false;

    gbananaTexture = loadTexture("image_project/banana.png", renderer);
    if (gbananaTexture == nullptr) success = false;

    g10ptsTexture = loadTexture("image_project/10pts.png", renderer);
    if (g10ptsTexture == nullptr) success = false;

    glosebannerTexture = loadTexture("image_project/losebanner.png", renderer);
    if (glosebannerTexture == nullptr) success = false;

    return success;
}

void destroyTextures() {
    SDL_DestroyTexture(gbackgroundTexture);
    SDL_DestroyTexture(gbasketTexture);
    SDL_DestroyTexture(gbananaTexture);
    SDL_DestroyTexture(g10ptsTexture);
    SDL_DestroyTexture(glosebannerTexture);

    gbackgroundTexture = NULL;
    gbasketTexture = NULL;
    gbananaTexture = NULL;
    g10ptsTexture = NULL;
    glosebannerTexture = NULL;
}

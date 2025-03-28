#include "loadTexture.h"


SDL_Texture* gbackgroundjungleTexture = NULL;
SDL_Texture* gbananaTexture=NULL;
SDL_Texture* gplatformTexture=NULL;
SDL_Texture* g10ptsTexture=NULL;
SDL_Texture* glosebannerTexture=NULL;
SDL_Texture* gmonkeystaystandrightTexture=NULL;
SDL_Texture* gmonkeystaystandleftTexture=NULL;
SDL_Texture* gmonkeyrunningleftTexture=NULL;
SDL_Texture* gmonkeyrunningrightTexture=NULL;
SDL_Texture* gmonkeyjumpandfallrightTexture=NULL;
SDL_Texture* gmonkeyjumpandfallleftTexture=NULL;

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

    gbackgroundjungleTexture = loadTexture("image_project/backgroundjungle.png", renderer);
    if (gbackgroundjungleTexture == NULL) success = false;

    gbananaTexture = loadTexture("image_project/banana.png", renderer);
    if (gbananaTexture == NULL) success = false;

    g10ptsTexture = loadTexture("image_project/10pts.png", renderer);
    if (g10ptsTexture == NULL) success = false;

    glosebannerTexture = loadTexture("image_project/losebanner.png", renderer);
    if (glosebannerTexture == NULL) success = false;

    gplatformTexture = loadTexture("image_project/platform.png", renderer);
    if (gplatformTexture == NULL) success = false;

    gmonkeystaystandrightTexture = loadTexture("image_project/MonkeyStayStandRight.png", renderer);
    if (gmonkeystaystandrightTexture == NULL) success = false;

    gmonkeystaystandleftTexture = loadTexture("image_project/MonkeyStayStandLeft.png", renderer);
    if (gmonkeystaystandleftTexture == NULL) success = false;

    gmonkeyrunningrightTexture = loadTexture("image_project/MonkeyRunningRight.png", renderer);
    if (gmonkeyrunningrightTexture == NULL) success = false;

    gmonkeyrunningleftTexture = loadTexture("image_project/MonkeyRunningLeft.png", renderer);
    if (gmonkeyrunningleftTexture == NULL) success = false;

    gmonkeyjumpandfallrightTexture = loadTexture("image_project/MonkeyJumpRight.png", renderer);
    if (gmonkeyjumpandfallrightTexture == NULL) success = false;

    gmonkeyjumpandfallleftTexture = loadTexture("image_project/MonkeyJumpLeft.png", renderer);
    if (gmonkeyjumpandfallleftTexture == NULL) success = false;

    return success;
}

void destroyTextures() {
    SDL_DestroyTexture(gbackgroundjungleTexture);
    SDL_DestroyTexture(gbananaTexture);
    SDL_DestroyTexture(g10ptsTexture);
    SDL_DestroyTexture(glosebannerTexture);
    SDL_DestroyTexture(gmonkeystaystandrightTexture);
    SDL_DestroyTexture(gmonkeystaystandleftTexture);
    SDL_DestroyTexture(gmonkeyrunningrightTexture);
    SDL_DestroyTexture(gmonkeyrunningleftTexture);
    SDL_DestroyTexture(gmonkeyjumpandfallrightTexture);
    SDL_DestroyTexture(gmonkeyjumpandfallleftTexture);

    gbackgroundjungleTexture = NULL;
    gbananaTexture = NULL;
    g10ptsTexture = NULL;
    glosebannerTexture = NULL;
    gmonkeystaystandrightTexture = NULL;
    gmonkeystaystandleftTexture = NULL;
    gmonkeyrunningleftTexture = NULL;
    gmonkeyrunningrightTexture = NULL;
    gmonkeyjumpandfallrightTexture = NULL;
    gmonkeyjumpandfallleftTexture = NULL;
}


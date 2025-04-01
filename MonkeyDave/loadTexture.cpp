#include "loadTexture.h"

SDL_Texture* gbackgroundstartTexture = NULL;

SDL_Texture* gbackgroundedgeforestTexture = NULL;
SDL_Texture* gbackgrounddarkforestTexture = NULL;
SDL_Texture* gbackgroundmagicforestTexture = NULL;

SDL_Texture* gpreviewedgeforestTexture = NULL;
SDL_Texture* gpreviewdarkforestTexture = NULL;
SDL_Texture* gpreviewmagicforestTexture = NULL;

SDL_Texture* gplatformedgeforestTexture = NULL;
SDL_Texture* gplatformdarkforestTexture = NULL;
SDL_Texture* gplatformmagicforestTexture = NULL;

SDL_Texture* gbananaTexture=NULL;
SDL_Texture* g10ptsTexture=NULL;
SDL_Texture* gbannerTexture=NULL;
SDL_Texture* gbeehiveTexture=NULL;
SDL_Texture* gwarningTexture=NULL;

SDL_Texture* gmonkeystaystandrightTexture=NULL;
SDL_Texture* gmonkeystaystandleftTexture=NULL;
SDL_Texture* gmonkeyrunningleftTexture=NULL;
SDL_Texture* gmonkeyrunningrightTexture=NULL;
SDL_Texture* gmonkeyjumpandfallrightTexture=NULL;
SDL_Texture* gmonkeyjumpandfallleftTexture=NULL;

SDL_Texture* gbuttonTexture=NULL;
SDL_Texture* gbuttonbackTexture=NULL;



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

    gbackgroundstartTexture = loadTexture("image_project/backgroundstart.png", renderer);
    if (gbackgroundstartTexture == NULL) success = false;

    gbackgroundedgeforestTexture = loadTexture("image_project/backgroundEdgeForest.png", renderer);
    if (gbackgroundedgeforestTexture == NULL) success = false;

    gbackgrounddarkforestTexture = loadTexture("image_project/backgroundDarkForest.png", renderer);
    if (gbackgrounddarkforestTexture == NULL) success = false;

    gbackgroundmagicforestTexture = loadTexture("image_project/backgroundMagicForest.png", renderer);
    if (gbackgroundmagicforestTexture == NULL) success = false;



    gpreviewedgeforestTexture = loadTexture("image_project/previewEdgeForest.png", renderer);
    if (gpreviewedgeforestTexture == NULL) success = false;

    gpreviewdarkforestTexture = loadTexture("image_project/previewDarkForest.png", renderer);
    if (gpreviewdarkforestTexture == NULL) success = false;

    gpreviewmagicforestTexture = loadTexture("image_project/previewMagicForest.png", renderer);
    if (gpreviewmagicforestTexture == NULL) success = false;




    gplatformedgeforestTexture = loadTexture("image_project/platformEdgeForest.png", renderer);
    if (gplatformedgeforestTexture == NULL) success = false;

    gplatformdarkforestTexture = loadTexture("image_project/platformDarkForest.png", renderer);
    if (gplatformdarkforestTexture == NULL) success = false;

    gplatformmagicforestTexture = loadTexture("image_project/platformMagicForest.png", renderer);
    if (gplatformmagicforestTexture == NULL) success = false;




    gbananaTexture = loadTexture("image_project/banana.png", renderer);
    if (gbananaTexture == NULL) success = false;

    g10ptsTexture = loadTexture("image_project/10pts.png", renderer);
    if (g10ptsTexture == NULL) success = false;

    gbannerTexture = loadTexture("image_project/banner.png", renderer);
    if (gbannerTexture == NULL) success = false;

    gbeehiveTexture = loadTexture("image_project/beehive.png", renderer);
    if (gbeehiveTexture == NULL) success = false;

    gwarningTexture = loadTexture("image_project/warning.png", renderer);
    if (gwarningTexture == NULL) success = false;




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




    gbuttonTexture = loadTexture("image_project/button.png", renderer);
    if (gbuttonTexture == NULL) success = false;

    gbuttonbackTexture = loadTexture("image_project/button.png", renderer);
    if (gbuttonbackTexture == NULL) success = false;

    return success;
}

void destroyTextures() {
    SDL_DestroyTexture(gbackgroundstartTexture);

    SDL_DestroyTexture(gbackgroundedgeforestTexture);
    SDL_DestroyTexture(gbackgrounddarkforestTexture);
    SDL_DestroyTexture(gbackgroundmagicforestTexture);

    SDL_DestroyTexture(gpreviewedgeforestTexture);
    SDL_DestroyTexture(gpreviewdarkforestTexture);
    SDL_DestroyTexture(gpreviewmagicforestTexture);

    SDL_DestroyTexture(gplatformedgeforestTexture);
    SDL_DestroyTexture(gplatformdarkforestTexture);
    SDL_DestroyTexture(gplatformmagicforestTexture);

    SDL_DestroyTexture(gbananaTexture);
    SDL_DestroyTexture(g10ptsTexture);
    SDL_DestroyTexture(gbannerTexture);
    SDL_DestroyTexture(gbeehiveTexture);
    SDL_DestroyTexture(gwarningTexture);

    SDL_DestroyTexture(gmonkeystaystandrightTexture);
    SDL_DestroyTexture(gmonkeystaystandleftTexture);
    SDL_DestroyTexture(gmonkeyrunningrightTexture);
    SDL_DestroyTexture(gmonkeyrunningleftTexture);
    SDL_DestroyTexture(gmonkeyjumpandfallrightTexture);
    SDL_DestroyTexture(gmonkeyjumpandfallleftTexture);

    SDL_DestroyTexture(gbuttonTexture);
    SDL_DestroyTexture(gbuttonbackTexture);




    gbackgroundstartTexture = NULL;

    gbackgroundedgeforestTexture = NULL;
    gbackgrounddarkforestTexture = NULL;
    gbackgroundmagicforestTexture = NULL;

    gpreviewedgeforestTexture = NULL;
    gpreviewdarkforestTexture = NULL;
    gpreviewmagicforestTexture = NULL;

    gplatformedgeforestTexture = NULL;
    gplatformdarkforestTexture = NULL;
    gplatformmagicforestTexture = NULL;

    gbananaTexture = NULL;
    g10ptsTexture = NULL;
    gbannerTexture = NULL;
    gbeehiveTexture = NULL;
    gwarningTexture = NULL;

    gmonkeystaystandrightTexture = NULL;
    gmonkeystaystandleftTexture = NULL;
    gmonkeyrunningleftTexture = NULL;
    gmonkeyrunningrightTexture = NULL;
    gmonkeyjumpandfallrightTexture = NULL;
    gmonkeyjumpandfallleftTexture = NULL;

    gbuttonTexture = NULL;
    gbuttonbackTexture=NULL;
}


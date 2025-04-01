#ifndef loadTexture__H_
#define loadTexture__H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

extern SDL_Texture* gbackgroundstartTexture;

extern SDL_Texture* gbackgroundedgeforestTexture;
extern SDL_Texture* gbackgrounddarkforestTexture;
extern SDL_Texture* gbackgroundmagicforestTexture;

extern SDL_Texture* gpreviewedgeforestTexture;
extern SDL_Texture* gpreviewdarkforestTexture;
extern SDL_Texture* gpreviewmagicforestTexture;

extern SDL_Texture* gplatformedgeforestTexture;
extern SDL_Texture* gplatformdarkforestTexture;
extern SDL_Texture* gplatformmagicforestTexture;

extern SDL_Texture* gbananaTexture;
extern SDL_Texture* g10ptsTexture;
extern SDL_Texture* gbeehiveTexture;
extern SDL_Texture* gbannerTexture;
extern SDL_Texture* gwarningTexture;

extern SDL_Texture* gmonkeystaystandrightTexture;
extern SDL_Texture* gmonkeystaystandleftTexture;
extern SDL_Texture* gmonkeyrunningrightTexture;
extern SDL_Texture* gmonkeyrunningleftTexture;
extern SDL_Texture* gmonkeyjumpandfallrightTexture;
extern SDL_Texture* gmonkeyjumpandfallleftTexture;

extern SDL_Texture* gbuttonTexture;
extern SDL_Texture* gbuttonbackTexture;


bool loadTextures(SDL_Renderer* renderer);
void destroyTextures();
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);

#endif // loadTexture__H_



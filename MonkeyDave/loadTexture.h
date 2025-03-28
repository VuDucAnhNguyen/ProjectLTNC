#ifndef loadTexture__H_
#define loadTexture__H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;


extern SDL_Texture* gbackgroundjungleTexture;
extern SDL_Texture* gbananaTexture;
extern SDL_Texture* gplatformTexture;
extern SDL_Texture* g10ptsTexture;
extern SDL_Texture* glosebannerTexture;
extern SDL_Texture* gmonkeystaystandrightTexture;
extern SDL_Texture* gmonkeystaystandleftTexture;
extern SDL_Texture* gmonkeyrunningrightTexture;
extern SDL_Texture* gmonkeyrunningleftTexture;
extern SDL_Texture* gmonkeyjumpandfallrightTexture;
extern SDL_Texture* gmonkeyjumpandfallleftTexture;


bool loadTextures(SDL_Renderer* renderer);
void destroyTextures();
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);

#endif // loadTexture__H_



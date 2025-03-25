#ifndef loadTexture__H_
#define loadTexture__H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

extern SDL_Texture* gbasketTexture;
extern SDL_Texture* gbackgroundTexture;
extern SDL_Texture* gbananaTexture;
extern SDL_Texture* g10ptsTexture;
extern SDL_Texture* glosebannerTexture;

bool loadTextures(SDL_Renderer* renderer);
void destroyTextures();
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);

#endif // loadTexture__H_


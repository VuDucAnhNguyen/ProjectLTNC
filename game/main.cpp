#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";


int main(int argc, char* argv[])
{
    SDL_Window* window=NULL;

    SDL_Surface* screenSurface=NULL;

    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout << "ERROR: "<<SDL_GetError();
    } else {
        window =SDL_CreateWindow("SDL try", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window==NULL){
            cout <<"ERROR: "<<SDL_GetError();
        } else {
            screenSurface= SDL_GetWindowSurface(window);
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
            SDL_UpdateWindowSurface( window );
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    SDL_DestroyWindow( window);
    SDL_Quit();
    return 0;
}



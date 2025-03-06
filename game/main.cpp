#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

bool init ();
bool loadMedia ();
void close ();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* HelloWorld = NULL;

int main(int argc, char* argv[]){
    if (!init()){
        cout <<"Failed to initialize\n";
    } else {
        if( !loadMedia() )
        {
            cout<< "Failed to load media!\n" ;
        } else {
            SDL_BlitSurface( HelloWorld, NULL, screenSurface, NULL );
            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    close();
    return 0;
}

bool init (){
    bool success = true; //tra ve gia tri true khi code chay bth, false khi loi
    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout << "ERROR: "<<SDL_GetError();
        success=false;
    } else {
        window = SDL_CreateWindow("SDL try", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            cout <<"ERROR: "<<SDL_GetError();
            success=false;
        } else {
            screenSurface= SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadMedia (){
    bool success=true;
    HelloWorld=SDL_LoadBMP("image_project/preview.bmp");
    if (HelloWorld==NULL){
        cout <<"Unable load image "<<SDL_GetError();
        success=false;
    }
    return success;
}

void close (){
    SDL_FreeSurface(HelloWorld);
    HelloWorld=NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_Quit();
}

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

bool init ();
bool loadMedia ();
void close ();
SDL_Surface* loadSurface (string path );
SDL_Surface* gScreenSurface = NULL;

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* HelloWorld = NULL;
SDL_Surface* currentSurface=NULL;
SDL_Surface* KeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];


int main(int argc, char* argv[]){


    if (!init()){
        cout <<"Failed to initialize\n";
    } else if (!loadMedia()){
        cout << "Failed to load media!\n";
       } else {
        SDL_Event e;
        bool quit = false;
        while( quit == false ){
            while( SDL_PollEvent(&e)){
                if( e.type == SDL_QUIT ){
                    quit = true;
                } else if (SDL_KEYDOWN){
                    switch (e.key.keysym.sym){
                        case SDLK_UP:
                        currentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                        break;

                        case SDLK_DOWN:
                        currentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                        break;

                        case SDLK_LEFT:
                        currentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                        break;

                        case SDLK_RIGHT:
                        currentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        break;

                        default:
                        currentSurface = KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;
                    }
                    SDL_BlitSurface( currentSurface, NULL, screenSurface, NULL );
                    SDL_UpdateWindowSurface( window );
                }
            }
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
    KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT]=loadSurface("image_project/press.bmp");
    if( KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        cout << "Failed load default image";
        success = false;
    }

    KeyPressSurfaces[ KEY_PRESS_SURFACE_UP]=loadSurface("image_project/up.bmp");
    if( KeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        cout << "Failed load up image";
        success = false;
    }

    KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN]=loadSurface("image_project/down.bmp");
    if( KeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        cout << "Failed load down image";
        success = false;
    }

    KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT]=loadSurface("image_project/left.bmp");
    if( KeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        cout << "Failed load left image";
        success = false;
    }

    KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT]=loadSurface("image_project/right.bmp");
    if( KeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        cout << "Failed load right image";
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface (string path){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if ( loadedSurface==NULL){
        cout <<"Unable load image "<<SDL_GetError();
    }
    return loadedSurface;
}

void close (){
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(KeyPressSurfaces[i]);
        KeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_Quit();
}

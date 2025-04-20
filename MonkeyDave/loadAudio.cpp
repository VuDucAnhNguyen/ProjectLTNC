#include "loadAudio.h"
#include <iostream>
using namespace std;

Mix_Music* backgroundMusic = NULL;
Mix_Chunk* jumpSound = NULL;
Mix_Chunk* warningSound = NULL;
Mix_Chunk* rungrassSound = NULL;
Mix_Chunk* runwoodSound = NULL;
Mix_Chunk* loseSound = NULL;
Mix_Chunk* pointSound =NULL;

bool loadAudio() {
    bool success = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << endl;
        success = false;
    }

    backgroundMusic = Mix_LoadMUS("audio_project/background.mp3");
    if (backgroundMusic == NULL) {
        cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
        success = false;
    }


    jumpSound = Mix_LoadWAV("audio_project/jump_sound.wav");
    if (jumpSound == NULL) {
        cout << "Failed to load jump sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }

    warningSound = Mix_LoadWAV("audio_project/warning_sound.wav");
    if (warningSound == NULL) {
        cout << "Failed to load warning sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }

    rungrassSound = Mix_LoadWAV("audio_project/run_grass_sound.wav");
    if (rungrassSound == NULL) {
        cout << "Failed to load run grass sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }

    runwoodSound = Mix_LoadWAV("audio_project/run_wood_sound.wav");
    if (runwoodSound == NULL) {
        cout << "Failed to load run wood sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }

    pointSound = Mix_LoadWAV("audio_project/point_sound.wav");
    if (pointSound == NULL) {
        cout << "Failed to load point sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }

    loseSound = Mix_LoadWAV("audio_project/lose_sound.wav");
    if (loseSound == NULL) {
        cout << "Failed to load lose sound effect! Error: " << Mix_GetError() << endl;
        success = false;
    }


    return success;
}




void destroyAudio() {
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(warningSound);
    Mix_FreeChunk(pointSound);
    Mix_FreeChunk(rungrassSound);
    Mix_FreeChunk(runwoodSound);
    Mix_FreeChunk(loseSound);

    backgroundMusic=NULL;
    jumpSound=NULL;
    warningSound=NULL;
    pointSound=NULL;
    rungrassSound=NULL;
    runwoodSound=NULL;
    loseSound=NULL;
}


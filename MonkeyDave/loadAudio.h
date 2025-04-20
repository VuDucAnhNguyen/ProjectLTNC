#ifndef loadAudio__H_
#define loadAudio__H_

#include <SDL_mixer.h>

extern Mix_Music* backgroundMusic;
extern Mix_Chunk* jumpSound;
extern Mix_Chunk* warningSound;
extern Mix_Chunk* rungrassSound;
extern Mix_Chunk* runwoodSound;
extern Mix_Chunk* loseSound;
extern Mix_Chunk* pointSound;

bool loadAudio();

void destroyAudio();

#endif


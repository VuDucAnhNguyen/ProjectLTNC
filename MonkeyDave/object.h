#ifndef OBJECTS__H_
#define OBJECTS__H_

#include <SDL.h>

struct object {
    int x, y, width, height, speed;

    object(int _x, int _y, int _width, int _height, int _speed);

    bool clicked(int mouseX, int mouseY);

    SDL_Rect rect();

    void moving(int x1, int x2);

    void falling();
};


extern object banana;
extern object monkey;
extern object img10pts;
extern object beehive[2];
extern object warning[2];

extern object previewEdgeForest;
extern object previewDarkForest;
extern object previewMagicForest;

extern object platformEdgeForest[5];
extern object platformDarkForest[7];
extern object platformMagicForest[7];

extern object buttonback;
extern object musicbar;
extern object musicthumb;
extern object soundbar;
extern object soundthumb;
extern object musicicon;
extern object speakericon;

extern object banner[5];
extern object button[9];
extern object buttonreset[3];


#endif

#include "object.h"
#include "Initclose.h"

object::object(int _x, int _y, int _width, int _height, int _speed){
    x=_x;
    y=_y;
    width=_width;
    height=_height;
    speed=_speed;
}

SDL_Rect object::rect() {
    return SDL_Rect{x, y, width, height};
}

void object::renderobject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* crop){
    SDL_Rect objectRect=SDL_Rect{x, y, width, height};
    SDL_RenderCopy(renderer,texture,  crop, &objectRect);
}

bool object::clicked(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

void object::moving(int x1, int x2){
    x+=speed;
    if (x<x1||x>x2){
        speed= -speed;
    }
}

void object::falling() {
    y += speed;
    if (y > SCREEN_HEIGHT - height) {
        y = SCREEN_HEIGHT - height;
    }
}


object banana(rand() % (SCREEN_WIDTH * 62 / 64 - 50) + (SCREEN_WIDTH / 64), -50, 50, 44, 3);
object img10pts(-100, -100, 40, 40, 0);
object monkey((SCREEN_WIDTH - 100) / 2, SCREEN_HEIGHT - 335, 100, 100, 6);
object beehive[2]={
    object (rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64), -70, 70, 70, 7),
    object (rand() % (SCREEN_WIDTH * 62 / 64 - 70) + (SCREEN_WIDTH / 64), -70, 70, 70, 7),
};
object warning[2]={
    object (0, 0, 70, 70, 0),
    object (0, 0, 70, 70, 0),
};

object previewEdgeForest ((SCREEN_WIDTH-232)/2-252 ,300 , 232, 174, 0);
object previewDarkForest((SCREEN_WIDTH-232)/2, 300, 232, 174, 0);
object previewMagicForest((SCREEN_WIDTH-232)/2 +252 ,300 , 232, 174, 0);

object banner[5]={
    object (SCREEN_WIDTH / 6, SCREEN_HEIGHT + 10, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT/2, 10), //gameover
    object (SCREEN_WIDTH / 48, SCREEN_HEIGHT + 10, SCREEN_WIDTH * 23/24, SCREEN_HEIGHT*11/15, 15),  //choosemap
    object (SCREEN_WIDTH / 6, SCREEN_HEIGHT + 10, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT*29/50, 15), //highscore
    object (SCREEN_WIDTH / 6, SCREEN_HEIGHT + 10, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT/2, 15),  //setting
    object (SCREEN_WIDTH /4, SCREEN_HEIGHT + 10, SCREEN_WIDTH /2, SCREEN_HEIGHT*3/4, 15) //gamepause
};

object platformEdgeForest[5] = {
    object((SCREEN_WIDTH-350)/2, SCREEN_HEIGHT-235, 350, 40, 0),
    object(0, SCREEN_HEIGHT-350, 350, 40, 0),
    object(SCREEN_WIDTH-350, SCREEN_HEIGHT-350, 350, 40, 0),
    object(0, SCREEN_HEIGHT-125, 350, 40, 0),
    object(SCREEN_WIDTH-350, SCREEN_HEIGHT-125, 350, 40, 0)
};

object platformDarkForest[7] = {
    object((SCREEN_WIDTH-400)/2, SCREEN_HEIGHT-225, 400, 40, 0),
    object(0, SCREEN_HEIGHT-350, 400, 40, 0),
    object(SCREEN_WIDTH-400, SCREEN_HEIGHT-350, 400, 40, 0),
    object(100, SCREEN_HEIGHT-485, 225, 40, 0),
    object(SCREEN_WIDTH-350, SCREEN_HEIGHT-485, 225, 40, 0),
    object(125, SCREEN_HEIGHT-125, 125, 40, 0),
    object(SCREEN_WIDTH-275, SCREEN_HEIGHT-125, 125, 40, 0)
};

object platformMagicForest[7] = {
    object((SCREEN_WIDTH-300)/2, SCREEN_HEIGHT-225, 300, 40, 0),
    object(0, SCREEN_HEIGHT-485, 200, 40, 0),
    object(SCREEN_WIDTH-200, SCREEN_HEIGHT-485, 200, 40, 0),
    object(0, SCREEN_HEIGHT-350, 150, 40, -2),
    object(SCREEN_WIDTH-150, SCREEN_HEIGHT-350, 150, 40, 2),
    object(180, SCREEN_HEIGHT-125, 150, 40, 2),
    object(SCREEN_WIDTH-330, SCREEN_HEIGHT-125, 150, 40, -2)
};

object button[9] = {
    object(SCREEN_WIDTH/2-170-10,SCREEN_HEIGHT-290, 170, 53, 0), //retry when lose
    object(SCREEN_WIDTH/2+10,SCREEN_HEIGHT-290,170,53,0), //main menu when lose
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-350,200,62,0), //play
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-280,200,62,0),//highscore
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-140,200,62,0),  //exit
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-210,200,62,0), //setting
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-420,200,62,0), //resume
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-350,200,62,0), //retry
    object((SCREEN_WIDTH-200)/2,SCREEN_HEIGHT-280,200,62,0)  //main menu
};

object buttonback((SCREEN_WIDTH-200)/2,0,200,62,0);

object buttonreset[3] = {
    object(580,250,150,46,0), //edgeforest
    object(580,300,150,46,0), //darkforest
    object(580,350,150,46,0), //magicforest
};

object musicbar(SCREEN_WIDTH/2-95,300,250, 40, 0);
object musicthumb(SCREEN_WIDTH/2+10, 300, 40,40, 0);
object soundbar(SCREEN_WIDTH/2-95,250,250, 40, 0);
object soundthumb(SCREEN_WIDTH/2+10, 250, 40,40, 0);
object musicicon (SCREEN_WIDTH/2-155,300, 40, 40, 0);
object speakericon(SCREEN_WIDTH/2-155,250, 40, 40, 0);


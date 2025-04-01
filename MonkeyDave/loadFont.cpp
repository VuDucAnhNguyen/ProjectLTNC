#include "loadFont.h"
#include <iostream>

TTF_Font* Boldonsefont14 =NULL;
TTF_Font* HanaleiFillfont64 =NULL;
TTF_Font* Boldonsefont24 =NULL;
using namespace std;

bool loadFonts() {
    bool success = true;

    Boldonsefont14 = TTF_OpenFont("font_project/Boldonse-Regular.ttf", 14);
    if (Boldonsefont14 == NULL) {
        cout << "Failed to load Boldonse14 font! TTF Error: " << TTF_GetError() <<endl;
        success = false;
    }

    HanaleiFillfont64 = TTF_OpenFont("font_project/HanaleiFill-Regular.ttf", 64);
    if (HanaleiFillfont64 == NULL) {
        cout << "Failed to load HanaleiFill48 font! TTF Error: " << TTF_GetError() <<endl;
        success = false;
    }

    Boldonsefont24 = TTF_OpenFont("font_project/Boldonse-Regular.ttf", 24);
    if (Boldonsefont24 == NULL) {
        cout << "Failed to load Boldonse24 font! TTF Error: " << TTF_GetError() <<endl;
        success = false;
    }

    return success;
}

void destroyFonts() {
    TTF_CloseFont(Boldonsefont14);
	TTF_CloseFont(HanaleiFillfont64);
    TTF_CloseFont(Boldonsefont24);

    Boldonsefont14 = NULL;
	HanaleiFillfont64 = NULL;
	Boldonsefont24 =NULL;
}


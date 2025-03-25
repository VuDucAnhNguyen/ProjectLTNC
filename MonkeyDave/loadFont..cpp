#include "loadFont.h"
#include <iostream>

TTF_Font* Boldonsefont14 =NULL;
TTF_Font* HanaleiFillfont48 =NULL;

bool loadFonts() {
    bool success = true;

    Boldonsefont14 = TTF_OpenFont("font_project/Boldonse-Regular.ttf", 14);
    if (Boldonsefont14 == NULL) {
        std::cout << "Failed to load Boldonse14 font! TTF Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    HanaleiFillfont48 = TTF_OpenFont("font_project/HanaleiFill-Regular.ttf", 48);
    if (HanaleiFillfont48 == NULL) {
        std::cout << "Failed to load HanaleiFill48 font! TTF Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    return success;
}

void destroyFonts() {
    TTF_CloseFont(Boldonsefont14);
	TTF_CloseFont(HanaleiFillfont48);

    Boldonsefont14 = NULL;
	HanaleiFillfont48 = NULL;
}

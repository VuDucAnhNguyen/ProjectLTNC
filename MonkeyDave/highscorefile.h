#ifndef HIGHSCOREFILE__H_
#define HIGHSCOREFILE__H_

#include <map>
#include <string>
using namespace std;

extern map <string, int> highscores;

void loadHighScores ();

void saveHighScores ();

#endif

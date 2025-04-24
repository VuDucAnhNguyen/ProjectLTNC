#include "highscorefile.h"
#include <map>
#include <fstream>

map <string, int> highscores;

void loadHighScores() {
    ifstream file("high_scores.txt");
    if (!file.is_open()) return;

    string mapgame;
    int score;
    while (file >> mapgame >> score) {
        highscores[mapgame] = score;
    }

    file.close();
}

void saveHighScores() {
    ofstream file("high_scores.txt");
    if (!file.is_open()) return;

    for (auto it = highscores.begin(); it != highscores.end(); ++it) {
    file << it->first << " " << it->second <<endl;
    }

    file.close();
}

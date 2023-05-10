#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "Game.h"


struct HighScore {
    int score;
    int level;
};

// Custom comparator for sorting the high scores in descending order
bool compareHighScores(const HighScore& a, const HighScore& b);

void insertHighScore(int score, int level);


class Menu{
public:
    int lifes;
    int score;
    int level;
    bool isGameStarted;
    bool isGameEnded, isGamePaused; 
    int gameStatus;

    //add menu attributes here
    Texture texture;
    Sprite menuBackground;
    Text text1, text2, text3, text4, text5;
    vector<Text*> highsScores;
    
    Font font;
    Menu();

    void display_menu();

    bool display_start_menu(RenderWindow& window);
    void display_endscreen_menu(RenderWindow& window);

    void display_game_win(RenderWindow& window);

   /* void display_pause_menu(RenderWindow& window)
    {
	}*/


    void display_instructions_menu(RenderWindow& window);

    void display_high_score_menu(RenderWindow& window);




};

#pragma once
#include <fstream>
#include "game.h"
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
    
    Font font;
    Menu()
    {
    //constructors body
        lifes = 3;
        score = 0;
        level = 1;
        isGameStarted = false;
        gameStatus = 0;
        isGamePaused = isGameEnded = false;

        if (!texture.loadFromFile("img/background_1.png")) {
            std::cout << "Failed to load menu background image" << std::endl;
        }
        menuBackground.setColor(Color(255, 255, 255, 255));
        menuBackground.setTexture(texture);
        menuBackground.setScale(2, 1.5);

        text1.setFillColor(Color::White);
        text2.setFillColor(Color::White);

        if (!font.loadFromFile("Sofia-Regular.otf"))
        {
            std::cout << "Error loading font" << std::endl;
        }


        text1.setFont(font);
        text2.setFont(font);
        text1.setString("Space Shooter");
        text1.setCharacterSize(100);
        text1.setPosition(Vector2f(100, 50));
        text2.setString("Press Space to start the game");
        text2.setCharacterSize(35);
        text2.setPosition(Vector2f(150, 300));
        text3.setFont(font);
        //text3.setString("Game Over");
        text3.setCharacterSize(35);
        text3.setPosition(Vector2f(100, 50));
        text4.setFont(font);
        //text4.setString("Press Space to start the game");
        text4.setCharacterSize(35);
        text4.setPosition(Vector2f(150, 300));
        text5.setFont(font);
        /*text5.setString("Press Esc to exit the game");*/
        text5.setCharacterSize(35);
        text5.setPosition(Vector2f(150, 400));


    }

    void display_menu()

    {
        srand(time(0));
        Game g; //create a game object
        //g.make_enemies();
        RenderWindow window(VideoMode(780, 780), "OOP-Project, Spring-2023");

        /*Sprite menuBackground(texture);
        Text text1, text2;
        Font font;*/

       

        while(!isGameEnded){
            
            window.clear();
            if (isGameStarted && lifes > 0) {    //start game
                g.level = level;
                g.lifes = lifes;
                //g.level = 3;

                g.make_enemies();
				gameStatus = g.start_game(window, score);
                if (gameStatus == 1) {
                    level++;    //next level
                }
                else if(gameStatus == 0)
                    lifes--;    //lost a life
                else if(gameStatus == -1)
                    isGameStarted = false;
			}
			else if(isGamePaused) { //game paused
            	display_pause_menu(window);
            }
            else if(gameStatus == -1 || lifes == 0) {  //game ended
                display_endscreen_menu(window);
                isGameEnded = true;
            }
			else {                  //display menu
            	isGameStarted = display_start_menu(window);
            }

            
            
         
        }
    //display menu screen here
            
    // add functionality of all the menu options here

    //if Start game option is chosen 
    
        



    }

    bool display_start_menu(RenderWindow& window) {
        
        text3.setString("Press I for Instructions");
        text4.setString("Press H for High Scores");

        text3.setPosition(Vector2f(150, 400));
        text4.setPosition(Vector2f(150, 500));

        Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                    // Start game if space is pressed
                    return true;
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::I) {
					//display instructions
					display_instructions_menu(window);
				}
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::H) {
                    display_high_score_menu(window);
                    
                    window.clear(Color::Black);
                }
                if (event.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game 
            }
            window.clear(Color::Black);
            window.draw(menuBackground);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.display();
        }
        window.clear(Color::Black);
    }
    void display_endscreen_menu(RenderWindow& window)
    {
        //display end screen menu here
        //writing score and level on a txt file

        text1.setString("Game Over");
        text2.setString("Press Any key to exit the game");

        Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed) {
					window.close();
				}
                if (event.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game 
            }
            window.clear(Color::Black);
            window.draw(menuBackground);
            window.draw(text1);
            window.draw(text2);
            window.display();
        }


        std::ofstream file;
        file.open("highscore.txt", std::ios::app);
        file << "Score: " << score << " Level: " << level << std::endl;
        file.close();



    }

    void display_game_win(RenderWindow& window)
    {//display game win screen here

	}

    void display_pause_menu(RenderWindow& window)
    {
	}


    void display_instructions_menu(RenderWindow& window) {
        text1.setString("Instructions");
        text2.setString("Press BackSpace to go back");
        text3.setString("Press Space to shoot");
        text4.setString("Press Left, Right, Up and Down arrow keys to move");

        text2.setPosition(Vector2f(150, 200));
        text3.setPosition(Vector2f(150, 300));
        text4.setPosition(Vector2f(50, 350));

        while (window.isOpen()) {
			Event event2;
            while (window.pollEvent(event2)) {
                if (event2.type == Event::KeyPressed || event2.key.code == Keyboard::BackSpace) {
					//backspace to return
					return;
				}
				if (event2.type == Event::Closed) // If cross/close is clicked/pressed
					window.close(); //close the game 
			}
			window.clear(Color::Black);
			window.draw(menuBackground);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.display();
		}
        window.clear(Color::Black);
	}

    void display_high_score_menu(RenderWindow& window) {
        //reading high score from txt file and displaying it on the screen
        text1.setString("High Score");
        text2.setString("Press BackSpace to go back now");
        std::ifstream file;
        file.open("highscore.txt");
        std::string line;
        int i = 0;
        while (std::getline(file, line)) {
			text3.setString(line);
			text3.setPosition(Vector2f(150, 150 + i * 50));
			window.draw(text3);
			i++;
		}
        file.close();
        Event event2;
        while (window.isOpen()) {
            while (window.pollEvent(event2)) {
                if (event2.type == Event::KeyPressed || event2.key.code == Keyboard::BackSpace) {
                    return;
                }
                if (event2.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game
            }
            window.clear(Color::Black);
            window.draw(menuBackground);
            window.draw(text1);
            window.draw(text2);
            window.display();
        }
        window.clear(Color::Black);
	}



};

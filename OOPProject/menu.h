
#include "game.h"
class Menu{
public:
    int lifes;
    int score;
    int level;
    bool isGameStarted;
    bool isGameEnded, isGamePaused;

    //add menu attributes here
    Texture texture;
    Sprite menuBackground;
    Text text1, text2;
    Font font;
    Menu()
    {
    //constructors body
        lifes = 3;
        score = 0;
        level = 1;
        isGameStarted = false;
        isGamePaused = isGameEnded = false;

        texture.loadFromFile("img/background_1.png");
        menuBackground.setTexture(texture);
        menuBackground.setScale(2, 1.5);

        text1.setFont(font);
        text2.setFont(font);
        text1.setString("Space Shooter");
        text1.setCharacterSize(100);
        text1.setPosition(340, 50);
        text2.setString("Press Space to start the game");
        text2.setCharacterSize(50);
        text2.setPosition(250, 300);

    }

    void display_menu()

    {
        Game g; //create a game object
        RenderWindow window(VideoMode(780, 780), "OOP-Project, Spring-2023");

        /*Sprite menuBackground(texture);
        Text text1, text2;
        Font font;*/

       

        while (window.isOpen()) {
            
            window.clear();
            if (isGameStarted) {    //start game
				isGameEnded = g.start_game(window);
                isGameStarted = false;
			}
			else if(isGamePaused) { //game paused
            	display_pause_menu(window);
            }
            else if(isGameEnded) {  //game ended
                display_endscreen_menu(window);
            }
			else {                  //display menu
            	isGameStarted = display_start_menu(window);
            }

            window.clear();
            
            window.display();
        }
    //display menu screen here
            
    // add functionality of all the menu options here

    //if Start game option is chosen 
    
        



    }

    bool display_start_menu(RenderWindow& window) {
        
        if (!texture.loadFromFile("img/background_1.png")) {
            std::cout << "Failed to load menu background image" << std::endl;
        }
        menuBackground.setTexture(texture);
        menuBackground.setScale(2, 1.5);

        Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                    // Start game if space is pressed
                    return true;
                }
            }

            window.draw(menuBackground);
            window.draw(text1);
            window.draw(text2);
        }

    }
    void display_endscreen_menu(RenderWindow& window)
    {

    }

    void display_game_win(RenderWindow& window)
    {
	}

    void display_pause_menu(RenderWindow& window)
    {
	}


    void display_instructions_menu(RenderWindow& window) {
	}

    void display_high_score_menu(RenderWindow& window) {
	}



};

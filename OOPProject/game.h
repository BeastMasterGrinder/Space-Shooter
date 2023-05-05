

#include "player.h"
#include "PowerUp.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Player* p; //player 
    // add other game attributes

    PowerUp powerUp;

    Game()
    {
        p=new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background1.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);

    }
    bool start_game(RenderWindow& window)
    {
        srand(time(0));
        //RenderWindow window(VideoMode(780, 780), title);//to change these chang it in PowerUp.h too
        Clock clock;
        float timer=0;
    
        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds(); 
            float ptime = clock.restart().asSeconds();

            clock.restart();
            timer += time;  
            //timer for shooting
            p->timer += ptime;
            //cout<<timer<<endl; 
 	    Event e;
            while (window.pollEvent(e))
            {  
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game                        	    
            }
          
	    //if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
     //           p->move("l");    // Player will move to left
	    //else if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
     //           p->move("r");  //player will move to right
	    //else if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
     //           p->move("u");    //playet will move upwards
	    //else if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
     //           p->move("d");  //player will move downwards
     //   else if(Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
     //           p->move("lu");
     //   else if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
     //            p->move("ru");
	    //else if(Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down))
	    //		p->move("ld");
	    //else if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down))
	    //		p->move("rd");
	    //else if(Keyboard::isKeyPressed(Keyboard::Space))
	    //		p->fire();
	    //else if(Keyboard::isKeyPressed(Keyboard::Escape))
	    //		window.close();
            float delta_x = 0, delta_y = 0;

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                delta_x = -1; //move the player left
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                delta_x = 1; //move the player right
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                delta_y = -1; //move the player up
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                delta_y = 1; //move the player down
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) || p->powerup)
				p->shoot();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            // check for diagonal movement
            if (delta_x != 0 && delta_y != 0) {
                if (delta_x < 0 && delta_y < 0) {
                    p->move("lu");
                }
                else if (delta_x > 0 && delta_y < 0) {
                    p->move("ru");
                }
                else if (delta_x < 0 && delta_y > 0) {
                    p->move("ld");
                }
                else if (delta_x > 0 && delta_y > 0) {
                    p->move("rd");
                }
            }
            else if (delta_x != 0) {
                if (delta_x < 0) {
                    p->move("l");
                }
                else {
                    p->move("r");
                }
            }
            else if (delta_y != 0) {
                if (delta_y < 0) {
                    p->move("u");
                }
                else {
                    p->move("d");
                }
            }

        //checking for power up
            if (p->sprite.getGlobalBounds().intersects(powerUp.sprite.getGlobalBounds())) {
                powerUp.activate(timer);
                
                cout << "POWERED UP!!\n";
            }
            /*cout<<"StartTime:"<<powerUp.startTime << endl;
            cout << "TimeNow:" << timer << endl;*/
            p->powerup = powerUp.isActive();
	    ////////////////////////////////////////////////
	    /////  Call your functions here            ////
	    //////////////////////////////////////////////
            for (int i = 0; i < p->bullets.size(); i++) {
                p->bullets[i].move();
                window.draw(p->bullets[i].sprite);
            }
            /*if (timer > 20) {
				timer = 0;
				int x = rand() % 780;
				int y = rand() % 780;
				enemy.push_back(Enemy(x, y));
			}
            for (int i = 0; i < enemy.size(); i++) {
				enemy[i].move();
				window.draw(enemy[i]);
			}
            for (int i = 0; i < enemy.size(); i++) {
                for (int j = 0; j < player.bullets.size(); j++) {
                    if (enemy[i].getGlobalBounds().intersects(player.bullets[j].getGlobalBounds())) {
						enemy.erase(enemy.begin() + i);
						player.bullets.erase(player.bullets.begin() + j);
					}
				}
			}
            for (int i = 0; i < enemy.size(); i++) {
                if (enemy[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
					enemy.erase(enemy.begin() + i);
					player.health--;
				}
			}
            if (player.health <= 0) {
				window.close();
			}*/


	    window.clear(Color::Black); //clears the screen
	    window.draw(background);  // setting background
	    window.draw(p->sprite);   // setting player on screen
        for (int i = 0; i < p->bullets.size(); i++) {
            p->bullets[i].move();
            window.draw(p->bullets[i].sprite);
        }

        powerUp.update(timer);
        window.draw(powerUp.sprite);

	    window.display();  //Displying all the sprites
        }

        return true;

    }


};


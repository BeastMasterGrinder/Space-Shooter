#pragma once

#include "Enemy.h"
#include "player.h"
#include "PowerUp.h"
#include "Danger.h"
#include "Lives.h"

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;


class Game
{
    int fireused = 1;
    float fireInitiat_time;
public:
    Text Life, Score, Level, time_string;
    Font font;

    Sprite background; //Game background sprite
    Texture bg_texture;
    Player* p; //player 
    // add other game attributes

    int level;
    int lifes;
    PowerUp powerUp;
    vector<Enemy*> enemies;
    Danger danger;
    Lives_power lives_power;
    
    int num_enemies;


    Game()
    {
        fireused = 1;
        fireInitiat_time = 0.0f;
        level = 1;
        p=new Player("img/player_ship.png");
        
        bg_texture.loadFromFile("img/background1.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);

        
        if (!font.loadFromFile("Sofia-Regular.otf"))
        {
            std::cout << "Error loading font" << std::endl;
        }

        Score.setFont(font);
        Score.setString("Score: 0");
        Score.setCharacterSize(35);
        Score.setPosition(Vector2f(10, 10));
        Life.setFont(font);
        Life.setString("Lifes: 3");
        Life.setCharacterSize(35);
        Life.setPosition(Vector2f(200, 10));
        Level.setFont(font);
        Level.setString("Level: 1");
        Level.setCharacterSize(35);
        Level.setPosition(Vector2f(400, 10));
        time_string.setFont(font);
        time_string.setString("Time: 0");
        time_string.setCharacterSize(35);
        time_string.setPosition(Vector2f(600, 10));


        Score.setFillColor(Color::White);
        Life.setFillColor(Color::White);
        Level.setFillColor(Color::White);
        time_string.setFillColor(Color::White);
        /*text1.setFont(font);
        text2.setFont(font);
        text1.setString("Space Shooter");
        text1.setCharacterSize(100);
        text1.setPosition(Vector2f(100, 50));*/
    }

    void make_enemies() {
        if (level == 1) { //make 3 enemies of alpha 2 enemies of beta and 1 of gamma
            enemies.push_back(new Enemy(Enemy::enemytype::Alpha, 1));
            enemies.push_back(new Enemy(Enemy::enemytype::Alpha, 1));
            enemies.push_back(new Enemy(Enemy::enemytype::Alpha, 1));
            enemies.push_back(new Enemy(Enemy::enemytype::Beta, 1));
            enemies.push_back(new Enemy(Enemy::enemytype::Beta, 1));
            enemies.push_back(new Enemy(Enemy::enemytype::Gamma, 1));
            //positioning enemies: gamma in the middle, alpha on the sides and beta in between
            enemies[0]->sprite.setPosition(300, 100);
            enemies[1]->sprite.setPosition(100, 100);
            enemies[2]->sprite.setPosition(500, 100);
            enemies[3]->sprite.setPosition(200, 200);
            enemies[4]->sprite.setPosition(400, 200);
            enemies[5]->sprite.setPosition(300, 300);
            num_enemies = 6;
        }
        else if (level == 2) {
            enemies.push_back(new Enemy(Enemy::enemytype::Monster, 2));
            //positioning monster in middle
            enemies[0]->sprite.setPosition(200, 50);
            num_enemies = 1;
        }
        else if (level == 3) {
            enemies.push_back(new Enemy(Enemy::enemytype::Dragon, 3));
            //positioning dragon in middle
            enemies[0]->sprite.setPosition(300, 100);
            num_enemies = 1;
        }
    }

    int start_game(RenderWindow& window, int& score)    //returns 1 is player goes to next level, 0 if player dies, -1 if player quits
    {
        
        //RenderWindow window(VideoMode(780, 780), title);//to change these chang it in PowerUp.h too
        Clock clock;
        float timer=0;
        float enemy_timer = 0;

        p->timer = 0;

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds(); 
            float ptime = clock.restart().asSeconds();

            clock.restart();
            timer += time;  
            //timer for shooting
            //p->timer += ptime;
            for(int i=0;i<enemies.size();i++)
				enemies[i]->timeSinceLastDrop += ptime;
            //cout<<timer<<endl;

            //make_enemies();

            


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
				p->shoot(&window, timer);
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                return -1;
            if (Keyboard::isKeyPressed(Keyboard::F) && fireused==1) {        //enages the fire powerup
                p->Fire = true;
                fireInitiat_time = timer;
                fireused--;
                cout << "Fire enetiated!\n";
            }

           //check if 5 seconds have passed since fire powerup was engaged
            if (timer - fireInitiat_time > 5 && p->Fire == true) {
				p->Fire = false;
			}

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

        //Checking for collision between player and enemies
            for (int i = 0; i < enemies.size(); i++) {
                if (p->sprite.getGlobalBounds().intersects(enemies[i]->sprite.getGlobalBounds())) {
					//keep the player away from the enemy
                    if (delta_x < 0) {
						p->move("r");
					}
                    else if (delta_x > 0) {
						p->move("l");
					}
                    else if (delta_y < 0) {
						p->move("d");
					}
                    else if (delta_y > 0) {
						p->move("u");
					}
                    lifes--;
                    //erase all enemies
                    enemies.erase(enemies.begin(), enemies.end());
                    p->sprite.setPosition(400, 780);
                    
                    return 0;
				}
			}
        //Checking for collision between bullets and enemies
            for (int i = 0; i < p->bullets.size(); i++) {
                for (int j = 0; j < enemies.size(); j++) {
                    if (p->bullets[i]->sprite.getGlobalBounds().intersects(enemies[j]->sprite.getGlobalBounds())) {
                        if (!p->Fire) {
                            enemies[j]->health -= p->bullets[i]->damage;
                            p->bullets.erase(p->bullets.begin() + i);
                            if (enemies[j]->health <= 0) {
                                enemies.erase(enemies.begin() + j);
                                score += 10;
                            }
                        }
                        else {  //keep the bullet moving and erase every enemy in its path
							enemies[j]->health -= p->bullets[i]->damage;
                            if (enemies[j]->health <= 0) {
								enemies.erase(enemies.begin() + j);
								score += 10;
							}

                        }
						break;
					}
				}
			}
        //Checking for collision between enemy bullets and player
            for (int i = 0; i < enemies.size(); i++) {
                for (int j = 0; j < enemies[i]->bullets.size(); j++) {
                    if (enemies[i]->bullets[j]->sprite.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
                        if (!powerUp.isActive()) {
							p->health -= enemies[i]->bullets[j]->damage;
						}
                        else {      //in powerUp mode, player is invincible
							p->health += 0;
						}
                        enemies[i]->bullets.erase(enemies[i]->bullets.begin() + j);
                        if (p->health <= 0) {
                            return 0;
                        }
                        break;
                    }
                }
            }
            //checking for collision between player and danger
            //for (int i = 0; i < danger.size(); i++) {
                if (p->sprite.getGlobalBounds().intersects(danger.sprite.getGlobalBounds())) {
					lifes--;
                    enemies.erase(enemies.begin(), enemies.end());

                    p->sprite.setPosition(400, 700);
                    danger.sprite.setPosition(1000, 1000);
					return 0;
				}
			//}
                if(p->sprite.getGlobalBounds().intersects(lives_power.sprite.getGlobalBounds())) {
                    lifes++;
					lives_power.sprite.setPosition(1000, 1000);
                }

            if (enemies.size() == 0 && level == 3)
                return -1;
            else if (enemies.size() == 0)
                return 1;
            

            /*cout<<"StartTime:"<<powerUp.startTime << endl;
            cout << "TimeNow:" << timer << endl;*/
            p->powerup = powerUp.isActive();
	    ////////////////////////////////////////////////
	    /////  Call your functions here            ////
	    //////////////////////////////////////////////
            for (int i = 0; i < p->bullets.size(); i++) {
                /*p->bullets[i].x = (p->x - 30) + (i * 10);
                p->bullets[i].y = p->y + 100;*/
                //p->bullets[i].sprite.setPosition(Vector2f((p->x - 20) + (i * 10), p->y + 10));
                
                p->bullets[i]->move(false);
                window.draw(p->bullets[i]->sprite);
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
            //2 random enemies call update function
            
            if (level == 1) {
                int i = rand() % enemies.size();
                int j = rand() % enemies.size();
                enemies[i]->update(timer, &window, p->sprite.getPosition().x, p->sprite.getPosition().y);
                enemies[j]->update(timer, &window, p->sprite.getPosition().x, p->sprite.getPosition().y);
            }
            else if (level == 2) {  //There's only 1 enemy
                enemies[0]->update(timer, &window, p->sprite.getPosition().x, p->sprite.getPosition().y);
            }
            else if (level == 3) {
                //There's only 1 enemy
                enemies[0]->update(timer, &window, p->sprite.getPosition().x, p->sprite.getPosition().y);
            }
			
           //updating the score life and level
            Score.setString("Score: " + to_string(score));
			Life.setString("Life: " + to_string(lifes));
			Level.setString("Level: " + to_string(level));
            time_string.setString("Time: " + to_string((int)timer));
			
            //Moving Danger sign
            if (timer > 10.0f) {
                danger.move();
            }
            //moving Lifes
            if (timer > 15.0f)
                lives_power.move();

            //moving enemies
            for (int i = 0; i < enemies.size(); i++) {
				enemies[i]->move();
			}
			

	    window.clear(Color::Black); //clears the screen
	    window.draw(background);  // setting background
	    window.draw(p->sprite);   // setting player on screen
        
        for (int i = 0; i < p->bullets.size(); i++) {
            p->bullets[i]->move(false);
            window.draw(p->bullets[i]->sprite);
        }
        //Draw enemies
        for (int i = 0; i < enemies.size(); i++) {
            for (int j = 0; j < enemies[i]->bullets.size(); j++) {
				enemies[i]->bullets[j]->move(true);
				window.draw(enemies[i]->bullets[j]->sprite);
			}
			window.draw(enemies[i]->sprite);
		}

        powerUp.update(timer);

        if(timer > 10.0f)
            window.draw(danger.sprite);
        if (timer > 15.0f)
            window.draw(lives_power.sprite);
        
        window.draw(powerUp.sprite);
        //drawing the score life and level
        window.draw(Score);
        window.draw(Life);
        window.draw(Level);
        window.draw(time_string);


	    window.display();  //Displying all the sprites
        }

    }

    void resetFire() {
        fireused = 1;
    }
};


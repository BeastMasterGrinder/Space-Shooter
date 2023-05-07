#pragma once
//#include <SFML/Graphics.hpp>
//#include <iostream>
#include <vector>
#include"bullet.h"
using namespace std;
using namespace sf;

class Enemy
{

public:
    int enemyLevel;
    int score;
    float dropInterval;
    float timeSinceLastDrop;
    int health;
    bool moving_right;

    sf::Texture alphaTexture;
    sf::Texture betaTexture;
    sf::Texture gammaTexture;
    sf::Texture Monster;
    sf::Texture Dragon;
    enum struct enemytype {
        Alpha, Beta, Gamma, Monster, Dragon
    };
    enemytype Etype;
    vector<Bullet*> bullets;
    Sprite sprite;
    int speed_enemies;

    Enemy(enemytype type, int level) : Etype(type), enemyLevel(level) {
        enemyLevel = level;
        score = 0;
        dropInterval = 0;
        timeSinceLastDrop = 0;
        health = 100;
        moving_right = true;
        speed_enemies = 1.0f;

        //sprite.setColor(sf::Color(255, 255, 255, 255));
        if (!alphaTexture.loadFromFile("img/enemy_1.png")) {
            cout<<"unable to load alpha texture\n";
        }
        if (!betaTexture.loadFromFile("img/enemy_2.png")) {
			cout << "unable to load beta texture\n";
		}
        if (!gammaTexture.loadFromFile("img/enemy_3.png")) {
            cout<< "unable to load gamma texture\n";
        }
        if (!Monster.loadFromFile("img/monster1.png")) {
            cout<< "unable to load gamma texture\n";
        }
        if (!Dragon.loadFromFile("img/dragon1.png")) {
			cout<< "unable to load gamma texture\n";
		}

        



        // Set enemy properties based on type and level
        switch (Etype) {
        case enemytype::Alpha:
            sprite.setTexture(alphaTexture);
            //sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

            score = 10 * enemyLevel;
            dropInterval = 5.0f; // 5 seconds interval
            health = 100;
            //sprite.setTexture(alphaTexture); // Replace with the appropriate texture for Alpha Invader
            break;

        case enemytype::Beta:
            sprite.setTexture(betaTexture);
            //sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

            score = 20 * enemyLevel;
            dropInterval = 3.0f; // 3 seconds interval
            health = 150;
            //sprite.setTexture(betaTexture); // Replace with the appropriate texture for Beta Invader
            break;

        case enemytype::Gamma:
            sprite.setTexture(gammaTexture);
            //sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

            score = 30 * enemyLevel;
            dropInterval = 2.0f; // 2 seconds interval
            health = 200;
            //sprite.setTexture(gammaTexture); // Replace with the appropriate texture for Gamma Invader
            break;

        case enemytype::Monster:
            sprite.setTexture(Monster);
            //sprite.setTextureRect(sf::IntRect(0, 0, 300, 300));

			score = 40 * enemyLevel;
			dropInterval = 3.0f; // 3 seconds interval
			health = 2500;
			//sprite.setTexture(Monster); // Replace with the appropriate texture for Gamma Invader
            sprite.setScale(0.5f, 0.5f);
			break;

        case enemytype::Dragon:
            sprite.setTexture(Dragon);
            //sprite.setTextureRect(sf::IntRect(0, 0, 400, 400));

            score = 50 * enemyLevel;
            dropInterval = 5.0f; // 5.0 seconds interval
            health = 10000;
            //sprite.setTexture(Dragon); // Replace with the appropriate texture for Gamma Invader
            sprite.setPosition(sf::Vector2f(100, 10)); // Set the initial position
            
            break;
        }

        // Set initial position and scale for the sprite
        
        //sprite.setScale(0.75f, 0.75f); // Set the initial scale
    }

    void update(float deltaTime, RenderWindow* window, float spaceshipX, float spaceshipY) {
        // Update enemy logic based on the elapsed time
        if (timeSinceLastDrop < dropInterval)
            return;
        if (!(health <= 0)) {

            // Check if it's time to drop a bomb
            timeSinceLastDrop += deltaTime;
            if (timeSinceLastDrop >= dropInterval) {
                dropBomb(window, spaceshipX, spaceshipY);
                timeSinceLastDrop = 0.0f;
            }
        }
        // Update other enemy logic here
    }

    void dropBomb(RenderWindow* window, float spaceshipX, float spaceshipY) {
        // Logic for dropping a bomb/bullet
        // Create a new bullet and add it to the bullets vector if enemy is alive and 4 seconds have passed since the last bullet
        Bullet* bomb = new Bullet(window, "img/PNG/Lasers/laserGreen03.png", sprite.getPosition().x, sprite.getPosition().y);
        
        if (enemyLevel == 2) {
            int x = sprite.getPosition().x + 100;
            int y = sprite.getPosition().y + 400;
            float radius = 100.0f; // Adjust the radius of the umbrella arch

            for (int i = 0; i < 5; i++) {
                

                Bullet* new_bullet = new Bullet(window, "img/PNG/Lasers/laserGreen04.png", x, y); // Create a new bullet object

                //new_bullet.sprite.setRotation(/*angle*/ + 90.0f); // Set the rotation angle for the bullet sprite (add 90 degrees to make it face upwards)
                bullets.push_back(new_bullet); // Add the bullet to the vector
                x +=50;
            }
            bomb->damage = 50;
        }
        else if (enemyLevel == 3) {
            int x = sprite.getPosition().x + 200;
            int y = sprite.getPosition().y + 200;

            // Calculate the direction vector from the dragon to the spaceship
            float dx = spaceshipX - x;
            float dy = spaceshipY - y;

            // Calculate the magnitude of the direction vector
            float magnitude = std::sqrt(dx * dx + dy * dy);

            // Normalize the direction vector
            float directionX = dx / magnitude;
            float directionY = dy / magnitude;

            // Set the bullet position to be slightly away from the dragon's position
            float bulletX = x + directionX * 100.0f;
            float bulletY = y + directionY * 100.0f;

            Bullet* new_bullet = new Bullet(window, "img/PNG/Lasers/laserGreen04.png", bulletX, bulletY); // Create a new bullet object

            // Set the rotation angle for the bullet sprite to point towards the spaceship
            float angle = std::atan2(directionY, directionX) * 180.0f / 3.14159f;
            new_bullet->sprite.setRotation(angle);

            bullets.push_back(new_bullet); // Add the bullet to the vector

            // Rest of the code...
            bomb->damage = 100;
        }

        bullets.push_back(bomb);
        


    }

    void move_bomb() {
        		// Logic for moving the bullet
		// Move the bullet
        for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move(true);
		}
    }

    bool takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            // Enemy destroyed, perform necessary actions
            return true;
        }
    }

    Sprite getSprite() const {
        return sprite;
    }

    void move() {
        //moving monster and dragon right and left within the screen
        if (Etype == enemytype::Monster || Etype == enemytype::Dragon) {
            if (moving_right) {
                if (sprite.getPosition().x + sprite.getGlobalBounds().width >= 780) {
                    moving_right = false;
                }
                else {
                    sprite.move(1.0f, 0.0f); // Move the sprite to the right
                }
            }
            else {
                if (sprite.getPosition().x <= 0) {
                    moving_right = true;
                }
                else {
                    sprite.move(-1.0f, 0.0f); // Move the sprite to the left
                }
            }

            // Rest of the code...
        }



        
        
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}

};
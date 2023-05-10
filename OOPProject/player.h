#pragma once
#include "bullet.h"
#include<cmath>
using namespace sf;

class Player {

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);

	}

public:
	float timer;

	Texture tex;
	Sprite sprite;
	vector<Bullet*> bullets;
	float speed = 0.1;
	int x, y;

	bool powerup = false;
	bool Fire;
	int health = 100;


	Player(std::string png_path) {
		Fire = false;

		timer = 0;




		sprite.setColor(sf::Color(255, 255, 255, 255));

		if (!tex.loadFromFile(png_path)) {
			cout << "unable to load player image\n";
		}

		sprite.setTexture(tex);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));

		x = 340; y = 700;

		sprite.setPosition(Vector2f(x, y));

		sprite.setScale(0.75, 0.75);
	}
	
	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x = -1;	//move the player left
		else if (s == "r")//move the player right
			delta_x = 1;
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;
		//for player to move diagnollay too;
		if (s == "lu") {
			delta_x = -1;
			delta_y = -1;
		}
		else if (s == "ru") {
			delta_x = 1;
			delta_y = -1;
		}
		else if (s == "ld") {
			delta_x = -1;
			delta_y = 1;
		}
		else if (s == "rd") {
			delta_x = 1;
			delta_y = 1;
		}

		delta_x *= speed * 10;
		delta_y *= speed * 10;

		x = x + delta_x;
		y = y + delta_y;

		//making sure the player doesn't go out of the screen
		
		if (x < 0)
			x = 700; // Move to the right edge
		if (x > 700)
			x = 0; // Move to the left edge
		if (y < 0)
			y = 700; // Move to the bottom edge
		if (y > 700)
			y = 0; // Move to the top edge

		sprite.setPosition(Vector2f(x, y));

		sprite.move(delta_x, delta_y);

	}

	void shoot(RenderWindow* window, float gametime) {
		const float shoot_interval = 0.5f; // interval between shots in seconds
		if (gametime < timer + shoot_interval) {
			return; // don't shoot yet
		}
		if (!powerup) {
			//create a bullet object and add it to the list of bullets
			//img / player_ship.png
			Bullet* new_bullet = new Bullet(window, "img/PNG/Lasers/laserBlue12.png", x, y);//img\PNG\Lasers
			//cout << "bullet shot\n";
			bullets.push_back(new_bullet);

		}
		else if (Fire) {	//in Fire mode 
			Bullet* fire_bullet = new Bullet(window, "img/PNG/Effects/fire02.png", x, y);
			fire_bullet->damage = 100;
			bullets.push_back(fire_bullet);

		}
		else {	//in power up mode
			int x = sprite.getPosition().x + 50;
			int y = sprite.getPosition().y + 50;
			float radius = 100.0f; // Adjust the radius of the umbrella arch

			for (int i = 0; i < 7; i++) {
				float angle = (i - 3) * 30.0f; // Adjust the angle between bullets

				float bulletX = x + radius * sin(angle * 3.14159f / 180.0f);
				float bulletY = y - radius * cos(angle * 3.14159f / 180.0f);

				Bullet* new_bullet = new Bullet(window, "img/PNG/Lasers/laserGreen04.png", bulletX, bulletY); // Create a new bullet object

				//new_bullet->sprite.setRotation(angle + 90.0f); // Set the rotation angle for the bullet sprite (add 90 degrees to make it face upwards)
				bullets.push_back(new_bullet); // Add the bullet to the vector
			}



		}
		timer = gametime;
	}

};

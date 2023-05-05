#include"bullet.h"
using namespace sf;
class Player{

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);

	}

public:
	float timer;
	
	Texture tex;
	Sprite sprite;
	vector<Bullet> bullets;
	float speed=0.1;
	int x,y;

	bool powerup = false;


	Player(std::string png_path)
	{
		
		timer = 0;
		
		bullets = std::vector<Bullet>();


		sprite.setColor(sf::Color(255, 255, 255, 255));

		if (!tex.loadFromFile(png_path)) {
			cout << "unable to load player image\n";
		}
		
		sprite.setTexture(tex);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));

		x=340;y=700;
		
		sprite.setPosition(Vector2f(x,y));

		sprite.setScale(0.75,0.75);
	}
	//called when player presses space bar
	void fire()
	{
		//create a bullet object and add it to the list of bullets

	}
	void move(std::string s){
		float delta_x=0,delta_y=0;
		if(s=="l")
			delta_x=-1;	//move the player left
		else if(s=="r")//move the player right
			delta_x=1;
		else if(s=="u")
			delta_y=-1;
		else if(s=="d")
			delta_y=1;
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

		delta_x*=speed * 10;
		delta_y*=speed * 10;

		x = x + delta_x;
		y = y + delta_y;

		sprite.setPosition(Vector2f(x,y));

		sprite.move(delta_x, delta_y);

	}
	void shoot() {
			const float shoot_interval = 0.5f; // interval between shots in seconds
			if (timer < shoot_interval) {
				return; // don't shoot yet
			}
		if (!powerup) {
			//create a bullet object and add it to the list of bullets
			//img / player_ship.png
			Bullet new_bullet("img/PNG/Lasers/laserRed02.png", x, y);
			//cout << "bullet shot\n";
			bullets.push_back(new_bullet);
			timer = 0;
		}
		else {
			for (int i = 0; i < 7; i++)
			{
				Bullet new_bullet("img/PNG/Lasers/laserGreen04.png", x, y); // create a new bullet object
				new_bullet.sprite.setRotation(i * 45); // set the rotation angle for the bullet sprite
				bullets.push_back(new_bullet); // add the bullet to the vector
			}
		}
	}
};

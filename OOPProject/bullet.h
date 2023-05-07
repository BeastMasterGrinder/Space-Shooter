#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<string.h>

using namespace std;
using namespace sf;

class Bullet : public Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
public:
	int x, y;
	float speed = 0.1;
	Texture tex;
	Sprite sprite;
	int damage;


	Bullet(RenderWindow* window, string png_path, int x, int y)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
		if (!tex.loadFromFile(png_path)) {
			cout << "unable to load bullet image\n";
		}
		//sprite.setTextureRect(IntRect(10, 10, 20, 20));
		sprite.setTexture(tex);
		this->x = x;
		this->y = y;
		sprite.setPosition(Vector2f(x, y));
		//sprite.setScale(0.75, 0.75);
		damage = 20;
	}
	void move(bool bomb)
	{
		if (!bomb) {
			y -= speed * 10;
			sprite.setPosition(Vector2f(x, y));
			sprite.move(0, -speed);
		}
		else {
			y += speed * 10;
			sprite.setPosition(Vector2f(x, y));
			sprite.move(0, speed);
		}
	}
};
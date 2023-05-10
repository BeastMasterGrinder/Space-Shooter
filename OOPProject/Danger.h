#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Danger
{
public:
	Sprite sprite;
	Texture texture;
	
	Danger() {
		int windowWidth = 780;
		int windowHeight = 780;
		// Load power-up texture and set its position randomly
		sprite.setColor(sf::Color(255, 255, 255, 255));
		if (!texture.loadFromFile("img/PNG/Meteors/meteorGrey_big2.png"))
			cout << "unable to load danger texture\n";

		sprite.setTexture(texture);
		sprite.setPosition(rand() % windowWidth, 0);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	void move() {	//move down

		sprite.move(0, 1.5);
	}

};
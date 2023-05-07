#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;

class PowerUp {
private:
    bool Active;
    float duration;
public:
    float startTime;
    Sprite sprite;
    Texture texture;
    Clock timer;
    PowerUp() {
        srand(time(0));
        duration = 0;
        startTime = 0;

        int windowWidth = 780;
        int windowHeight = 780;
        // Load power-up texture and set its position randomly
        sprite.setColor(sf::Color(255, 255, 255, 255));
        texture.loadFromFile("img/PNG/Power-ups/bolt_gold.png");
        sprite.setTexture(texture);
        sprite.setPosition(rand() % windowWidth, rand() % windowHeight);
        Active = false;
    }

    void activate(float stime) {
        Active = true;
        duration = 1000.0f;
        startTime = stime;
        sprite.setPosition(-1000, -1000);
        //timer.restart();
    }

    bool isActive() {
        return Active;
    }

    void draw(RenderWindow& window) {
        if (Active) {
            window.draw(sprite);
        }
    }

    void update(float timer) {
        if (Active) {
			duration -= (timer - startTime);
            if (duration <= 0) {
                Active = false;
            }
        }
    }
};

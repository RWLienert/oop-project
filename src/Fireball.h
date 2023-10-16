// The fireball class defines the ammo of each catapult denoted as fireballs and defines how they move and are drawn to the screen

#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Fireball : public Entity{
    private:
        int speed = 4; 
    public:
        Fireball(string imgDirectory);
        void move(float power, Vector2f startPos, Vector2f direction);
        bool isFired();
        void reload();
        void draw(RenderWindow* win);
        void spawn(int endX, int endY);
        ~Fireball();
};

#endif
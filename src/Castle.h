#ifndef CASTLE_H
#define CASTLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Catapult.h"
#include <iostream>
using namespace sf;
using namespace std;

class Castle : public Entity{
    protected:
        int lives;
        Vector2f centre;
        Catapult** catapults;
    public:
        Castle(int lives, int width, int height);
        void spawn(int winX, int winY);
        void draw(RenderWindow* win);
        Catapult** getCatapults();
        ~Castle();
};

#endif
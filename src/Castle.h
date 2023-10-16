// The castle class defines the creation of the castle and is used to generate an array of catapults. This is in essence the user's character. It provides functions to create this object and obtain its values.

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
        Catapult** catapults;
    public:
        Castle(int width, int height,string imgDirectory);
        void spawn(int winX, int winY);
        void draw(RenderWindow* win);
        Catapult** getCatapults();
        ~Castle();
};

#endif
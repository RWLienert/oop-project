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
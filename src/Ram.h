// The ram class defines an inhereted class that is of type enemy. It has functions to draw and spawn the enemy as well as define how it will move

#ifndef RAM_H
#define RAM_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <cmath>
#include <iostream>
using namespace sf;
using namespace std;

class Ram : public Enemy{
    protected:
        int maxRam;
    public:
        Ram(int width, int height, string imgDirectory);
        void draw(RenderWindow* win);
        void spawn(int winX, int winY);
        void movePath(Vector2f castlePosition);
        ~Ram();
};

#endif
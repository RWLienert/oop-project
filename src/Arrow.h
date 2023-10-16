// This class takes care of the power meter or 'arrow' that dictates how far each catapult will fire their fireballs. It includes information about its sprite and shape

#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Arrow : public Entity{
    private:
        Shape* body;
    public:
        Arrow(string imgDirectory);
        void spawn(int centreX, int centreY);
        void draw(RenderWindow* win);
        Shape* getBar();
        ~Arrow();
};

#endif
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
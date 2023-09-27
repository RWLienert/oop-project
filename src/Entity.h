#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Entity{
    protected:
        Shape* body;
    public:
        void draw(RenderWindow* win);
};

#endif
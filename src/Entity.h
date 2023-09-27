#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Entity{
    protected:
        Shape* body;
        bool alive;
    public:
        void draw(RenderWindow* win);
        virtual void spawn(int winX, int winY) = 0;
};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Entity{
    protected:
        Texture* texture;
        Sprite* sprite;
        bool alive;
        int width;
        int height;
    public:
        virtual void draw(RenderWindow* win) = 0;
        virtual void spawn(int winX, int winY) = 0;
};

#endif
#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Arrow : public Entity{
    private:
        Texture* texture;
        Sprite* sprite;
    public:
        Arrow(string imgDirectory);
        void spawn(int centreX, int centreY);
        void draw(RenderWindow* win);
        Sprite* getSprite();
        Shape* getBar();
        ~Arrow();
};

#endif
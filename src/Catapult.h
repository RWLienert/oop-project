#ifndef CATAPULT_H
#define CATAPULT_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Catapult : public Entity{
    protected:
        Vector2f pivot;
    public:
        Catapult(int width, int height, string imgDirectory);
        void spawn(int cornerX, int cornerY);
        void draw(RenderWindow* win);
        Sprite* getSprite();
        Vector2f getPivot();
        ~Catapult();
};

#endif
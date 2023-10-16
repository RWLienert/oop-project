#ifndef ONAGER_H
#define ONAGER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <cmath>
#include <ctime>
#include <iostream>
using namespace sf;
using namespace std;

class Onager : public Enemy{
    protected:
        int maxOnagers;
    public:
        Onager(int width, int height, string imgDirectory);
        void draw(RenderWindow* win);
        void spawn(int winX, int winY);
        void movePath(Vector2f castlePosition);
        ~Onager();
};

#endif
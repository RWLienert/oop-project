#ifndef ONAGER_H
#define ONAGER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>
#include <ctime>
#include <iostream>
using namespace sf;
using namespace std;

class Onager : public Enemy{
    protected:
        Shape* body;
        int maxOnagers;
    public:
        Onager(int width, int height);
        void draw(RenderWindow* win);
        void spawn(int winX, int winY);
        ~Onager();
};

#endif
#ifndef CASTLE_H
#define CASTLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Castle : public Entity{
    protected:
        int health;
        Vector2f centre;
        int width;
        int height;
    public:
        Castle(int health, int width, int height);
        void spawn(int winX, int winY);
        ~Castle();
};

#endif
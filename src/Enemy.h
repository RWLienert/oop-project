// The enemy class is an abstract class that defines the speed of enemies and a virtual function that dictates how they should be moved

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
using namespace sf;
using namespace std;

class Enemy : public Entity{
    protected:
        int speed;
        Vector2f castlePosition;
    public:
        virtual void movePath(Vector2f castlePosition);
};

#endif

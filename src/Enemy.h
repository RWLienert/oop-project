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
        int health;
        Vector2f castlePosition;
    public:
        virtual void movePath(Vector2f castlePosition);
};

#endif

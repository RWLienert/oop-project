// The onager class defines an inhereted class that is of type enemy. It has functions to draw and spawn the enemy as well as define how it will move

#ifndef ONAGER_H
#define ONAGER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Fireball.h"
#include <cmath>
#include <ctime>
#include <iostream>
using namespace sf;
using namespace std;

class Onager : public Enemy{
    protected:
        int maxOnagers;
        Fireball** onagerFireball;
        bool inPosition;
        Vector2f fireDirection;
        int ranShoot[3];
    public:
        Onager(int width, int height, string imgDirectory);
        void draw(RenderWindow* win);
        void spawn(int winX, int winY);
        void movePath(Vector2f castlePosition);
        void fire();
        void reload();
        int* getRand();
        bool getInPosition();      
        Fireball** getOnagerFireball();
        ~Onager();
};

#endif
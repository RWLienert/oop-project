#ifndef CATAPULT_H
#define CATAPULT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "Fireball.h"
#include <iostream>
using namespace sf;
using namespace std;

class Catapult : public Entity{
    protected:
        Vector2f pivot;
        Vector2f end;
        Vector2f startPos;
        Vector2f direction;
        Fireball** fireballs;
        int numBalls;
        int remainingBalls;
        float power;
    public:
        Catapult(int width, int height, string imgDirectory, int numBalls);
        void spawn(int cornerX, int cornerY);
        void draw(RenderWindow* win);
        void fire(float endX, float endY);
        void reload();
        void updateFire(float power, Vector2f startPos, Vector2f direction);
        int remaining();
        void setRemaining();
        Vector2f getPivot();
        ~Catapult();
};

#endif
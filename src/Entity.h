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
        Vector2f castlePos;
        bool alive;
        int width;
        int height;
    public:
        virtual void draw(RenderWindow* win) = 0;
        virtual void spawn(int x, int y) = 0;
        Sprite* getSprite();
        void setCastlePos(Vector2f castlePos);
};

#endif
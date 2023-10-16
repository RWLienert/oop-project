// Entity is a base class (abstract) that defines functions used to create each game object. It provides variables such as the sprite, texture and positioning as well as getters and setters to adjust these values. 

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
        Vector2f position;
        Vector2f firePos;
        bool alive;
        int width;
        int height;
    public:
        virtual void draw(RenderWindow* win) = 0;
        virtual void spawn(int x, int y) = 0;
        Sprite* getSprite();
        void setAlive(bool alive);
        bool getAlive();
        Vector2f getPosition();
        Vector2f* getFirePos();
        void setFirePos(Vector2f firePos);
};

#endif
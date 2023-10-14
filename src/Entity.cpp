#include "Entity.h"

void Entity::draw(RenderWindow* win){}

void Entity::spawn(int winX, int winY){}

Sprite* Entity::getSprite(){
    return sprite;
}

void Entity::setAlive(bool alive){
    this->alive = alive;
}

bool Entity::getAlive(){
    return alive;
}

Vector2f Entity::getPosition(){
    return position;
}

Vector2f* Entity::getFirePos(){
    return &firePos;
}
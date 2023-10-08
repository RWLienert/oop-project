#include "Entity.h"

void Entity::draw(RenderWindow* win){}

void Entity::spawn(int winX, int winY){}

Sprite* Entity::getSprite(){
    return sprite;
}

void Entity::setCastlePos(Vector2f castlePos){
    this->castlePos = castlePos;
}
#include "Entity.h"

void Entity::draw(RenderWindow* win){
    win->draw(*body);
}

void Entity::spawn(int winX, int winY){}
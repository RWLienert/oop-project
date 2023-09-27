#include "Entity.h"

void Entity::draw(RenderWindow* win){
    win->draw(*body);
}

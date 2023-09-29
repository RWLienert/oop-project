#include "Catapult.h"

Catapult::Catapult(int width, int height, string imgDirectory){
    // initialise values
    this->width = width;
    this->height = height;
    // create body
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Catapult Texture didn't load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(width*0.9,height/2);

    alive = false;
}

void Catapult::spawn(int cornerX, int cornerY){
    //define positioning
    sprite->setPosition(cornerX,cornerY);
    alive = true;
    pivot = Vector2f(cornerX,cornerY);
}

void Catapult::draw(RenderWindow* win){
    win->draw(*sprite);
}

Sprite* Catapult::getSprite(){
    return sprite;
}

Vector2f Catapult::getPivot(){
    return pivot;
}

Catapult::~Catapult(){
    delete this->sprite;
}
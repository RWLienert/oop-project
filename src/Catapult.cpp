#include "Catapult.h"

Catapult::Catapult(int width, int height){
    // initialise values
    this->width = width;
    this->height = height;
    // create body
    body = new RectangleShape(Vector2f(width,height));
    body->setOrigin(width*0.8,height/2);
    body->setFillColor(Color(57, 58, 59));
    alive = false;
}

void Catapult::spawn(int cornerX, int cornerY){
    //define positioning
    body->setPosition(cornerX,cornerY);
    alive = true;
    pivot = Vector2f(cornerX,cornerY);
}

Shape* Catapult::getBody(){
    return body;
}

Catapult::~Catapult(){
    delete this->body;
}
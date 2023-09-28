#include "Arrow.h"

Arrow::Arrow(string imgDirectory){
    // creates the arrow's texture, sprite and power bar
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile("resources/arrow.png")){
        cout << "Arrow Texture didn't load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setPosition(-400,-400);
    sprite->setOrigin(130,24);
    sprite->setScale(1.5,1.5);
    body = new RectangleShape(Vector2f(100,8));
    body->setFillColor(Color::Red);
    body->setOrigin(190,4);
}

void Arrow::spawn(int centreX, int centreY){
    sprite->setPosition(centreX,centreY);
    body->setPosition(centreX,centreY);
}

void Arrow::draw(RenderWindow* win) {
    win->draw(*sprite);
    win->draw(*body);
}

Sprite* Arrow::getSprite(){
    return sprite;
}

Shape* Arrow::getBar(){
    return body;
}

Arrow::~Arrow(){
    delete this->sprite;
    delete this->texture;
}
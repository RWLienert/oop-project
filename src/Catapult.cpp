#include "Catapult.h"

Catapult::Catapult(int width, int height, string imgDirectory, int numBalls){
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
    this->numBalls = numBalls;
    fireballs = new Fireball*[numBalls];
    for (int i = 0; i < numBalls; i++) {
        fireballs[i] = new Fireball("resources/fireball.png");
    }
}

void Catapult::spawn(int cornerX, int cornerY){
    //define positioning
    sprite->setPosition(cornerX,cornerY);
    alive = true;
    pivot = Vector2f(cornerX,cornerY);
    end = pivot;
}

void Catapult::draw(RenderWindow* win){
    win->draw(*sprite);
    for (int i = 0; i < numBalls; i++) {
        if (fireballs[i]->isFired()) {
            fireballs[i]->draw(win);
            fireballs[i]->move(power,startPos,direction);
        }
    }
}

void Catapult::fire(float endX, float endY){
    for (int i = 0; i < numBalls; i++){
        if (!fireballs[i]->isFired()){
            fireballs[i]->spawn(endX,endY);
            remainingBalls = numBalls - 1;
            break;
        }
    }
}

void Catapult::reload(){
    for (int i = 0; i < numBalls; i++){
        if (fireballs[i]->isFired()){
            fireballs[i]->reload();
        }
    }
}

void Catapult::updateFire(float power, Vector2f startPos, Vector2f direction){
    this->power = power;
    this->startPos = startPos;
    this->direction = direction;
}

int Catapult::remaining(){
    return remainingBalls;
}

void Catapult::setRemaining(){
    remainingBalls = numBalls;
}

Sprite* Catapult::getSprite(){
    return sprite;
}

Vector2f Catapult::getPivot(){
    return pivot;
}

Catapult::~Catapult(){
    delete this->sprite;
    delete [] this->fireballs;
}
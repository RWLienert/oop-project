#include "Catapult.h"

Catapult::Catapult(int width, int height, string imgDirectory, int numBalls){
    // initialise values
    this->width = width;
    this->height = height;

    // create sprite
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

    // initialise shooting variables
    for (int i = 0; i < 3; i++){
        startPos[i] = Vector2f(0,0);
        direction[i] = Vector2f(0,0);
        power[i] = 0;
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
    // draws a fireball if it has been fired
    for (int i = 0; i < numBalls; i++) {
        if (fireballs[i]->isFired()) {
            fireballs[i]->draw(win);
            fireballs[i]->move(power[i],startPos[i],direction[i]);
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
    // assigns shooting variables to their respective fireball
    for (int i = 0; i < numBalls; i++){
        if (!fireballs[i]->isFired()){
            this->power[i] = power;
            this->direction[i] = direction;
            this->startPos[i] = startPos;
        }
    }
}

int Catapult::remaining(){
    return remainingBalls;
}

void Catapult::setRemaining(){
    remainingBalls = numBalls;
}

Vector2f Catapult::getPivot(){
    return pivot;
}

Fireball** Catapult::getFireballs(){
    return fireballs;
}

Catapult::~Catapult(){
    delete this->sprite;
    delete [] this->fireballs;
}
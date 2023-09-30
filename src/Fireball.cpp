#include "Fireball.h"
#include <cmath>

Fireball::Fireball(string imgDirectory){
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Fireball Texture didn't load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(21/2,21/2);
    alive = false;
}

void Fireball::move(float power, Vector2f startPos, Vector2f direction){
    float travelledDistance = sqrt(pow(sprite->getPosition().x-startPos.x,2)+pow(sprite->getPosition().y-startPos.y,2));
    float distanceScale = 2.5;
    float imgScale = 1;
    if (travelledDistance < distanceScale*power){
        float changeX = speed*-direction.x;
        float changeY = speed*-direction.y;
        sprite->move(changeX,changeY);
        if (travelledDistance < 2*(distanceScale*power)/3){
            imgScale += 0.005;
            sprite->scale(imgScale,imgScale);
        }
        else{
            imgScale -= 0.01;
            sprite->scale(imgScale,imgScale);
        }
    }
    else{
        alive = false;
    }
}

bool Fireball::isFired(){
    return alive;
}

void Fireball::reload(){
    alive = false;
}

void Fireball::draw(RenderWindow* win){
    win->draw(*sprite);
}

void Fireball::spawn(int endX, int endY){
    sprite->setPosition(endX,endY);
    alive = true;
}

int Fireball::getSpeed(){
    return speed;
}

Fireball::~Fireball(){
    delete this->sprite;
}
#include "Castle.h"
#include <time.h>

Castle::Castle(int health, int width, int height){
    this->health = health;
    this->width = width;
    this->height = height;
    body = new RectangleShape(Vector2f(width,height));
    body->setOrigin(width/2,height/2);
    body->setFillColor(Color::White);
    alive = false;
    srand(time(0));
}

void Castle::spawn(int winX, int winY){
    int randX = winX/3 + rand() % (winX - (2*winX)/3);
    int randY = winY/3 + rand() % (winY - (2*winY)/3);
    body->setPosition(randX,randY);
    cout << randX << endl;
    cout << randY << endl;
    alive = true;
}

Castle::~Castle(){
    delete this->body;
}
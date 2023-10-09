#include "Onager.h"

Onager::Onager(int width, int height){
    this->width = width;
    this->height = height;
    body = new RectangleShape(Vector2f(30.f,30.f));
    body->setOrigin(15.f,15.f);
    body->setFillColor(Color(132, 138, 133));
    body->setPosition(-100,-100);
    alive = false;
    srand(time(NULL));
}

void Onager::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*body);
    }
}

void Onager::spawn(int winX, int winY){
    int onagerRandX = rand() % (winX - 20);
    int onagerRandY = rand() % (winY - 20);
    body->setPosition(static_cast<float>(onagerRandX), static_cast<float>(onagerRandY));
    alive = true;
}

Onager::~Onager(){
    delete body;
}
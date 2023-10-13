#include "Ram.h"

Ram::Ram(int width, int height, string imgDirectory){
    this->width = width;
    this->height = height;
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "ram sprite was unable to load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(width/2,height/2);
    sprite->scale(1.4,1.4);

    alive = false;
    srand(time(NULL));
}

void Ram::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*sprite);
    }
}

void Ram::spawn(int winX, int winY){
    int ramRandX = rand() % (winX - 20);
    int ramRandY = rand() % (winY - 20);
    sprite->setPosition(static_cast<float>(ramRandX), static_cast<float>(ramRandY));
    alive = true;
}

Ram::~Ram(){
    delete sprite;
}
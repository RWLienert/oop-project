#include "Castle.h"
#include <time.h>

Castle::Castle(int lives, int width, int height,string imgDirectory){
    // initialise values
    this->lives = lives;
    this->width = width;
    this->height = height;

    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Castle Texture didn't load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(width/2,height/2);
    sprite->scale(1.4,1.4);

    alive = false;
    // create 4 catapults
    catapults = new Catapult*[4];
    for (int i = 0; i < 4; i++) {
        catapults[i] = new Catapult(50,12,"resources/catapult.png",3);
    }
    srand(time(0));
}

// overides Entity draw function to display the catapults
void Castle::draw(RenderWindow* win){
    win->draw(*sprite);
    for (int i = 0; i < 4; i++) {
        catapults[i]->draw(win);
    }
}

// spawns the castle and catapults in each corner
void Castle::spawn(int winX, int winY){
    int randX = winX/3 + rand() % (winX - (2*winX)/3);
    int randY = winY/3 + rand() % (winY - (2*winY)/3);
    sprite->setPosition(randX,randY);
    cout << randX << endl;
    cout << randY << endl;
    alive = true;
    centre = Vector2f(randX,randY);
    catapults[0]->spawn(centre.x-width/2,centre.y-width/2);
    catapults[1]->spawn(centre.x+width/2,centre.y-width/2);
    catapults[2]->spawn(centre.x-width/2,centre.y+width/2);
    catapults[3]->spawn(centre.x+width/2,centre.y+width/2);
}

Catapult** Castle::getCatapults(){
    return catapults;
}

Castle::~Castle(){
    delete this->sprite;
    delete this->catapults;
}
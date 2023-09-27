#include "Castle.h"
#include <time.h>

Castle::Castle(int lives, int width, int height){
    // initialise values
    this->lives = lives;
    this->width = width;
    this->height = height;
    // setup body
    body = new RectangleShape(Vector2f(width,height));
    body->setOrigin(width/2,height/2);
    body->setFillColor(Color(132, 138, 133));
    alive = false;
    // create 4 catapults
    catapults = new Catapult*[4];
    for (int i = 0; i < 4; i++) {
        catapults[i] = new Catapult(40,12);
    }
    srand(time(0));
}

// overides Entity draw function to display the catapults
void Castle::draw(RenderWindow* win){
    win->draw(*body);
    for (int i = 0; i < 4; i++) {
        catapults[i]->draw(win);
    }
}

// spawns the castle and catapults in each corner
void Castle::spawn(int winX, int winY){
    int randX = winX/3 + rand() % (winX - (2*winX)/3);
    int randY = winY/3 + rand() % (winY - (2*winY)/3);
    body->setPosition(randX,randY);
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
    delete this->body;
}
#include "Game.h"
#include <cmath>

// create window and objects
Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title);
    win->setFramerateLimit(60);
    castle = new Castle(4,140,140,"resources/castle.png");
    arrow = new Arrow("resources/arrow.png");
}

// load objects
void Game::load(){
    castle->spawn(win->getSize().x,win->getSize().y);
}

// move catapults based on mouse location
void Game::moveCatapult(Vector2f translatedPos, int currentCatapult){
    if (clickOn == true) {
        // math to find the required angle to move the catapult
        Vector2f currentPosition = castle->getCatapults()[currentCatapult]->getSprite()->getPosition();
        const float PI = 3.14159265;
        float difX = currentPosition.x - translatedPos.x;
        float difY = currentPosition.y - translatedPos.y;

        // calculate the distance between mouse and catapult
        float scaleArrow = sqrt(difX*difX+difY*difY);
        if (scaleArrow > 300) {
            scaleArrow = 300;
        }

        // alter the arrow's length and colour based on position
        arrow->getSprite()->setScale(1.5+(scaleArrow*0.002),1.5);
        arrow->getBar()->setScale(1+(scaleArrow*0.0013),1);
        arrow->getBar()->setFillColor(Color(227, 206-scaleArrow/2, 18));

        // calculate rotation and apply it to the objects
        float rotation = (atan2(difY,difX))* 180/PI;
        castle->getCatapults()[currentCatapult]->getSprite()->setRotation(rotation);
        arrow->getSprite()->setRotation(rotation);
        arrow->getBar()->setRotation(rotation);
    }
}

// game loop
void Game::run(){
    load();
    clickOn = false;
    while (win->isOpen()){
        Event e;
        while (win->pollEvent(e)){
            // calculate position
            int clickCount = 0;
            Vector2i mousePos = Mouse::getPosition(*win);
            Vector2f translatedPos = win->mapPixelToCoords(mousePos);
            if (e.type == Event::Closed){
                win->close();
            }
            // check for click
            if (Mouse::isButtonPressed(Mouse::Left)){
                for (int i = 0; i < 4; i++){
                    // check whether mouse cursor overlaps a catapult's outline
                    if (castle->getCatapults()[i]->getSprite()->getGlobalBounds().contains(translatedPos)){
                        arrow->spawn(castle->getCatapults()[i]->getPivot().x,castle->getCatapults()[i]->getPivot().y);
                        currentCatapult = i;
                        clickOn = true;
                        clickCount++;
                    }
                }
                if (clickCount == 0) {
                    clickOn = false;
                    arrow->spawn(-400,-400);
                }
            }
            moveCatapult(translatedPos, currentCatapult);
        }
        win->clear(Color(42,120,59));
        castle->draw(win);
        arrow->draw(win);
        win->display();
    }
}

Game::~Game(){
    delete win;
}
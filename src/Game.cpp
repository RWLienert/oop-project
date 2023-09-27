#include "Game.h"
#include <cmath>

// create window
Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title);
    win->setFramerateLimit(60);
    castle = new Castle(100,100,100);
}

// load objects
void Game::load(){
    castle->spawn(win->getSize().x,win->getSize().y);
}

// move catapults based on mouse location
void Game::moveCatapult(Vector2f translatedPos, int currentCatapult){
    if (clickOn == true) {
        // math to find the required angle to move the catapult
        Vector2f currentPosition = castle->getCatapults()[currentCatapult]->getBody()->getPosition();
        const float PI = 3.14159265;
        float difX = currentPosition.x - translatedPos.x;
        float difY = currentPosition.y - translatedPos.y;

        float rotation = (atan2(difY,difX))* 180/PI;
        castle->getCatapults()[currentCatapult]->getBody()->setRotation(rotation);
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
                    if (castle->getCatapults()[i]->getBody()->getGlobalBounds().contains(translatedPos)){
                        currentCatapult = i;
                        clickOn = true;
                        clickCount++;
                    }
                }
                if (clickCount == 0) {
                    clickOn = false;
                }
            }
            moveCatapult(translatedPos, currentCatapult);
        }
        win->clear(Color(42,120,59));
        castle->draw(win);
        win->display();
    }
}

Game::~Game(){
    delete win;
}
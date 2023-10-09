#include "Game.h"
#include <cmath>
#include <SFML/System/Clock.hpp>

// create window and objects
Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title);
    win->setFramerateLimit(60);
    castle = new Castle(140,140,"resources/castle.png");
    arrow = new Arrow("resources/arrow.png");
    maxEnemies = 10;
    onagers = new Onager*[maxEnemies];
    for (int i = 0; i < maxEnemies; i++) {
        onagers[i] = new Onager(30,30);
    }
}

// load objects
void Game::load(){
    spawnCount = 0;
    castle->spawn(win->getSize().x,win->getSize().y);
}

// move catapults based on mouse location
void Game::moveCatapult(Vector2f translatedPos, int currentCatapult){
    if (clickOn == true) {
        // math to find the required angle to move the catapult and fireball
        Vector2f currentPosition = castle->getCatapults()[currentCatapult]->getSprite()->getPosition();
        const float PI = 3.14159265;
        float difX = currentPosition.x - translatedPos.x;
        float difY = currentPosition.y - translatedPos.y;

        direction.x = -difX/(sqrt(difX*difX+difY*difY));
        direction.y = -difY/(sqrt(difX*difX+difY*difY));

        // Equation describes where the fireball's path starts
        float startX = currentPosition.x + 40 * direction.x;
        float startY = currentPosition.y + 40 * direction.y;

        startPos.x = startX;
        startPos.y = startY;

        // calculate the distance between mouse and catapult
        power = sqrt(difX*difX+difY*difY);
        if (power > 300) {
            power = 300;
        }

        // alter the arrow's length and colour based on position
        arrow->getSprite()->setScale(1.5+(power*0.002),1.5);
        arrow->getBar()->setScale(1+(power*0.0013),1);
        arrow->getBar()->setFillColor(Color(227, 206-power/2, 18));

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
    Clock clock;
    while (win->isOpen()){
        Time deltaTime = clock.restart();
        Event e;
        while (win->pollEvent(e)){
            // calculate position
            int clickCount = 0;
            Vector2i mousePos = Mouse::getPosition(*win);
            Vector2f translatedPos = win->mapPixelToCoords(mousePos);
            switch(e.type){
                case Event::Closed:
                    win->close();
                    break;
                case Event::KeyPressed:
                    if(e.key.code == Keyboard::Escape){
                        win->close();
                    }
                    break;
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
                    if (clickOn == true){
                        // Allows the fireball to be fired and to reload the bullets
                        castle->getCatapults()[currentCatapult]->updateFire(power,startPos,direction);
                        castle->getCatapults()[currentCatapult]->fire(startPos.x,startPos.y);
                        if (castle->getCatapults()[currentCatapult]->remaining() <= 0){
                            castle->getCatapults()[currentCatapult]->reload();
                        }
                    }
                    clickOn = false;
                    arrow->spawn(-400,-400);
                }
            }
            moveCatapult(translatedPos, currentCatapult);
        }
        win->clear(Color(42,120,59));
        castle->draw(win);
        enemySpawnTimer += deltaTime.asMilliseconds();
        if (enemySpawnTimer >= enemySpawnInterval && spawnCount < maxEnemies){
            onagers[spawnCount]->spawn(win->getSize().x, win->getSize().y);
            enemySpawnTimer = 0.0f; // Reset the timer
            spawnCount++;
        }
        arrow->draw(win);
        for (int i = 0; i < maxEnemies; i++){
            onagers[i]->draw(win);
        }
        win->display();
    }
}

Game::~Game(){
    delete win;
    delete castle;
    delete arrow;
}
#include "Game.h"
#include <cmath>
#include <SFML/System/Clock.hpp>

// create window and objects
Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title,Style::Default);
    mainMenu = new Menu(win->getSize().x, win->getSize().y);
    win->setFramerateLimit(60);
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
    // set background and import textures for other pages
    RectangleShape background;
    background.setSize(Vector2f(1300, 800));
    Texture mainTexture;
    Texture secondaryTexture;
    Texture grassTexture;
    mainTexture.loadFromFile("resources/background.jpg");
    secondaryTexture.loadFromFile("resources/landscape.jpg");
    grassTexture.loadFromFile("resources/grass.png");
    background.setTexture(&mainTexture);

    // define text for instructions
    Text instructions;
    Text level;
    Text kills;
    Text time;
    Font* font = mainMenu->getFont();
    instructions.setFont(*font);
    instructions.setFillColor(Color::Black);
    instructions.setString("How to Play: \n Defend your castle from the swarms of enemies and \n Survive until the time runs out! You have four lives \n which can be lost if an enemy reaches your castle or \n you get hit by a fireball. Shoot by clicking on a \n catapult, and then moving the cursor. Another click \n will launch it at the enemies! \n \n Can you be the King of the Hill?");
    instructions.setCharacterSize(35);
    instructions.setPosition(600,150);
    level.setFont(*font);
    level.setFillColor(Color(204, 204, 188));
    level.setString("Level: 1");
    level.setCharacterSize(45);
    level.setPosition(10,10);
    kills.setFont(*font);
    kills.setFillColor(Color(204, 204, 188));
    kills.setString("Kills: 0");
    kills.setCharacterSize(45);
    kills.setPosition(10,50);
    time.setFont(*font);
    time.setFillColor(Color(204, 204, 188));
    time.setString("Time: 50");
    time.setCharacterSize(45);
    time.setPosition(10,90);

    // defines which page is being selected
    int page = -1;

    clickOn = false;
    Clock clock;
    while (win->isOpen()){
        Time deltaTime = clock.restart();
        Event e;
        while (win->pollEvent(e)){
            switch(e.type){
                // logic for closing window
                case Event::Closed:
                    win->close();
                    break;
                case Event::KeyPressed:
                    if(e.key.code == Keyboard::Escape && page == 0){
                        page = -1;
                        background.setTexture(&mainTexture);
                    }
                    else if (e.key.code == Keyboard::Escape){
                       win->close(); 
                    }
                    break;
            }

            // defines keypresses to use the menu
            if (e.type == Event::KeyReleased){
                if (e.key.code == Keyboard::Up){
                    mainMenu->moveUp();
                }

                if (e.key.code == Keyboard::Down){
                    mainMenu->moveDown();
                }

                if (e.key.code == Keyboard::Return){
                    int x = mainMenu->mainMenuPressed();

                    // enters game
                    if (x == 0){
                        win->clear();
                        background.setTexture(&grassTexture);
                        page = x;

                        // initialise game objects
                        castle = new Castle(140,140,"resources/castle.png");
                        arrow = new Arrow("resources/arrow.png");
                        maxEnemies = 10;
                        onagers = new Onager*[maxEnemies];
                        for (int i = 0; i < maxEnemies; i++) {
                            onagers[i] = new Onager(30,30);
                        }
                        rams = new Ram*[maxEnemies];
                        for (int i = 0; i < maxEnemies; i++) {
                            rams[i] = new Ram(30,30, "resources/ram.png");
                        }
                        
                        load();
                    }

                    // enters the high score page
                    if (x == 1){
                        background.setTexture(&secondaryTexture);
                        page = x;
                    }

                    // enters the instructions page
                    if (x == 2){
                        background.setTexture(&secondaryTexture);
                        page = x;
                    }

                    // exit program
                    if (x == 3)
                        win->close();
                    break;
                }
            }
            
            if (page == 0){

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
        }

        if (page != 0){
            // shows menu until the game is entered
            win->clear();
            win->draw(background);
            mainMenu->draw(*win);
        }

        // gameloop for the game
        if (page == 0){
            win->clear();
            win->draw(background);
            win->draw(level);
            win->draw(kills);
            win->draw(time);
            castle->draw(win);
            enemySpawnTimer += deltaTime.asMilliseconds();
            if (enemySpawnTimer >= enemySpawnInterval && spawnCount < maxEnemies){
                onagers[spawnCount]->spawn(win->getSize().x, win->getSize().y);
                rams[spawnCount]->spawn(win->getSize().x, win->getSize().y);
                enemySpawnTimer = 0.0f; // Reset the timer
                spawnCount++;
            }

            // enemy movement

            Vector2f castlePos = castle->getPosition();
            for (int i = 0; i < maxEnemies; i++){
                if (onagers[i]->getAlive() == true){
                    onagers[i]->movePath(castlePos);
                }
                if (rams[i]->getAlive() == true){
                    rams[i]->movePath(castlePos);
                }
            }

            // collision code for enemies and castle
            for (int i = 0; i < maxEnemies; i++){
                if (onagers[i]->getAlive() == true && onagers[i]->getPosition().x > castle->getPosition().x - 90 && onagers[i]->getPosition().x < castle->getPosition().x + 90 && onagers[i]->getPosition().y > castle->getPosition().y - 90 && onagers[i]->getPosition().y < castle->getPosition().y + 90){
                    onagers[i]->setAlive(false);
                }
                if (rams[i]->getAlive() == true && rams[i]->getPosition().x > castle->getPosition().x - 90 && rams[i]->getPosition().x < castle->getPosition().x + 90 && rams[i]->getPosition().y > castle->getPosition().y - 90 && rams[i]->getPosition().y < castle->getPosition().y + 90){
                    rams[i]->setAlive(false);
                }
            }

            // collision code for fireballs and enemies
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 3; j++){
                    Vector2f firePos = *(castle->getCatapults()[i]->getFireballs()[j]->getFirePos());
                    if (firePos.x != -100 && firePos.y != -100){
                        for (int k = 0; k < maxEnemies; k++){
                            if (onagers[k]->getPosition().x > firePos.x - 50 && onagers[k]->getPosition().x < firePos.x + 50 && onagers[k]->getPosition().y > firePos.y - 50 && onagers[k]->getPosition().y < firePos.y + 50){
                                onagers[k]->setAlive(false);
                                firePos.x = -100;
                                firePos.y = -100;
                            }
                            if (rams[k]->getPosition().x > firePos.x - 50 && rams[k]->getPosition().x < firePos.x + 50 && rams[k]->getPosition().y > firePos.y - 50 && rams[k]->getPosition().y < firePos.y + 50){
                                rams[k]->setAlive(false);
                                firePos.x = -100;
                                firePos.y = -100;
                            }
                        }
                    }
                }
            }

            arrow->draw(win);
            for (int i = 0; i < maxEnemies; i++){
                onagers[i]->draw(win);
                rams[i]->draw(win);
            }
        }

        if (page == 2){
            win->draw(instructions);
        }

        win->display();
    }
}

Game::~Game(){
    delete win;
    delete mainMenu;
    delete castle;
    delete arrow;
}
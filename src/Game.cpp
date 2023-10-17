#include "Game.h"
#include <cmath>
#include <SFML/System/Clock.hpp>
#include <sstream>

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

// Utilised to concatenate variables together to print them on the screen
template <typename T, typename U> string toString(T text, U arg){
    stringstream ss;
    ss << text << arg;
    return ss.str();
}

// game loop
void Game::run(){
    UnitTest unitTest;
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

    // define text for game
    Text instructions;
    Text highscore;
    Text level;
    Text kills;
    Text time;
    Text lives;
    Text end;
    Font* font = mainMenu->getFont();
    instructions.setFont(*font);
    instructions.setFillColor(Color::Black);
    instructions.setString("How to Play: \n Defend your castle from the swarms of enemies and \n Survive until the time runs out! You have four lives \n which can be lost if an enemy reaches your castle or \n you get hit by a fireball. Shoot by clicking on a \n catapult, and then moving the cursor. Another click \n will launch it at the enemies! \n \n Can you be the King of the Hill?");
    instructions.setCharacterSize(35);
    instructions.setPosition(600,150);
    highscore.setFont(*font);
    highscore.setFillColor(Color::Black);
    highscore.setString("Current Max:");
    highscore.setCharacterSize(50);
    highscore.setPosition(820,160);
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
    lives.setFont(*font);
    lives.setFillColor(Color(204, 204, 188));
    lives.setString("Lives: 4");
    lives.setCharacterSize(45);
    lives.setPosition(10,130);
    end.setFont(*font);
    end.setFillColor(Color(204, 204, 188));
    end.setString("GAME OVER!");
    end.setCharacterSize(45);
    end.setPosition(800,240);

    // defines which page is being selected
    int page = -1;

    // initialise the score variables
    bool scoreRead = false;
    int highLevel, lowTime, maxKilled;

    // initialise the timer
    int countdown = 61;

    Clock clock;
    Clock clock2;
    Time elapsed;
    clickOn = false;
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
                        gameRun = false;
                        background.setTexture(&mainTexture);
                    }
                    else if (e.key.code == Keyboard::Escape){
                       win->close(); 
                    }
                    break;
            }

            // defines keypresses to use the menu
            if (e.type == Event::KeyReleased && gameRun == false){
                if (e.key.code == Keyboard::Up){
                    mainMenu->moveUp();
                }

                if (e.key.code == Keyboard::Down){
                    mainMenu->moveDown();
                }

                if (e.key.code == Keyboard::Return){
                    int x = mainMenu->mainMenuPressed();

                    // enters game from menu
                    if (x == 0){
                        // clear variables and environment
                        win->clear();
                        gameOver = false;
                        gameRun = true;
                        clickOn = false;
                        Level = 1;
                        Lives = 4;
                        Kills = 0;
                        level.setPosition(10,10);
                        level.setFillColor(Color(204, 204, 188));
                        kills.setPosition(10,50);
                        kills.setFillColor(Color(204, 204, 188));
                        time.setPosition(10,90);
                        time.setFillColor(Color(204, 204, 188));
                        deltaTime = clock.restart();
                        countdown = 61;
                        background.setTexture(&grassTexture);
                        page = x;

                        // initialise game objects
                        castle = new Castle(140,140,"resources/castle.png");
                        arrow = new Arrow("resources/arrow.png");
                        onagers = new Onager*[maxEnemies];
                        for (int i = 0; i < maxEnemies; i++) {
                            onagers[i] = new Onager(40,40,"resources/onager.png");
                        }
                        rams = new Ram*[maxEnemies];
                        for (int i = 0; i < maxEnemies; i++) {
                            rams[i] = new Ram(50,30, "resources/ram.png");
                        }
                        
                        load();
                        unitTest.runObjectTests(win,castle,arrow,onagers,rams,maxEnemies);
                        unitTest.runStatTests(Level, Kills, page, countdown);
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
            
            // Logic for shooting
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

            if (gameOver == true && page == -1){
                win->draw(end);
                level.setPosition(850,310);
                time.setPosition(850,350);
                kills.setPosition(850,390);
                win->draw(level);
                win->draw(time);
                win->draw(kills);
            }
        }

        // gameloop for the game
        if (page == 0){
            // runs clock countdown
            elapsed = clock2.getElapsedTime();
            if (elapsed.asSeconds() >= 1){
                countdown--;
                clock2.restart();
            }
            if (countdown == 0){
                // reset window for new level
                Level++;
                clock2.restart();
                countdown = 60;
                maxEnemies += 1;
                enemySpawnInterval -= 200;

                win->clear();
                clickOn = false;
                deltaTime = clock.restart();
                background.setTexture(&grassTexture);

                // initialise game objects
                arrow = new Arrow("resources/arrow.png");
                maxEnemies = 10;
                onagers = new Onager*[maxEnemies];
                for (int i = 0; i < maxEnemies; i++) {
                    onagers[i] = new Onager(40,40,"resources/onager.png");
                }
                rams = new Ram*[maxEnemies];
                for (int i = 0; i < maxEnemies; i++) {
                    rams[i] = new Ram(50,30, "resources/ram.png");
                }
                spawnCount = 0;
            }

            win->clear();
            win->draw(background);

            // incrementally add enemies to page
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
                int space = 105;
                if (onagers[i]->getAlive() == true && onagers[i]->getPosition().x > castle->getPosition().x - space && onagers[i]->getPosition().x < castle->getPosition().x + space && onagers[i]->getPosition().y > castle->getPosition().y - space && onagers[i]->getPosition().y < castle->getPosition().y + space){
                    onagers[i]->setAlive(false);
                    Lives -= 1;
                }
                if (rams[i]->getAlive() == true && rams[i]->getPosition().x > castle->getPosition().x - space && rams[i]->getPosition().x < castle->getPosition().x + space && rams[i]->getPosition().y > castle->getPosition().y - space && rams[i]->getPosition().y < castle->getPosition().y + space){
                    rams[i]->setAlive(false);
                    Lives -= 1;
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
                                Kills++;
                            }
                            if (rams[k]->getPosition().x > firePos.x - 50 && rams[k]->getPosition().x < firePos.x + 50 && rams[k]->getPosition().y > firePos.y - 50 && rams[k]->getPosition().y < firePos.y + 50){
                                rams[k]->setAlive(false);
                                Kills++;
                            }
                        }
                        firePos.x = -100;
                        firePos.y = -100;
                        castle->getCatapults()[i]->getFireballs()[j]->setFirePos(firePos);
                    }
                }
            }
            for (int i = 0; i < maxEnemies; i++){
                Vector2f firePos = *(onagers[i]->getOnagerFireball()[0]->getFirePos());
                if (firePos.x != -100 && firePos.y != -100){
                    if (firePos.x > castle->getPosition().x - 550 && firePos.x < castle->getPosition().x + 550 && firePos.y > castle->getPosition().y - 550 && firePos.y < castle->getPosition().y + 550) {
                        Lives -= 1;
                    }
                    firePos.x = -100;
                    firePos.y = -100;
                    onagers[i]->getOnagerFireball()[0]->setFirePos(firePos);
                }
            }
            // draw objects
            for (int i = 0; i < maxEnemies; i++){
                onagers[i]->draw(win);
                rams[i]->draw(win);
                if (onagers[i]->getInPosition() == true){
                    for (int j = 0; j < 3; j++){
                        if (onagers[i]->getRand()[j] == countdown){
                            onagers[i]->fire();
                        }
                    }
                }
            }


            win->draw(level);
            win->draw(kills);
            win->draw(time);

            // logic for game over
            if (Lives <= 0){
                gameOver = true;
                gameRun = false;
                page = -1;
                background.setTexture(&grassTexture);

                // open file and get variables
                ifstream readFile;
                readFile.open("resources/highscore.txt");

                if (readFile.is_open()){
                    readFile >> highLevel >> lowTime >> maxKilled;
                }
                readFile.close();

                // open file and enter variables
                ofstream writeFile("resources/highscore.txt");
                
                if (writeFile.is_open()){
                    if (Level > highLevel || (Level == highLevel && countdown < lowTime)){
                        writeFile << "";
                        writeFile << Level << " " << countdown << " " << Kills;
                    }
                }
            }

            // print stats to window
            level.setString(toString<string,int>("Level: ", Level));
            kills.setString(toString<string,int>("Kills: ", Kills));
            time.setString(toString<string,int>("Time: ", countdown));
            lives.setString(toString<string,int>("Lives: ", Lives));
            win->draw(lives);

            castle->draw(win);
            arrow->draw(win);
        }

        // highscore page logic
        if (page == 1){
            if (scoreRead == false){
                ifstream readFile;
                readFile.open("resources/highscore.txt");

                if (readFile.is_open()){
                    readFile >> highLevel >> lowTime >> maxKilled;
                }
                readFile.close();
                scoreRead = true;
            }

            // load and adjust text
            level.setPosition(850,210);
            time.setPosition(850,250);
            kills.setPosition(850,290);
            level.setFillColor(Color(105, 80, 78));
            kills.setFillColor(Color(105, 80, 78));
            time.setFillColor(Color(105, 80, 78));
            level.setString(toString<string,int>("Level: ", highLevel));
            time.setString(toString<string,int>("Time: ", lowTime));
            kills.setString(toString<string,int>("Kills: ", maxKilled));
            win->draw(level);
            win->draw(time);
            win->draw(kills);
            win->draw(highscore);
        }
        else{
            scoreRead = false;
        }

        if (page == 2){
            win->draw(instructions);
        }

        win->display();
    }
}

// initialise static variables
float Game::enemySpawnInterval = 5000;
int Game::maxEnemies = 4;
int Game::Lives = 4;
int Game::Kills = 0;
int Game::Level = 1;

Game::~Game(){
    delete win;
    delete mainMenu;
    delete castle;
    delete arrow;
}
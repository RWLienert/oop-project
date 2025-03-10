// This class is responsible for running the main game code. It handles all of the screen text, game objects and the loop that runs within the program.

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Castle.h"
#include "Arrow.h"
#include "Onager.h"
#include "UnitTest.h"
#include "Ram.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace sf;
using namespace std;

class Game{
    protected:
        RenderWindow* win;
        Menu* mainMenu;
        Castle* castle;
        Arrow* arrow;
        Onager** onagers;
        Ram** rams;
        bool clickOn;
        int currentCatapult;
        Vector2f startPos;
        Vector2f direction;
        float power;
        static int Lives;
        static int Kills;
        static int Level;
        bool gameOver;
        bool gameRun;
        static int maxEnemies;
        int spawnCount;
        float enemySpawnTimer;
        static float enemySpawnInterval;
    public:
        Game(int width, int height, string title);
        void load();
        void run();
        void moveCatapult(Vector2f translatedPos, int currentCatapult);
        ~Game();
};

#endif
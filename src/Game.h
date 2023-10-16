#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Castle.h"
#include "Arrow.h"
#include "Onager.h"
#include "Ram.h"
#include <iostream>
#include <string>
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
        bool gameOver;
        int maxEnemies;
        int spawnCount;
        float enemySpawnTimer;
        float enemySpawnInterval = 5000;
    public:
        Game(int width, int height, string title);
        void load();
        void run();
        void moveCatapult(Vector2f translatedPos, int currentCatapult);
        ~Game();
};

#endif
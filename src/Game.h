#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Castle.h"
#include "Arrow.h"
#include "Onager.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Game{
    protected:
        RenderWindow* win;
        Castle* castle;
        Arrow* arrow;
        Onager** onagers;
        bool clickOn;
        int currentCatapult;
        Vector2f startPos;
        Vector2f direction;
        float power;
        int lives;
        int maxEnemies;
        int spawnCount;
        float enemySpawnTimer;
        float enemySpawnInterval = 2000;
    public:
        Game(int width, int height, string title);
        void load();
        void run();
        void moveCatapult(Vector2f translatedPos, int currentCatapult);
        ~Game();
};

#endif
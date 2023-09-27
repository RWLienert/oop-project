#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Castle.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Game{
    protected:
        RenderWindow* win;
        Castle* castle;
        bool clickOn;
        int currentCatapult;
    public:
        Game(int width, int height, string title);
        void load();
        void run();
        void moveCatapult(Vector2f translatedPos, int currentCatapult);
        ~Game();
};

#endif
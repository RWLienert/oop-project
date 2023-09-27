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
    public:
        Game(int width, int height, string title);
        void load();
        void run();
        ~Game();
};

#endif
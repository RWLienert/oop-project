#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Game{
    private:
        RenderWindow* win;
    public:
        Game(int width, int height, string title);
        void run();
        ~Game();
};

#endif
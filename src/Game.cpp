#include <iostream>
#include "Game.h"

Game::Game(int width, int height,string title) {
    win = new RenderWindow(VideoMode(width,height),title);
}


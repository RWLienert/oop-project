#include <iostream>
#include "Game.h"

Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title);
}

void Game::run(){
    while (win->isOpen()){
        Event e;
        while (win->pollEvent(e)){
            if (e.type == Event::Closed){
                win->close();
            }
        }
        win->clear();
        win->display();
    }
}

Game::~Game(){
    delete win;
}
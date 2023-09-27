#include "Game.h"

// create window
Game::Game(int width, int height,string title){
    win = new RenderWindow(VideoMode(width,height),title);
    castle = new Castle(100,80,80);
}

// load objects
void Game::load(){
    castle->spawn(win->getSize().x,win->getSize().y);
}

// game loop
void Game::run(){
    load();
    while (win->isOpen()){
        Event e;
        while (win->pollEvent(e)){
            if (e.type == Event::Closed){
                win->close();
            }
        }
        win->clear();
        castle->draw(win);
        win->display();
    }
}

Game::~Game(){
    delete win;
}
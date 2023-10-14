#ifndef MENU_H
#define MENU_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Menu{
    protected:
        int mainMenuSelected;
        static const int maxMainMenu = 4;
        Font font;
        Text MainMenu[maxMainMenu];
    public:
        Menu(float width, float height);
        void draw(RenderWindow& window);
        void moveUp();
        void moveDown();
        int mainMenuPressed();
        Font* getFont();
        ~Menu();
};

#endif
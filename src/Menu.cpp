#include "Menu.h"

Menu::Menu(float width, float height){
    if (!font.loadFromFile("resources/gameFont.ttf")){
        cout << "Font didn't load" << endl;
    }

    //Play
    MainMenu[0].setFont(font);
    MainMenu[0].setFillColor(Color::Black);
    MainMenu[0].setString("Play");
    MainMenu[0].setCharacterSize(70);
    MainMenu[0].setPosition(200, 100);
    //Highscore
    MainMenu[1].setFont(font);
    MainMenu[1].setFillColor(Color::Black);
    MainMenu[1].setString("High Score");
    MainMenu[1].setCharacterSize(70);
    MainMenu[1].setPosition(200,200);
    //Instructions
    MainMenu[2].setFont(font);
    MainMenu[2].setFillColor(Color::Black);
    MainMenu[2].setString("Instructions");
    MainMenu[2].setCharacterSize(70);
    MainMenu[2].setPosition(200,300);
    //Exit
    MainMenu[3].setFont(font);
    MainMenu[3].setFillColor(Color::Black);
    MainMenu[3].setString("Exit");
    MainMenu[3].setCharacterSize(70);
    MainMenu[3].setPosition(200,400);

    navigate.setFont(font);
    navigate.setFillColor(Color(204, 204, 188));
    navigate.setString("Press Up & Down Keys to Navigate");
    navigate.setCharacterSize(35);
    navigate.setPosition(20,730);


    mainMenuSelected = -1;
}

Menu::~Menu(){
}

//Draw MainMenu
void Menu::draw(RenderWindow& win){
    for (int i = 0; i < maxMainMenu; ++i){
        win.draw(MainMenu[i]);
        win.draw(navigate);
    }
}

//Moveup
void Menu::moveUp()
{
    // logic for switching menu elements with the up key
    if (mainMenuSelected - 1 >= 0){
        MainMenu[mainMenuSelected].setFillColor(Color::Black);
        for (int i = 0; i < maxMainMenu; i++){
            MainMenu[i].setOutlineThickness(0);
        }

        mainMenuSelected--;
        if (mainMenuSelected == -1){
            mainMenuSelected = maxMainMenu - 1;
        }
        MainMenu[mainMenuSelected].setFillColor(Color(246,244,185));
        MainMenu[mainMenuSelected].setOutlineThickness(3);
        MainMenu[mainMenuSelected].setOutlineColor(Color::Black);
    }
}

//Move Down
void Menu::moveDown(){
    // logic for switching menu elements with the down key
    if (mainMenuSelected + 1 < maxMainMenu){
        MainMenu[mainMenuSelected].setFillColor(Color::Black);
        for (int i = 0; i < maxMainMenu; i++){
            MainMenu[i].setOutlineThickness(0);
        }

        mainMenuSelected++;
        if (mainMenuSelected == maxMainMenu){
            mainMenuSelected = 0;
        }
        MainMenu[mainMenuSelected].setFillColor(Color(246,244,185));
        MainMenu[mainMenuSelected].setOutlineThickness(3);
        MainMenu[mainMenuSelected].setOutlineColor(Color::Black);
    }
}

int Menu::mainMenuPressed(){
    return mainMenuSelected;
}

Font* Menu::getFont(){
    return &font;
}
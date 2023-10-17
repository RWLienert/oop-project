#ifndef TESTS_H
#define TESTS_H

#include "Castle.h"
#include "Ram.h"

// Due to the nature of Enemy and Entity being abstract classes, these cannot be tested

class UnitTest {
    private:
        void testCastle(Window* win, Castle* castle){
            if (castle->getPosition().x < (0.2 * win->getSize().x) || castle->getPosition().x > (0.7 * win->getSize().x)){
                cout << castle->getPosition().x << endl;
                cout << castle->getPosition().y << endl;
                cout << win->getSize().x << endl;
                cout << win->getSize().y << endl;
                cout << "Error in castle positioning" << endl;
            }

            if (castle->getAlive() != true){
                cout << "Castle is not on the screen" << endl;
            }
            
            if (castle->getCatapults()[5] == nullptr){
                cout << "Too many catapults" << endl;
            }
        }

        void testArrow(Window* win, Arrow* arrow){
            if (arrow->getAlive() == true){
                cout << "Arrow was instantiated wrong" << endl;
            }
            if ((arrow->getPosition().x < win->getSize().x && arrow->getPosition().x > 0) || (arrow->getPosition().y < win->getSize().y && arrow->getPosition().y > 0)){
                cout << "Arrow was positioned incorrectly" << endl;
            }
        }

        void testOnagers(Window* win, Onager** onagers, int maxEnemies){
            for (int i = 1; i < maxEnemies; i++){
                if (onagers[i]->getAlive() == true){
                    cout << "Spawning of onagers is incorrect at run";
                }
            }
        }

        void testRams(Window* win, Ram** rams, int maxEnemies){
            for (int i = 1; i < maxEnemies; i++){
                if (rams[i]->getAlive() == true){
                    cout << "Spawning of rams is incorrect at run";
                }
            }
        }

    public:
        void runObjectTests(Window* win, Castle* castle, Arrow* arrow, Onager** onagers, Ram** rams, int maxEnemies){
            testCastle(win, castle);
            testArrow(win, arrow);
            testOnagers(win,onagers,maxEnemies);
            testRams(win,rams,maxEnemies);
        }
};

#endif
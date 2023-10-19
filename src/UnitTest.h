// This function tests most of the code within the other classes to ensure that it works and is functioning correctly. It will print out the error, if a problem occurs

#ifndef TESTS_H
#define TESTS_H

#include "Castle.h"
#include "Ram.h"
#include <cmath>
#include <sstream>

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

        void testLevel(int Level){
            if (Level != 1){
                cout << "Level has been initialised incorrectly" << endl;
            }
        }

        void testKills(int Kills){
            if (Kills != 0){
                cout << "Kills has been initialised incorrectly" << endl;
            }
        }

        void testPage(int page){
            if (page != 0){
                cout << "Pages have been initialised incorrectly" << endl;
            }
        }

        void testCountdown(int countdown){
            if (countdown < 0 || countdown > 61){
                cout << "The clock timer has been initialised incorrectly" << endl;
            }
        }

        void testFile(int highLevel, int lowTime, int maxKilled){
            if (highLevel < 0){
                cout << "Level scores were incorrectly read (-ve)" << endl;
            }
            if (lowTime > 61 || lowTime < 0){
                cout << "Timing scores were incorrectly read (Outside 0 - 60)" << endl;
            }
            if (maxKilled < 0){
                cout << "Kill count score was incorrectly read (-ve)";
            }
        }

        void testBackground(RectangleShape background, Texture* texture){
            if (background.getTexture() != texture){
                cout << "Background has not been correctly allocated to the scene" << endl;
            }
            if (background.getSize().x != 1300 && background.getSize().y != 800){
                cout << "Background sizing doesn't fit screen" << endl;
            }
        }

        void testDraw(Onager* onager, Castle* castle){
            if (sqrt(pow(onager->getPosition().x-castle->getPosition().x,2)+pow(onager->getPosition().y-castle->getPosition().y,2)) > 301 && onager->getInPosition() == true){
                cout << "In position has been miscalculated" << endl;
            }

            for (int i = 0; i < 3; i++){
                if (onager->getRand()[i] < 0 || onager->getRand()[i] > 60){
                    cout << "Onager's random function is wrong!";
                }
            }
        }

        void testFire(Vector2f firePos){
            if (firePos.x != -100 && firePos.y != -100){
                cout << "The firing positions that are used for collision haven't been reset";
            }
        }

        void testText(Text level, Text kills, Text time, Text lives, int Level, int Kills, int countdown, int Lives){
            stringstream str1, str2, str3, str4;
            str1 << "Level: " << Level;
            str2 << "Kills: " << Kills;
            str3 << "Time: " << countdown;
            str4 << "Lives: " << Lives;
            if (level.getString() != str1.str()){
                cout << "Levels are not being displayed correctly";
            }
            if (kills.getString() != str2.str()){
                cout << "Kills are not being displayed correctly";
            }
            if (time.getString() != str3.str()){
                cout << "Time is not being displayed correctly";
            }
            if (lives.getString() != str4.str()){
                cout << "Lives are not being displayed correctly";
            }
        }

        void testHighScore(int Level, int highLevel, int countdown, int lowTime){
            if (Level < highLevel){
                cout << "High score were incorrectly allocated after game (Level)" << endl;
            }
            if (Level == highLevel && countdown > lowTime) {
                cout << "High score were incorrectly allocated after game (Time)" << endl;
            }
        }

    public:
        void runObjectTests(Window* win, Castle* castle, Arrow* arrow, Onager** onagers, Ram** rams, int maxEnemies){
            testCastle(win, castle);
            testArrow(win, arrow);
            testOnagers(win,onagers,maxEnemies);
            testRams(win,rams,maxEnemies);
        }

        void runStatTests(int Level, int Kills, int page, int countdown){
            testLevel(Level);
            testKills(Kills);
            testPage(page);
            testCountdown(countdown);
        }

        void runFileTests(int highLevel, int lowTime, int maxKilled){
            testFile(highLevel, lowTime, maxKilled);
        }

        void runBackgroundTests(RectangleShape background, Texture* texture){
            testBackground(background, texture);
        }

        void runDrawTests(Onager* onager, Castle* castle){
            testDraw(onager, castle);
        }

        void runFireTests(Vector2f firePos){
            testFire(firePos);
        }

        void runTextTests(Text level, Text kills, Text time, Text lives, int Level, int Kills, int countdown, int Lives){
            testText(level,kills,time,lives,Level,Kills,countdown,Lives);
        }

        void runHighScoreTests(int Level, int highLevel, int countdown, int lowTime){
            testHighScore(Level, highLevel, countdown, lowTime);
        }
};

#endif
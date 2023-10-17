#ifndef TESTS_H
#define TESTS_H

#include "Castle.h"

// Due to the nature of Enemy and Entity being abstract classes, these cannot be tested

class UnitTest {
    private:
        void testCastlePos(Window* win, Castle* castle){
            if (castle->getPosition().x > 100){
                cout << castle->getPosition().x << endl;
                cout << castle->getPosition().y << endl;
                cout << win->getSize().x << endl;
                cout << win->getSize().y << endl;
                cout << "Error in castle positioning" << endl;
            }
        }
    public:
        void runTests(Window* win, Castle* castle){
            testCastlePos(win, castle);
        }
};

#endif
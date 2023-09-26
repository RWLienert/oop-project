#include <criterion/criterion.h>
#include "../src/Game.h"

Test(windowtests, create) {
    Game game(1000,700,"Fortress Fury");
    cr_expect( "game should not crash");
}
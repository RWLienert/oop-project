#include <criterion/criterion.h>
#include "../src/Castle.h"

Test(castletests, create) {
    Castle castle(80,80,"../resources/castle.png");
    cr_expect("Castle class initialisation broke");
    castle.spawn(1000,1000);
    cr_expect("Castle isn't spawning");
}
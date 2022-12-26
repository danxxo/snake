#include <unistd.h>
#include "Game.h"

int main() {
    Game game(15 , 20, 20);
    game.RenderLoop();

    return 0;
}

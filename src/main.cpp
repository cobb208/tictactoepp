#include <iostream>
#include "Game.h"

int main() {
    Game *game = new Game();
    game->Game_loop();
    delete(game);
}

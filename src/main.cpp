#include <SFML/Graphics.hpp>
#include "GameHandler.h"

int main() {
    GameHandler* game = new GameHandler(3,0);
    game->run();

    return 0;
}

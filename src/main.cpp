#include <SFML/Graphics.hpp>
#include "GameHandler.h"
#include <iostream>

int main() {
    int size = 0;
    bool start = false;
    std::cout << "AI TIC TAC TOE" << std::endl;

    while(size <= 0){
        std::cout << "Size of the grid: " << std::endl;
        std::cin >> size;
        std::cout << std::endl;
    }

    std::cout << "Do you want to start? (1/0)" << std::endl;
    std::cin >> start;
    std::cout << std::endl;

    GameHandler* game = new GameHandler(size,start);
    game->run();
    delete game;

    return 0;
}

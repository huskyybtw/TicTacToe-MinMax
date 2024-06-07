//
// Created by marek on 07.06.2024.
//

#ifndef CMAKESFMLPROJECT_GAMEHANDLER_H
#define CMAKESFMLPROJECT_GAMEHANDLER_H

#include <SFML/Graphics.hpp>

struct Cell{
    sf::RectangleShape cell;
    int elem = 0;

};

class GameHandler {
    std::vector<Cell> Grid;
    sf::RenderWindow window;
    int rows;
    int cols;
    int cellSize;

    bool playerTurn;
    int maxMoves;
    bool checkWin();
    void MouseAction(sf::Vector2<float> mousePos);
    public:
        GameHandler(int size,bool playerTurn);
        void run();

};


#endif //CMAKESFMLPROJECT_GAMEHANDLER_H

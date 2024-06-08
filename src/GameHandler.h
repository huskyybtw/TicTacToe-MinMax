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
    int checkWin(std::vector<Cell> GameState, int size);
    void MouseAction(sf::Vector2<float> mousePos);

    // AI RELATED FUNCTIONS -> MINMAX.CPP
    float heuristicScore(std::vector<Cell> prevGameState ,int size);
    int evaluateLine(int player1Count, int player2Count);
    void BestMove();
    float MiniMax(std::vector<Cell> GameState, int depth, bool isMaximizing, float alpha, float beta);
    public:
        GameHandler(int size,bool playerTurn);
        void run();

};


#endif //CMAKESFMLPROJECT_GAMEHANDLER_H

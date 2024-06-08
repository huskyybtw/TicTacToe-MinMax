//
// Created by marek on 07.06.2024.
//

#include <iostream>
#include "GameHandler.h"


GameHandler::GameHandler(int size,bool playerTurn)
        : window(sf::VideoMode(800, 800), "SFML Grid Box"), rows(size), cols(size) {

    int gridBoxSize = 600;
    this->cellSize = static_cast<float>(gridBoxSize) / size;
    this->playerTurn = playerTurn;
    this->maxMoves = size * size;

    const sf::Color cellColor = sf::Color::White;
    const sf::Color gridColor = sf::Color::Black;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize + 100, row * cellSize + 100);
            cell.setOutlineThickness(1.f);
            cell.setFillColor(cellColor);
            cell.setOutlineColor(gridColor);
            Grid.push_back({cell,0});
        }
    }
}

void GameHandler::MouseAction(sf::Vector2<float> mousePos){
    for(auto& cell : Grid) {
        if(cell.cell.getGlobalBounds().contains(mousePos)) {
            if(cell.elem == 0){
                if(playerTurn) {
                    cell.cell.setFillColor(sf::Color::Red);
                    cell.elem = 1;

                    maxMoves--;
                    playerTurn = !playerTurn;
                }
            }
        }
    }
}

void GameHandler::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        for(auto& _cell : Grid) {
            window.draw(_cell.cell);
        }
        window.display();

        if(!playerTurn){
            BestMove();
            maxMoves--;
            playerTurn = !playerTurn;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            MouseAction(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        int win = checkWin(Grid,rows);

        if(win == 1){
            std::cout << "PLAYER" << " Wins" << std::endl;
            window.close();
        }

        if(win == 2){
            std::cout << "AI" << " Wins" << std::endl;
            window.close();
        }

        if(maxMoves == 0){
            std::cout << "Draw" << std::endl;
            window.close();
        }
    }
}
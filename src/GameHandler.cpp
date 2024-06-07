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

bool GameHandler::checkWin() {

    std::cout << std::endl;
    int rowWin = 0;
    for(int i=0 ; i<cols ;i = i+rows){
        if(Grid.at(i).elem != 0){
            for(int j=i ; j<rows ; j++){
                if(Grid.at(j).elem != true && Grid.at(i).elem == Grid.at(j).elem){
                    rowWin++;
                }
                else{
                    continue;
                }
            }
        }
        if(rowWin == rows){
            return true;
        }
        rowWin = 0;
    }

    int colWin = 0;
    for(int i=0 ; i<cols ; i++){
        if(Grid.at(i).elem != 0){
            for(int j=i ; j<Grid.size() ;  j = j+rows){
                if(Grid.at(j).elem != 0 && Grid.at(i).elem == Grid.at(j).elem){
                    colWin++;
                }
                else{
                    continue;
                }
            }
        }
        if(colWin == cols){
            std::cout << "Win" << std::endl;
            window.close();
        }
        colWin = 0;
    }

    // diagonal win conditon
    int diagLeftWin = 0;
    int diagLeft = 0;
    if(Grid.at(diagLeft).elem != 0){
        for(int j = diagLeft+rows+1 ; j<Grid.size() ; j = j+rows+1){
            if(Grid.at(j).elem != 0 && Grid.at(diagLeft).elem == Grid.at(j).elem){
                diagLeftWin++;
            }
            else{
                continue;
            }
        }
        if(diagLeftWin == rows-1){
            return true;
        }
    }

    int diagRightWin = 0;
    int diagRight = rows-1;
    if(Grid.at(diagRight).elem != 0){
        for(int j = diagRight+rows-1 ; j<Grid.size() ; j = j+rows-1){
            if(Grid.at(j).elem != true && Grid.at(diagRight).elem == Grid.at(j).elem){
                diagRightWin++;
            }
            else{
                continue;
            }
        }
        if(diagRightWin == rows-1){
            return true;
        }
    }

    return false;
}

void GameHandler::MouseAction(sf::Vector2<float> mousePos){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for(auto& cell : Grid) {
            if(cell.cell.getGlobalBounds().contains(mousePos)) {
                if(cell.elem == 0){
                    if(playerTurn) {
                        cell.cell.setFillColor(sf::Color::Red);
                        cell.elem = 1;
                    }
                    else {
                        cell.cell.setFillColor(sf::Color::Blue);
                        cell.elem = 2;
                    }
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            MouseAction(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            if(checkWin()){
                std::cout << !playerTurn << " Wins" << std::endl;
                window.close();
            }
        }

        if(maxMoves == 0){
            std::cout << "Draw" << std::endl;
            window.close();
        }
    }
}
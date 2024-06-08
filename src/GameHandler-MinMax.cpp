//
// Created by marek on 08.06.2024.
//
#include "GameHandler.h"

int GameHandler::checkWin(std::vector<Cell> GameState, int size){
    bool isDraw = true;
    for(int i=0 ; i<GameState.size() ; i++){
        if(GameState.at(i).elem == 0){
            isDraw = false;
        }
    }
    if(isDraw){
        return 0;
    }

    int rowWin = 0;
    for(int i=0 ; i<size ; i = i+size){
        if(GameState.at(i).elem != 0){
            for(int j=i ; j<size ; j++){
                if(GameState.at(j).elem != 0 && GameState.at(i).elem == GameState.at(j).elem){
                    rowWin++;
                }
                else{
                    break;
                }
            }
        }
        if(rowWin == size){
            return GameState.at(i).elem;
        }
        rowWin = 0;
    }

    int colWin = 0;
    for(int i=0 ; i<size ; i++){
        if(GameState.at(i).elem != 0){
            for(int j=i ; j<GameState.size() ;  j = j+size){
                if(GameState.at(j).elem != 0 && GameState.at(i).elem == GameState.at(j).elem){
                    colWin++;
                }
                else{
                    break;
                }
            }
        }
        if(colWin == size){
            return GameState.at(i).elem;
        }
        colWin = 0;
    }

    int diagLeftWin = 0;
    int diagLeft = 0;
    if(GameState.at(diagLeft).elem != 0){
        for(int j = diagLeft+size+1 ; j<GameState.size() ; j = j+size+1){
            if(GameState.at(j).elem != 0 && GameState.at(diagLeft).elem == GameState.at(j).elem){
                diagLeftWin++;
            }
            else{
                break;
            }
        }
        if(diagLeftWin == size-1){
            return GameState.at(diagLeft).elem;
        }
    }

    int diagRightWin = 0;
    int diagRight = size-1;
    if(GameState.at(diagRight).elem != 0){
        for(int j = diagRight+size-1 ; j<GameState.size() ; j = j+size-1){
            if(GameState.at(j).elem != 0 && GameState.at(diagRight).elem == GameState.at(j).elem){
                diagRightWin++;
            }
            else{
                break;
            }
        }
        if(diagRightWin == size-1){
            return GameState.at(diagRight).elem;
        }
    }

    return -1;
}

float GameHandler::heuristicScore(std::vector<Cell> GameState, int size) {
    int score = 0;

    for (int i = 0; i < size; ++i) {
        int player1Count = 0;
        int player2Count = 0;
        for (int j = 0; j < size; ++j) {
            if (GameState[i * size + j].elem == 1) player1Count++;
            if (GameState[i * size + j].elem == 2) player2Count++;
        }
        score += evaluateLine(player1Count, player2Count);
    }

    for (int i = 0; i < size; ++i) {
        int player1Count = 0;
        int player2Count = 0;
        for (int j = 0; j < size; ++j) {
            if (GameState[i + j * size].elem == 1) player1Count++;
            if (GameState[i + j * size].elem == 2) player2Count++;
        }
        score += evaluateLine(player1Count, player2Count);
    }

    int player1Count = 0;
    int player2Count = 0;
    for (int i = 0; i < size; ++i) {
        if (GameState[i * size + i].elem == 1) player1Count++;
        if (GameState[i * size + i].elem == 2) player2Count++;
    }
    score += evaluateLine(player1Count, player2Count);

    player1Count = 0;
    player2Count = 0;
    for (int i = 0; i < size; ++i) {
        if (GameState[i * size + (size - 1 - i)].elem == 1) player1Count++;
        if (GameState[i * size + (size - 1 - i)].elem == 2) player2Count++;
    }
    score += evaluateLine(player1Count, player2Count);

    return score;
}

int GameHandler::evaluateLine(int player1Count, int player2Count) {
    const int WIN_SCORE = 1000;
    const int BLOCK_OPPONENT_SCORE = 50;
    const int CREATE_OPPORTUNITY_SCORE = 10;

    if (player1Count == 0) {
        switch (player2Count) {
            case 3:
                return WIN_SCORE;
            case 2:
                return CREATE_OPPORTUNITY_SCORE;
            case 1:
                return 1;
        }
    } else if (player2Count == 0) {
        switch (player1Count) {
            case 3:
                return -WIN_SCORE;
            case 2:
                return -BLOCK_OPPONENT_SCORE;
            case 1:
                return -1;
        }
    }
    return 0;
}

void GameHandler::BestMove() {
    float bestScore = -10000;
    int bestMove = -1;
    std::vector<int> bestMoves;
    std::vector<Cell> GameState = Grid;
    float alpha = -INT_MIN;
    float beta = INT_MAX;

    for (int i = 0; i < GameState.size(); ++i) {
        if (GameState[i].elem == 0) {
            GameState[i].elem = 2;
            float score = MiniMax(GameState, 0, false, alpha, beta);
            GameState[i].elem = 0;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
                if(score == 1){
                    bestMoves.push_back(i);
                }
            }

            alpha = std::max(alpha, score);
        }
    }

    for(auto& move : bestMoves){
        if(move == ((rows*rows)/2)){
            Grid[move].elem = 2;
            Grid[move].cell.setFillColor(sf::Color::Blue);
            return;
        }
    }

    Grid[bestMove].elem = 2;
    Grid[bestMove].cell.setFillColor(sf::Color::Blue);
}

float GameHandler::MiniMax(std::vector<Cell> GameState, int depth, bool isMaximizing, float alpha, float beta) {
    int result = checkWin(GameState, rows);
    if(result != -1){
        if(result == 2){
            return 1;
        }
        else if(result == 1){
            return -1;
        }
        else{
            return 0;
        }
    }

    if(rows > 3 && depth >= rows){
        return heuristicScore(GameState, rows);
    }

    if(isMaximizing){
        float bestScore = -10000;
        for(int i=0 ; i<GameState.size() ; i++){
            if(GameState[i].elem == 0){
                GameState[i].elem = 2;
                float score = MiniMax(GameState, depth+1, false, alpha, beta);
                GameState[i].elem = 0;
                bestScore = std::max(score, bestScore);
                alpha = std::max(alpha, score);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return bestScore;
    }

    else{
        float bestScore = 10000;
        for(int i=0 ; i<GameState.size() ; i++){
            if(GameState[i].elem == 0){
                GameState[i].elem = 1;
                float score = MiniMax(GameState, depth+1, true, alpha, beta);
                GameState[i].elem = 0;
                bestScore = std::min(score, bestScore);
                beta = std::min(beta, score);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return bestScore;
    }
}
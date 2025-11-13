#pragma once
#include <iostream>
#include <vector>
#include <random>


enum class Bonus { None, Exchange, Stone, Robbery };

struct Cell {
    int used = -1;
    int owner = -1;
    std::string color = "\033[37m";
    std::string symbol = ".";
    Bonus bonus = Bonus::None;

};

class Board
{
private:
    int size;
    std::vector<Cell> grid;

public:
    Board();
    Board(int size);
    
    int getSize() {
        return size;
    }

    Cell& at(int row, int col) {
        return grid[row * size + col];
    }
    
    void seedBonuses(int numPlayer, std::mt19937& rng);
    int side() const { return size; }
    void displayBoard();
};
#pragma once
#include <iostream>
#include <vector>

struct Cell {
    int used = -1;
    int owner = -1;
    std::string color = "\033[37m";
    std::string symbol = ".";
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
    
    void displayBoard();
};
#pragma once
#include <iostream>
#include <vector>

struct Cell {
    int used = -1;
};

class Board
{
private:
    int size;
    std::vector<Cell> grid;

public:
    Board();
    Board(int size);
    
    Cell& at(int row, int col) {
        return grid[row * size + col];
    }
    
    void displayBoard();
};
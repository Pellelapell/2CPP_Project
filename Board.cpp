#include "Board.hpp"
#include <iostream>

Board::Board() : size(0), grid() {}

Board::Board(int size) : size(size), grid(size * size)
{
}

void Board::displayBoard()
{
    std::cout << "Board Size: " << size << "x" << size << std::endl;
    std::cout << "  ";
    for (int i = 0; i < size && i < size; ++i)
    {
        std::cout << char('A' + i) << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
    {
        std::cout << char('A' + i) << ' ';
        for (int j = 0; j < size; ++j)
        {
            const auto &c = at(i, j);
            if (c.used == -1)
                std::cout << c.color << c.symbol << ' ';
            else
                std::cout << c.color << c.symbol << ' ';
        }
        std::cout << std::endl;
    }
}

#include "Board.hpp" 

Board::Board() : size(0), grid() {}

Board::Board(int size) : grid(size * size) {}

void Board::displayBoard()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
           const auto& c = at(i, j);
           if (c.used == -1)
                std::cout << ". ";
              else
                std::cout << c.used << ' ';
        }
        std::cout << std::endl;
    }
}

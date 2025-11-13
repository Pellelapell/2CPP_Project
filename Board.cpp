#include "Board.hpp"
#include <iostream>
#include <cmath>

Board::Board() : size(0), grid() {}

Board::Board(int size) : size(size), grid(size * size)
{
}

void Board::displayBoard()
{
    const char* RESET = "\033[0m";
    const char* GRAY  = "\033[90m"; // for bonus markers

    std::cout << "Board Size: " << size << "x" << size << "\n  ";
    for (int j = 0; j < size; ++j)
        std::cout << char('A' + j) << ' ';
    std::cout << '\n';

    for (int i = 0; i < size; ++i)
    {
        std::cout << char('A' + i) << ' ';
        for (int j = 0; j < size; ++j)
        {
            const Cell& c = at(i, j);

            if (c.used != -1) {
                // Occupied: show colored symbol
                std::cout << c.color << c.symbol << ' ' << RESET;
            } else {
                // Empty: show bonus if any, else '.'
                char mark = '.';
                switch (c.bonus) {
                    case Bonus::Exchange: mark = 'E'; break;
                    case Bonus::Stone:    mark = 'S'; break;
                    case Bonus::Robbery:  mark = 'R'; break;
                    default:              mark = '.'; break;
                }
                std::cout << GRAY << mark << ' ' << RESET;
            }
        }
        std::cout << '\n';
    }
}



static bool inBounds(int y, int x, int N) {
    return y >= 0 && y < N && x >= 0 && x < N;
}

void Board::seedBonuses(int numPlayers, std::mt19937& rng) {
        auto needExchange = (int)std::ceil(1.5 * numPlayers);
    auto needStone    = (int)std::ceil(0.5 * numPlayers);
    auto needRobbery  = numPlayers;

    auto tryPlace = [&](Bonus b)->bool {
        if (size < 3) return false; // no interior cell exists
        std::uniform_int_distribution<int> dist(1, size - 2); // avoid edges
        for (int attempts = 0; attempts < 5000; ++attempts) {
            int y = dist(rng), x = dist(rng);

            // cell must be empty and not already a bonus
            Cell& c = at(y, x);
            if (c.used != -1 || c.bonus != Bonus::None) continue;

            // no adjacent (8-neighborhood) bonus
            bool ok = true;
            for (int dy = -1; dy <= 1 && ok; ++dy)
                for (int dx = -1; dx <= 1 && ok; ++dx) {
                    if (dy == 0 && dx == 0) continue;
                    int ny = y + dy, nx = x + dx;
                    if (inBounds(ny, nx, size) && at(ny, nx).bonus != Bonus::None)
                        ok = false;
                }

            if (!ok) continue;

            c.bonus = b;
            return true;
        }
        return false;
    };

    while (needExchange-- > 0) tryPlace(Bonus::Exchange);
    while (needStone--    > 0) tryPlace(Bonus::Stone);
    while (needRobbery--  > 0) tryPlace(Bonus::Robbery);
}
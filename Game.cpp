#include "Game.hpp"
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

Game::Game(std::vector<class Player> players, int numPlayers) : players(players),
                                                                size(numPlayers < 5 ? 20 : 30),
                                                                board(size)
{
    board.displayBoard();
    initializeTiles();
    currentRound = 1;
}

std::vector<std::string> rotateTile90Clockwise(const std::vector<std::string> &tile)
{
    if (tile.empty())
        return {};

    size_t rows = tile.size();
    size_t cols = tile[0].size();

    std::vector<std::string> rotated(cols, std::string(rows, ' '));

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            rotated[j][rows - 1 - i] = tile[i][j];
        }
    }

    return rotated;
}

Game::~Game() {}

std::vector<class Player> Game::getPlayers()
{
    return (players);
}

int Game::getSize()
{
    return (size);
}

void Game::initializeTiles()
{
    tiles =
        {
            {"100", "111"},
            {"010", "010", "111"},
            {"010", "111", "010"},
            {"001", "111", "100"},
            {"010", "111"},
            {"11", "11"},
            {"101", "111"},
            {"111"},
            {"01", "11", "10"},
            {"10", "11"},
            {"001", "011", "110"},
            {"11"},
            {"01", "11", "10", "10", "11"},
            {"111", "100", "100", "100", "100"},
            {"00010", "00010", "00011", "01110", "11000"},
            {"001", "011", "110", "100"},
            {"010", "111", "110"},
            {"111"},
            {"10", "11", "10", "10"},
            {"011", "110", "110"},
            {"010", "110", "111"},
            {"010", "010", "111", "100"},
            {"10", "11"},
            {"11", "11", "11"},
            {"111", "010", "010", "010"},
            {"1000", "1100", "0110", "0011"},
            {"11111"},
            {"100", "111", "001", "001"},
            {"10", "11", "10", "11", "10"},
            {"10", "11", "11", "10"},
            {"010", "010", "010", "111", "101"},
            {"11"},
            {"1000", "1110", "1011"},
            {"01", "01", "11", "10", "10"},
            {"1100", "0100", "0111", "1100", "1000"},
            {"10", "10", "11", "10"},
            {"01", "11", "10"},
            {"1001", "1111"},
            {"0011", "1001", "1111"},
            {"1000", "1000", "1100", "0111"},
            {"110", "011", "110", "011", "010"},
            {"10", "11", "11"},
            {"0100", "0100", "1111"},
            {"11", "11"},
            {"01", "11", "111", "111", "10"},
            {"111", "010", "110"},
            {"1111"},
            {"010", "111"},
            {"1000", "1000", "1111"},
            {"0110", "1100", "0111"},
            {"01", "11", "10", "10"},
            {"100", "111"},
            {"10", "11", "10", "10", "10"},
            {"00111", "00100", "00100", "00100", "11100"},
            {"01", "01", "11", "10", "11", "10"},
            {"1111"},
            {"1100", "0100", "0111", "0001"},
            {"010", "010", "111", "010", "010"},
            {"001", "001", "111"},
            {"1", "1", "1", "1", "1", "1"},
            {"101", "111", "010", "110"},
            {"0010", "1110", "0111", "0100"},
            {"011", "010", "010", "111"},
            {"10", "10", "11", "10", "10"},
            {"1100", "0100", "0101", "1111"},
            {"001", "011", "110", "100", "110"},
            {"011", "010", "010", "010", "110", "100"},
            {"1010", "1111"},
            {"1100", "0101", "0101", "0111"},
            {"10", "11", "10", "10", "10"},
            {"1000", "1010", "1111", "0100", "0100"},
            {"11", "10", "10", "10", "10", "10", "10"},
            {"010", "111", "100", "100"},
            {"11"},
            {"001", "101", "111"},
            {"010", "111", "101"},
            {"00100", "00100", "11111", "00100", "00100"},
            {"0001", "0011", "0010", "0010", "0110", "1100"},
            {"11", "10", "11", "10", "11"},
            {"0100", "0100", "0100", "1111", "0100"},
            {"01", "11", "10", "10", "10"},
            {"011", "010", "110", "100"},
            {"011", "010", "110", "011", "010", "010"},
            {"110", "110", "011", "010", "010", "010"},
            {"010", "011", "110", "010"},
            {"1100", "1111"},
            {"0011", "1110", "1000", "1100"},
            {"011", "010", "010", "110"},
            {"010", "010", "111", "010"},
            {"111", "101", "100", "110"},
            {"010", "011", "110", "100"},
            {"100", "110", "111"},
            {"10", "10", "10", "11"},
            {"0100", "1111", "1000"},
            {"011", "110", "100", "100"},
            {"01", "11", "10", "11"}};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(tiles.begin(), tiles.end(), g);
    int tilesToPick;
    int numPlayers = players.size();
    double ratio = 10.67;
    tilesToPick = static_cast<int>(std::ceil(numPlayers * ratio));
    tiles.resize(tilesToPick);
}

void Game::runGame()
{
    // Game loop implementation goes here

    // doit iterer sur les 9 rounds
    // et pour chaque round, iterer sur chaque joueur

    // sur chaque tour de joueur :
    // afficher le board
    // afficher les tiles disponibles
    // prompt le joueur d'une rep (ex: si il prend le tile OU si il veut trade)
    // si trade, gerer le trade
    // si pick tile, demander au joueur ou il veut poser le tile
    // verifier si le move est valide
    // si non, dire que le move n'est pas valide,
    // si oui, poser le tile sur le board
    // passer au joueur suivant

    for (int round = 1; round <= 9; ++round)
    {
        std::cout << "Round " << round << " begins!" << std::endl;
        for (auto &player : players)
        {
            std::cout << "It's " << player.getPlayerName() << "'s turn." << std::endl;
            board.displayBoard();
            if (tiles.empty())
            {
                std::cout << "No more tiles available." << std::endl;
                return;
            }
            else
            {
                std::cout << "\n Current tile:\n"
                          << std::endl;
                int tileSize;
                tiles[0].size() >> tileSize;
                for (const std::string &line : tiles[0])
                {
                    std::cout << line << std::endl;
                }
                std::cout << "\nDo you want to (1) pick this tile or (2) trade? Enter 1 or 2: ";
                std::string choice;
                std::cin >> choice;
                if (choice == "1")
                {
                    std::cout << "You chose to pick the tile." << std::endl;
                }
                else if (choice == "2")
                {
                    std::cout << "You chose to trade." << std::endl;
                    std::cout << "Which tile would you like to trade for? (Enter tile index 1 to 5): \n";
                    for (int i = 0; i < 5; ++i)
                    {
                        for (const std::string &line : tiles[i + 1])
                        {
                            std::cout << line << std::endl;
                        }
                        std::cout << "----\n";
                    }
                    // prompt pour le choix de la tile
                    // implementer la logique de trade ici
                    // 1 a 5
                    // si pick 3, push back 1 2, la prochaine tile sera la 4
                    int tradeChoice;
                    std::cin >> tradeChoice;
                    if (tradeChoice >= 1 && tradeChoice <= 5)
                    {
                        std::cout << "You traded for tile " << tradeChoice << "." << std::endl;
                        for (int i = 0; i < tradeChoice; i++)
                        {
                            tiles.push_back(tiles[i]);
                            tiles.erase(tiles.begin());
                        }
                    }
                    else
                    {
                        std::cout << "Invalid trade choice. Skipping turn." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid choice. Skipping turn." << std::endl;
                }
                while (true)
                {
                    std::cout << "Do you want to (F)lip, (R)otate, or (P)lace the tile? Enter F, R, or P: ";
                    char action;
                    std::cin >> action;
                    if (action == 'F' || action == 'f')
                    {
                        std::reverse(tiles[0].begin(), tiles[0].end());
                        for (auto &line : tiles[0])
                        {
                            std::reverse(line.begin(), line.end());
                        }
                        for (const std::string &line : tiles[0])
                        {
                            std::cout << line << std::endl;
                        }
                    }
                    else if (action == 'R' || action == 'r')
                    {
                        std::cout << "You chose to rotate the tile." << std::endl;
                        auto &tile = tiles[0];
                        tile = rotateTile90Clockwise(tile);
                        for (const std::string &line : tiles[0])
                        {
                            std::cout << line << std::endl;
                        }
                    }
                    else if (action == 'P' || action == 'p')
                    {
                        std::cout << "You chose to place the tile." << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid action. Please enter F, R, or P." << std::endl;
                    }
                }
                // F pour flip
                // R pour rotate
                // P pour place

                while (true)
                {
                    std::cout << "Where would you like to place the tile? (Enter row and column, e.g., AB): ";
                    char rowChar, colChar;
                    std::cin >> rowChar >> colChar;
                    if (rowChar < 'A' || rowChar >= 'A' + size ||
                        colChar < 'A' || colChar >= 'A' + size)
                    {
                        std::cout << "Invalid position. Retry." << std::endl;
                        continue;
                    }
                    else
                    {
                        std::cout << "You chose to place the tile at " << rowChar << " " << colChar << "." << std::endl;
                        tiles.erase(tiles.begin());
                        break;
                    }
                }
            }
        }
    }
}
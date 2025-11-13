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
    std::random_device rd;
    std::mt19937 rng(rd());
    board.seedBonuses(numPlayers, rng);
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

    for (int round = 1; round <= 2; ++round)
    {
        std::cout << "Round " << round << " begins!" << std::endl;
        char symbol = 'A' + round - 1;
        std::string symbolStr(1, symbol);
        for (auto &player : players)
        {
            std::cout << "It's " << player.getPlayerName() << "'s turn." << std::endl;
            board.displayBoard();
            if (tiles.empty())
            {
                std::cout << "No more tiles available." << std::endl;
                return;
            }
            if (round == 1)
            {
                while (true)
                {
                    std::vector<std::string> oneByOne = {"1"};
                    std::string symbol(1, player.getPlayerId() + '0');

                    char rowChar, colChar;
                    std::cout << "Round 1: place your 1x1 tile (e.g. A,C): ";
                    std::cin >> rowChar >> colChar;

                    if (rowChar < 'A' || rowChar >= 'A' + size ||
                        colChar < 'A' || colChar >= 'A' + size)
                    {
                        std::cout << "Invalid position. Retry." << std::endl;

                        continue;
                    }
                    else 
                    {
                        int result = placeTile(board, oneByOne, rowChar - 'A', colChar - 'A', player, symbol);
                        if (result != 0)
                        {
                            std::cout << "Invalid placement, retry.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        else
                        {
                            std::cout << "Tile placed!\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            resolveBonusesAfterPlacement(player, symbolStr);
                            break;
                        }
                    }
                }
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

                if (player.getCoupon() == 0) {
                    std::cout << "No coupon, place your tile!" << std::endl;
                }
                else if (choice == "1")
                {
                    std::cout << "You chose to pick the tile." << std::endl;
                }
                else if (choice == "2")
                {
                    player.deductCoupon();
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
                        int result = placeTile(board, tiles[0], rowChar - 'A', colChar - 'A', player, symbolStr);
                        if (result != 0)
                        {
                            std::cout << "Invalid placement. Retry." << std::endl;
                            continue;
                        }
                        else
                        {
                            resolveBonusesAfterPlacement(player, symbolStr);
                            tiles.erase(tiles.begin());
                            break;
                        }
                    }
                }
            }
        }
    }

    redeemExchangeCoupon();

    checkForWinner();
}

int Game::placeTile(Board &board,
                    const std::vector<std::string> &tile,
                    int startRow, int startCol,
                    const Player &player,
                    std::string symbol)
{
    if (tile.empty())
        return -1;

    const int h = (int)tile.size();
    const int w = (int)tile[0].size();
    const int N = board.getSize();
    const int pid = player.getPlayerId();

    if (startRow < 0 || startCol < 0 || startRow + h > N || startCol + w > N)
        return -1;
    for (const auto &r : tile)
        if ((int)r.size() != w)
            return -1;

    auto filled = [](char ch)
    { return ch == '1'; };

    for (int dy = 0; dy < h; ++dy)
        for (int dx = 0; dx < w; ++dx)
            if (filled(tile[dy][dx]) && board.at(startRow + dy, startCol + dx).used != -1)
                return -1;

    auto partOfPlacement = [&](int ny, int nx)
    {
        int ly = ny - startRow, lx = nx - startCol;
        return (0 <= ly && ly < h && 0 <= lx && lx < w && filled(tile[ly][lx]));
    };

    bool hasAnyOwned = false;
    for (int y = 0; y < N && !hasAnyOwned; ++y)
        for (int x = 0; x < N && !hasAnyOwned; ++x)
            if (board.at(y, x).owner == pid)
                hasAnyOwned = true;

    bool touchesOwn = false;
    auto checkNeighbor = [&](int y, int x)
    {
        if (y < 0 || y >= N || x < 0 || x >= N)
            return;
        if (partOfPlacement(y, x))
            return;
        const Cell &c = board.at(y, x);
        if (c.used != -1)
        {
            if (c.owner >= 0 && c.owner != pid)
                throw 1;
            if (c.owner == pid)
                touchesOwn = true;
        }
    };

    try
    {
        for (int dy = 0; dy < h; ++dy)
            for (int dx = 0; dx < w; ++dx)
                if (filled(tile[dy][dx]))
                {
                    int y = startRow + dy, x = startCol + dx;
                    checkNeighbor(y - 1, x);
                    checkNeighbor(y + 1, x);
                    checkNeighbor(y, x - 1);
                    checkNeighbor(y, x + 1);
                }
    }
    catch (int)
    {
        return -2;
    }

    if (hasAnyOwned && !touchesOwn)
        return -3;

    for (int dy = 0; dy < h; ++dy)
        for (int dx = 0; dx < w; ++dx)
            if (filled(tile[dy][dx]))
            {
                Cell &cell = board.at(startRow + dy, startCol + dx);
                if (cell.bonus != Bonus::None)
                    cell.bonus = Bonus::None;
                cell.used = 1;
                cell.owner = pid;
                cell.color = player.getPlayerColor();
                cell.symbol = symbol;
            }

    return 0;
}

#include <vector>
#include <iostream>
#include <algorithm>
int Game::largestSquareForPlayer(Board &board, int playerId)
{
    int N = board.getSize();
    std::vector<int> prev(N + 1, 0), cur(N + 1, 0);
    int best = 0;

    for (int y = 1; y <= N; ++y)
    {
        for (int x = 1; x <= N; ++x)
        {
            if (board.at(y - 1, x - 1).owner == playerId)
            {
                cur[x] = 1 + std::min({prev[x], cur[x - 1], prev[x - 1]});
                best = std::max(best, cur[x]);
            }
            else
            {
                cur[x] = 0;
            }
        }
        std::swap(prev, cur);
        std::fill(cur.begin(), cur.end(), 0);
    }

    return best;
}

// Add this helper (needs Board::side() accessor and at(row,col))
int countOwned(Board& b, int pid) {
    int s = b.side();
    int n = 0;
    for (int r = 0; r < s; ++r)
        for (int c = 0; c < s; ++c)
            if (b.at(r,c).used == pid) ++n;
    return n;
}

void Game::checkForWinner() {
    int bestSize = 0, winnerIdx = -1; bool tie = false;

    for (size_t i = 0; i < players.size(); ++i) {
        int sz = largestSquareForPlayer(board, players[i].getPlayerId());
        if (sz > bestSize) { bestSize = sz; winnerIdx = (int)i; tie = false; }
        else if (sz == bestSize) { tie = true; }
    }

    // Tiebreaker by cell count (also covers bestSize == 0)
    if (tie || bestSize == 0) {
        int bestCells = -1; int cellsTieCount = 0; int bestIdx = -1;
        for (size_t i = 0; i < players.size(); ++i) {
            int cells = countOwned(board, players[i].getPlayerId());
            if (cells > bestCells) { bestCells = cells; bestIdx = (int)i; cellsTieCount = 1; }
            else if (cells == bestCells) { ++cellsTieCount; }
        }
        if (cellsTieCount == 1) { bestSize = -1; winnerIdx = bestIdx; tie = false; } // decided by cells
    }

    std::cout << "\n=== GAME OVER ===\n";
    board.displayBoard();

    if (tie) {
        std::cout << "Perfect tie (same square size and same owned cells).\n";
    } else if (bestSize > 0) {
        std::cout << "Winner: " << players[winnerIdx].getPlayerName()
                  << " with a " << bestSize << "x" << bestSize << " square!\n";
    } else if (bestSize == -1) { // decided by cells
        std::cout << "Winner by cells: " << players[winnerIdx].getPlayerName() << "\n";
    } else {
        std::cout << "No squares; winner by cells logic applied above.\n";
    }
}


bool Game::isCapturedBy(int pid, int r, int c)
{
    const int N = board.getSize();
    auto own = [&](int y, int x)
    {
        return y >= 0 && y < N && x >= 0 && x < N && board.at(y, x).owner == pid;
    };
    return own(r - 1, c) && own(r + 1, c) && own(r, c - 1) && own(r, c + 1);
}

void Game::resolveBonusesAfterPlacement(const Player &player, const std::string &symbol)
{
    const int pid = player.getPlayerId();
    const int N = board.getSize();

    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            Cell &cell = board.at(r, c);
            if (cell.bonus == Bonus::None)
                continue;

            if (isCapturedBy(pid, r, c))
            {
                Bonus b = cell.bonus;
                cell.bonus = Bonus::None;
                cell.owner = pid;
                cell.used = 1;
                cell.color = player.getPlayerColor();
                cell.symbol = "*";

                applyCapturedBonus(player, r, c, b, symbol);
            }
        }
    }
}

void Game::applyCapturedBonus(const Player &player, int /*r*/, int /*c*/, Bonus b, const std::string &symbol)
{
    const int pid = player.getPlayerId();

    switch (b)
    {
    case Bonus::Exchange:
        if ((int)exchangeCoupons.size() <= pid)
            exchangeCoupons.resize(pid + 1, 0);
        exchangeCoupons[pid] += 1;
        std::cout << player.getPlayerName()
                  << " captured an Exchange bonus (+1 coupon, now "
                  << exchangeCoupons[pid] << ").\n";
        break;

    case Bonus::Stone:
        std::cout << player.getPlayerName()
                  << " captured a Stone bonus — place a stone now.\n";
        placeStoneImmediate(pid);
        break;

    case Bonus::Robbery:
        std::cout << player.getPlayerName()
                  << " captured a Robbery bonus — resolve now.\n";
        doRobberyImmediate(player, symbol);
        break;

    default:
        break;
    }
}

#include <queue>
#include <cctype>

bool Game::parseCoord2(const char rr, const char cc, int &r, int &c)
{
    r = std::toupper(rr) - 'A';
    c = std::toupper(cc) - 'A';
    int N = board.getSize();
    return (r >= 0 && r < N && c >= 0 && c < N);
}

void Game::placeStoneImmediate(int pid)
{
    const int N = board.getSize();
    while (true)
    {
        std::cout << "Place your stone (e.g., AC): ";
        char rr, cc;
        if (!(std::cin >> rr >> cc))
        {
            std::cin.clear();
            continue;
        }

        int r, c;
        if (!parseCoord2(rr, cc, r, c))
        {
            std::cout << "Out of bounds.\n";
            continue;
        }

        Cell &cell = board.at(r, c);
        if (cell.used != -1)
        {
            std::cout << "Cell not empty.\n";
            continue;
        }

        cell.used = -2;
        cell.owner = -1;
        cell.color = "\033[90m";
        cell.symbol = "O";
        std::cout << "Stone placed at " << (char)std::toupper(rr) << (char)std::toupper(cc) << ".\n";
        break;
    }
}

void Game::doRobberyImmediate(const Player &player, const std::string &newSymbol)
{
    const int N = board.getSize();
    const int pid = player.getPlayerId();

    while (true)
    {
        std::cout << "Robbery: pick an enemy tile (enter a cell on it, e.g., AC): ";
        char rr, cc;
        if (!(std::cin >> rr >> cc))
        {
            std::cin.clear();
            continue;
        }

        int r, c;
        if (!parseCoord2(rr, cc, r, c))
        {
            std::cout << "Out of bounds.\n";
            continue;
        }

        const Cell &chosen = board.at(r, c);
        if (chosen.used == -1 || chosen.owner == -1)
        {
            std::cout << "Not a placed tile.\n";
            continue;
        }
        if (chosen.owner == pid)
        {
            std::cout << "That’s already yours.\n";
            continue;
        }

        captureTileFlood(player, r, c, newSymbol);
        std::cout << "Robbery successful at " << (char)std::toupper(rr) << (char)std::toupper(cc) << ".\n";
        break;
    }
}

void Game::captureTileFlood(const Player &player, int startR, int startC, const std::string &newSymbol)
{
    const int N = board.getSize();
    const int pid = player.getPlayerId();
    const int prevOwner = board.at(startR, startC).owner;
    const std::string sym = board.at(startR, startC).symbol;

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<char>> vis(N, std::vector<char>(N, 0));
    auto inb = [&](int y, int x)
    { return y >= 0 && y < N && x >= 0 && x < N; };

    q.push({startR, startC});
    vis[startR][startC] = 1;

    while (!q.empty())
    {
        auto [r, c] = q.front();
        q.pop();
        Cell &cell = board.at(r, c);

        cell.owner = pid;
        cell.color = player.getPlayerColor();
        cell.symbol = newSymbol;

        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};
        for (int k = 0; k < 4; ++k)
        {
            int nr = r + dr[k], nc = c + dc[k];
            if (!inb(nr, nc) || vis[nr][nc])
                continue;

            const Cell &nb = board.at(nr, nc);
            if (nb.used == -2)
                continue;
            if (nb.used != -1 && nb.owner == prevOwner && nb.symbol == sym)
            {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
}

void Game::redeemExchangeCoupon()
{
    const int N = board.getSize();

    for (const auto &p : players)
    {
        int pid = p.getPlayerId();
        if ((int)exchangeCoupons.size() <= pid)
            exchangeCoupons.resize(pid + 1, 0);
    }

    std::cout << "\n=== Exchange Coupon End Phase ===\n";
    for (const auto &player : players)
    {
        const int pid = player.getPlayerId();
        int &coupons = exchangeCoupons[pid];
        coupons = 1;
        while (coupons > 0)
        {
            board.displayBoard();
            std::cout << player.getPlayerName() << " has " << coupons
                      << " coupon(s). Place a 1x1 tile? (y/n): ";
            char yn;
            if (!(std::cin >> yn))
            {
                std::cin.clear();
                continue;
            }
            if (yn != 'y' && yn != 'Y')
                break;

            while (true)
            {
                std::cout << "Enter position (e.g., AC): ";
                char rr, cc;
                if (!(std::cin >> rr >> cc))
                {
                    std::cin.clear();
                    continue;
                }
                int r = std::toupper(rr) - 'A';
                int c = std::toupper(cc) - 'A';
                if (r < 0 || r >= N || c < 0 || c >= N)
                {
                    std::cout << "Out of bounds.\n";
                    continue;
                }

                Cell &cell = board.at(r, c);
                if (cell.used != -1)
                {
                    std::cout << "Cell not empty.\n";
                    continue;
                }

                cell.used = 1;
                cell.owner = pid;
                cell.color = player.getPlayerColor();
                cell.symbol = "+";
                std::cout << "Placed at " << (char)std::toupper(rr) << (char)std::toupper(cc) << ".\n";
                break;
            }

            --coupons;
        }
    }
    std::cout << "=== End Phase Completed ===\n";
}

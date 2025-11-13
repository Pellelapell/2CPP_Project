#pragma once
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
    private:
        std::vector<class Player> players;
        std::vector<std::vector<std::string>> tiles;
        int size;
        int currentRound;
        Board board;
    
    public:
        Game(std::vector<class Player> players, int numPlayers);
        ~Game();    
    
        std::vector<class Player> getPlayers();
        int getSize();
        
        void initializeTiles();
        int placeTile(Board& board, const std::vector<std::string>& tile, int startRow, int startCol, const Player& player, std::string symbol);
        void runGame();
        void checkForWinner();
        int largestSquareForPlayer(Board& board, int playerId);

        void resolveBonusesAfterPlacement(int pid, std::string& symbol);
        std::vector<int> exchangeCoupons;

        void resolveBonusesAfterPlacement(const Player& player, const std::string& symbol);
        bool isCapturedBy(int pid, int r, int c);
        void applyCapturedBonus(const Player& player, int r, int c, Bonus b, const std::string& symbol);

        void doRobberyImmediate(const Player& player, const std::string& newSymbol);
        void placeStoneImmediate(int pid);
        void captureTileFlood(const Player& player, int startR, int startC, const std::string& newSymbol);


        bool parseCoord2(const char rr, const char cc, int& r, int& c);
        void redeemExchangeCoupon();
};
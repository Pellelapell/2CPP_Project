#pragma once
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
    private:
        std::vector<class Player> players;
        std::vector<std::string> tiles;
        int size;
        Board board;
    
    public:
        Game(std::vector<class Player> players, int numPlayers);
        ~Game();    
    
        std::vector<class Player> getPlayers();
        int getSize();
        
        void initializeTiles();

        void runGame();
};
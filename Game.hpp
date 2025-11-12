#pragma once
#include <iostream>
#include <vector>
#include "Player.hpp"

class Game
{
    private:
        std::vector<class Player> players;
        int size;
        std::vector<std::string> tiles;
    
    public:
        Game(std::vector<class Player> players, int numPlayers);
        ~Game();    
    
        std::vector<class Player> getPlayers();
        int getSize();
        
        void initializeTiles();

        void runGame();
};
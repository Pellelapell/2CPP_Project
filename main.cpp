#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include "Player.hpp"

int getNumPlayers()
{
    int numPlayers;
    int isDigit = 0;

    while (!isDigit)
    {
        std::cout << "Entre le nombre de joueurs" << std::endl;
        std::cin >> numPlayers;

        if (std::isdigit(numPlayers))
            isDigit = 1;
        else
            std::cout << "Invalid integer" << std::endl;
    }
    return numPlayers;
}

std::vector<Player> createPlayerList(int numPlayers)
{
    std::vector<Player> playerList;
    for (int i = 0; i < numPlayers; ++i)
    {
        Player player;
        std::cout << "Joueur " << i + 1 << " , entre ton pseudo !" << std::endl;
        std::string playerName;
        std::cin >> playerName;
        player.setPlayerName(playerName);
        std::cout << "Quelle couleur voudrais-tu ?" << std::endl;
        std::string playerColor;
        std::cin >> playerColor;
        player.setPlayerColor(playerColor);
        std::cout << player.getPlayerColor() << player.getPlayerName() << std::endl;
        playerList.push_back(player);
    }
    return playerList;
}

int main()
{
    int numPlayers = getNumPlayers();
    std::vector<Player> playerList = createPlayerList(numPlayers);
    return 0;
}
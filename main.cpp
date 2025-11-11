#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Player.hpp"

int getNumPlayers()
{
    std::cout << "Entre le nombre de joueurs" << std::endl;
    int numPlayers;
    std::cin >> numPlayers;
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
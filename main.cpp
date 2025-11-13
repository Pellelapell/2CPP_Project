#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <limits>
#include "Player.hpp"
#include "Game.hpp"

int getNumPlayers()
{
    int numPlayers;

    while (true)
    {
        std::cout << "How many players ?" << std::endl;

        if (std::cin >> numPlayers && numPlayers >= 2 && numPlayers <= 9)
            return (numPlayers);
        else
        {
            std::cout << "Invalid number, pick between 2 and 9." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::vector<Player> createPlayerList(int numPlayers)
{
    std::vector<Player> playerList;
    std::vector<std::string> colors = {"Rouge", "Bleu", "Vert", "Jaune", "Noir", "Blanc", "Violet", "Orange", "Rose"};

    for (int i = 0; i < numPlayers; ++i)
    {
        Player player;
        std::cout << "Player " << i + 1 << " , enter your nickname !" << std::endl;
        player.setPlayerId(i + 1);
        std::string playerName;
        std::cin >> playerName;
        player.setPlayerName(playerName);
        std::cout << "Which color would you like ? Here are the available colors : " << std::endl;
        for (int n = 0; n < colors.size(); ++n)
            std::cout << colors[n] << " ";
        std::cout << std::endl;

        std::string playerColor;
        std::cin >> playerColor;
        while (std::find(colors.begin(), colors.end(), playerColor) == colors.end())
        {
            std::cout << "Invalid Color, please choose between available colors :" << std::endl;
            for (int n = 0; n < colors.size(); ++n)
                std::cout << colors[n] << " ";
            std::cout << std::endl;
            std::cin >> playerColor;
        }
        std::vector<std::string>::iterator it = std::find(colors.begin(), colors.end(), playerColor);
        colors.erase(it);
        player.setPlayerColor(playerColor);
        std::cout << player.getPlayerId() << player.getPlayerColor() << ' ' << player.getPlayerName() << "\033[37m" << std::endl;
        playerList.push_back(player);
    }
    return playerList;
}

int main()
{
    int numPlayers = getNumPlayers();
    std::vector<Player> playerList = createPlayerList(numPlayers);
    Game game(playerList, numPlayers);
    game.runGame();
    return 0;
}
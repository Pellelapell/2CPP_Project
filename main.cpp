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
        std::cout << "Entre le nombre de joueurs" << std::endl;

        if (std::cin >> numPlayers && numPlayers >= 2 && numPlayers <= 9)
            return (numPlayers);
        else
        {
            std::cout << "Nombre de joueur invalide : doit etre entre 2 et 9" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Look pour tolower les colors
std::vector<Player> createPlayerList(int numPlayers)
{
    std::vector<Player> playerList;
    std::vector<std::string> colors = {"Rouge", "Bleu", "Vert", "Jaune", "Noir", "Blanc", "Violet", "Orange", "Rose"};

    for (int i = 0; i < numPlayers; ++i)
    {
        Player player;
        std::cout << "Joueur " << i + 1 << " , entre ton pseudo !" << std::endl;
        std::string playerName;
        std::cin >> playerName;
        player.setPlayerName(playerName);
        std::cout << "Quelle couleur voudrais-tu ? voici les couleurs disponibles : " << std::endl;
        for (int n = 0; n < colors.size(); ++n)
            std::cout << colors[n] << " ";
        std::cout << std::endl;

        std::string playerColor;
        std::cin >> playerColor;
        while (std::find(colors.begin(), colors.end(), playerColor) == colors.end())
        {
            std::cout << "Couleur invalide, choisis-en une autre parmi les couleurs disponibles :" << std::endl;
            for (int n = 0; n < colors.size(); ++n)
                std::cout << colors[n] << " ";
            std::cout << std::endl;
            std::cin >> playerColor;
        }
        std::vector<std::string>::iterator it = std::find(colors.begin(), colors.end(), playerColor);
        colors.erase(it);
        player.setPlayerColor(playerColor);
        std::cout << player.getPlayerColor() << ' ' << player.getPlayerName() << std::endl;
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
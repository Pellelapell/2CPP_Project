#include "Player.hpp"
#include <iostream>
#include <unordered_map>
#include <algorithm>

void Player::setPlayerName(std::string name)
{
    this->playerName = name;
}

void Player::setPlayerColor(std::string color)
{
    this->playerColor = color;
    static const std::unordered_map<std::string, std::string> colorCode = {
        {"Rouge", "\033[31m"},
        {"Bleu", "\033[34m"},
        {"Vert", "\033[32m"},
        {"Jaune", "\033[33m"},
        {"Noir", "\033[30m"},
        {"Blanc", "\033[37m"},
        {"Violet", "\033[35m"},
        {"Orange", "\033[91m"},
        {"Rose", "\033[95m"}
    };
        std::string code = color;
        std::transform(code.begin(), code.end(), code.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        auto it = colorCode.find(color);
        this->playerColor = it->second;
};


std::string Player::getPlayerColor()
{
    return (playerColor);
}

std::string Player::getPlayerName()
{
    return (playerName);
}

#include "Player.hpp"
#include <iostream>

void Player::setPlayerName(std::string name)
{
    this->playerName = name;
}

void Player::setPlayerColor(std::string color)
{
    this->playerColor = color;
}

std::string Player::getPlayerColor()
{
    return (playerColor);
}

std::string Player::getPlayerName()
{
    return (playerName);
}

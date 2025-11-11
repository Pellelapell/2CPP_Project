#pragma once
#include <string>

class Player
{
private:
    std::string playerName;
    std::string playerColor;

public:
    void setPlayerName(std::string name);
    void setPlayerColor(std::string color);
    std::string getPlayerName();
    std::string getPlayerColor();
};
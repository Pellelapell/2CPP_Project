#pragma once
#include <string>

class Player
{
private:
    std::string playerName;
    std::string playerColor;
    int exchangesCoupon;
    int id;

public:
    void setPlayerName(std::string name);
    void setPlayerColor(std::string color);
    void setPlayerId(int playerId);
    std::string getPlayerName() const { return playerName; }
    int getPlayerId() const { return id; }
    std::string getPlayerColor() const { return playerColor; }
};
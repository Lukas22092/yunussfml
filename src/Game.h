#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
struct Object
{
    int posx{};
    int posy{};
    int sx{};
    int sy{};
};
class Game
{
    private:
    std::vector<Object> objects{};
    Player player{};

    public:
    bool leftWallCoalision(const Player& player, const std::vector<Object>& objects);
    bool rightWallCoalision(const Player& player, const std::vector<Object>& objects);
    bool groundCoalision(const Player& player, const std::vector<Object>& objects); 
    bool headCoalision(const Player& player, const std::vector<Object>& objects); 
    void start();
};
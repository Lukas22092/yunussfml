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
    bool leftWallCoalision(Player player, std::vector<Object> objects);
    bool rightWallCoalision(Player player, std::vector<Object> objects);
    bool groundCoalision(Player player, std::vector<Object> objects); 
    bool headCoalision(Player player, std::vector<Object> objects); 
    void start();
};
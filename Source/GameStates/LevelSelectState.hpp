//
// Created by david on 1/27/2017.
//

#ifndef SKILLED_EAGLE_GAME_LEVELSELECTSTATE_HPP
#define SKILLED_EAGLE_GAME_LEVELSELECTSTATE_HPP

#include <SFML/System/String.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IState.h"
#include "../Menu.hpp"

class Game;

class LevelSelectState: public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn;
public:
    LevelSelectState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};


#endif //SKILLED_EAGLE_GAME_LEVELSELECTSTATE_HPP

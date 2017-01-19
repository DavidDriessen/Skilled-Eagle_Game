//
// Created by david on 1/19/2017.
//

#ifndef SKILLED_EAGLE_GAME_CONTROLLESSTATE_HPP
#define SKILLED_EAGLE_GAME_CONTROLLESSTATE_HPP

#include <SFML/System/String.hpp>
#include <functional>
#include "IState.h"
#include "../Menu.hpp"

class Game;

class ControllesState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn = {
            "Jump",
            "Apply"};
public:
    ControllesState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};

#endif //SKILLED_EAGLE_GAME_CONTROLLESSTATE_HPP

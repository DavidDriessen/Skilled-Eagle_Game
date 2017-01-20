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

enum Actions {
    Jump
};

struct KeyActions {
    sf::Keyboard::Key key = sf::Keyboard::Unknown;
    std::function<void(void)> action = []() {};
};

class ControllesState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn = {
            "Jump",
            "Apply"};
    std::map<Actions, KeyActions> key;
    KeyActions *key_to_bind;
public:
    ControllesState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void asign_action(Actions &action, std::function<void(void)> &func);

    void run_actions(sf::Event &event);
};

#endif //SKILLED_EAGLE_GAME_CONTROLLESSTATE_HPP

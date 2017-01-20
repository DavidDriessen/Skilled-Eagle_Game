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
    Jump,
    Left,
    Right
};

struct KeyActions {
    sf::Keyboard::Key key = sf::Keyboard::Unknown;
    std::function<void(void)> pressed = []() {};
    std::function<void(void)> released = []() {};
};

class ControllesState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn = {
            "Jump",
            "Left",
            "Right"};
    std::map<Actions, KeyActions> key;
    KeyActions *key_to_bind;
public:
    ControllesState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void assign_pressed(const Actions &action, const std::function<void()> &func);

    void assign_released(const Actions &action, const std::function<void()> &func);

    void run_actions(sf::Event &event);
};

#endif //SKILLED_EAGLE_GAME_CONTROLLESSTATE_HPP

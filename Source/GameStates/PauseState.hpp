//
// Created by david on 1/23/2017.
//

#ifndef SKILLED_EAGLE_GAME_PAUSESTATE_HPP
#define SKILLED_EAGLE_GAME_PAUSESTATE_HPP


#include "IState.h"
#include "../Menu.hpp"

class Game;

class PauseState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn = {
            "HighScore:    ",
            "Resume",
            "Options",
            "Main Menu"};
public:
    PauseState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};


#endif //SKILLED_EAGLE_GAME_PAUSESTATE_HPP

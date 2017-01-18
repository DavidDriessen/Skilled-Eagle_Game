//
// Created by robbie on 17-1-2017.
//

#ifndef MENU_H
#define MENU_H

#include <SFML/System/String.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IState.h"
#include "../Menu.hpp"

class Game;

class MenuState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> l = {
            "Start Game",
            "Edit Character",
            "Show Highscores",
            "Options",
            "Quit"};
public:
    MenuState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};


#endif //WAVEFORMS_MENU_H

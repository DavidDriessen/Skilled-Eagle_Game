//
// Created by endargon on 2/1/17.
//

#ifndef SKILLED_EAGLE_GAME_MUSICSELECTSTATE_HPP
#define SKILLED_EAGLE_GAME_MUSICSELECTSTATE_HPP

#include <SFML/System/String.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IState.h"
#include "../Menu.hpp"

class Game;

class MusicSelectState: public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn;
public:
    MusicSelectState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};


#endif //SKILLED_EAGLE_GAME_MUSICSELECTSTATE_HPP

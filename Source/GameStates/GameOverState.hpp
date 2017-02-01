//
// Created by endargon on 2/1/17.
//

#include <SFML/Graphics/Text.hpp>
#include "IState.h"
#include "../Menu.hpp"
#include "../Utility/ResourceIdentifiers.hpp"

#ifndef SKILLED_EAGLE_GAME_GAMEOVERSTATE_HPP
#define SKILLED_EAGLE_GAME_GAMEOVERSTATE_HPP

class Game;

class GameOverState : public IState {
    Game *game;
    bool dead = false;
    sf::Text status;
    sf::Text score;
    sf::Clock blink;
    sf::Color textColor;
    //some variable for highscore list
public:

    GameOverState(Game *pGame, bool dead);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    int direction = 0;
};

#endif //SKILLED_EAGLE_GAME_GAMEOVERSTATE_HPP

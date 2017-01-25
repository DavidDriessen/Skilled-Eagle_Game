//
// Created by david on 1/25/2017.
//

#ifndef SKILLED_EAGLE_GAME_SOONSTATE_HPP
#define SKILLED_EAGLE_GAME_SOONSTATE_HPP

#include <SFML/Graphics.hpp>
#include "IState.h"

class Game;

class SoonState: public IState {
    Game *game;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
public:
    SoonState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);
};


#endif //SKILLED_EAGLE_GAME_SOONSTATE_HPP

//
// Created by david on 2/1/2017.
//

#ifndef SKILLED_EAGLE_GAME_HIGHSCORESTATE_HPP
#define SKILLED_EAGLE_GAME_HIGHSCORESTATE_HPP


#include "IState.h"
#include "../Menu.hpp"

class Game;

class HighScoreState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn;
public:
    HighScoreState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void load_score();
};


#endif //SKILLED_EAGLE_GAME_HIGHSCORESTATE_HPP

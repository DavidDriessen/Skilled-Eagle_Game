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
    int score = 0;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> btn;
public:
    HighScoreState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void load_levels();

    void load_score(std::string level, bool sort = true);

    void add_score(std::string level, int score);

    void set_current_score(int score);

    int get_current_score();

    int get_latest_score(std::string level);

    int get_highest_score(std::string level);
};


#endif //SKILLED_EAGLE_GAME_HIGHSCORESTATE_HPP

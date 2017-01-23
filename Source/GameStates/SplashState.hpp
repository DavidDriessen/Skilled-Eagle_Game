//
// Created by MuscioCraft on 19-1-2017.
//


#ifndef WAVEFORMS_SPLASHSTATE_HPP
#define WAVEFORMS_SPLASHSTATE_HPP
#include "IState.h"
#include <SFML/Graphics.hpp>


class Game;

class SplashState : public IState {
private:
    Game *game;
    sf::Sprite sprite_eagle;
    sf::Sprite sprite_name;
    sf::Sprite sprite_presents;

    sf::Texture texture_eagle;
    sf::Texture texture_name;
    sf::Texture texture_presents;

    sf::Clock clock_eagle;
    sf::Clock clock_name;
    sf::Clock clock_presents;

    sf::Vector2f size;
    sf::Time elapsed;
    sf::Time time_limit_name = sf::seconds(3);
    sf::Time time_limit_presents = time_limit_name + sf::seconds(2);
    sf::Time time_limit_eagle = time_limit_presents + sf::seconds(3);


public:
    SplashState();

    SplashState(Game *pGame);

    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow &window);

};


#endif //WAVEFORMS_SPLASHSTATE_H

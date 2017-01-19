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
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f size;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time time_limit = sf::seconds(5);
public:
    SplashState();

    SplashState(Game *pGame);

    void input(sf::Event &event);
    void update(float delta);
    void draw(sf::RenderWindow &window);

};


#endif //WAVEFORMS_SPLASHSTATE_H

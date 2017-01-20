//
// Created by robbie on 17-1-2017.
//

#ifndef GAME_H
#define GAME_H

#include "IState.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level.h"
#include "../ScreenObjects/ScreenObject.h"
#include "../Character.hpp"

class Game;

class PlayState : public IState {
private:
    Game *game;
    Level level;
    Character player = Character(sf::Vector2f(0, 300), 0.3, 0.4, 100, 172, 260, 0.2);
    std::vector<ScreenObject *> level_objects;
public:
    PlayState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);


};


#endif //WAVEFORMS_GAME_H

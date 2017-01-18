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
class Game;

class PlayState : public IState {
private:
    Game *game;
    Level level;
    std::vector<ScreenObject*> level_objects;
public:
    PlayState();

    PlayState(Game *pGame);

    void input(sf::Event &event);
    void update(float data);
    void draw(sf::RenderWindow &window);


};


#endif //WAVEFORMS_GAME_H
